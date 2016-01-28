#include "wrradioscreen.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "mpd_tools.h"
#include "cgapplication.h"

WRRadioScreen::WRRadioScreen(CGWidget *parent):
    CGScreen(parent)
{
    m_playingItem=-1;
    //std::cout<<"WRRadioScreen::paint size="<<size()<<"\n";
    //setBackgroundColor(CGColor::ccDarkgray);
    CGLinearLayout* vlay=new CGLinearLayout(this, cgdVertical);
    setLayout(vlay);


    m_stationList=new CGListWidget(this);

    CGWidget* wibhlay=new CGWidget(this);
    CGLinearLayout* hlay=new CGLinearLayout(wibhlay, cgdHorizontal);
    wibhlay->setLayout(hlay);
    m_playState=new CGImage(0,0,24,24, wibhlay);
    m_playState->setImageSymbol(CGSymbol::iPlayAnimated);
    m_label=new CGLabel(0,0,24,24,wibhlay);
    m_label->setText("line 1 ...\nplaying ...\nline 3 ... ");
    m_label->setFontSize(12);
    hlay->addWidget(m_playState, -3);
    hlay->addWidget(new CGWidget(wibhlay), -1);
    hlay->addWidget(m_label, -15);

    vlay->addWidget(m_stationList, -4);
    vlay->addWidget(wibhlay, -1);
    hlay->layoutWidgets();
    vlay->layoutWidgets();
    addWebradiosFromCONF("webradio_stations.ini");
    addWebradiosFromCONF("~/.webradio_gui/webradio_stations.ini");
    addWebradiosFromCONF("/etc/webradio_stations.ini");
    addWebradiosFromCONF("~/webradio_stations.ini");

    m_playing=mpdtools::isPlaying();
}

WRRadioScreen::~WRRadioScreen()
{
    stop();
}

void WRRadioScreen::paint(cairo_t *c)
{
    if ((m_playing=mpdtools::isPlaying())) {
        m_playState->setImageSymbol(CGSymbol::iPlayAnimated);
        std::string txt;
        mpdtools::clearErrors();
        txt+=mpdtools::getCurrentName();
        mpdtools::hadError(true);
        if (txt.size()>0 && txt[txt.size()-1]!='\n') txt+="\n";
        mpdtools::clearErrors();
        txt+=mpdtools::getCurrentTitle();
        mpdtools::hadError(true);
        if (txt.size()>0 && txt[txt.size()-1]!='\n') txt+="\n";
        char elapsed[1024];
        mpdtools::clearErrors();
        float el=mpdtools::getElapsedTime();
        mpdtools::hadError(true);
        sprintf(elapsed, "  elapsed: %02d:%02d", (int)floor(el/60), int(el)%60);
        txt+=elapsed;
        //if (txt.size()>0 && txt[txt.size()-1]!='\n') txt+="\n";
        m_label->setText(txt);
    } else {
        m_playState->setImageSymbol(CGSymbol::iPause);
        m_label->setText("\n ... not playing ...\n\n");
    }
    CGScreen::paint(c)   ;
    //std::cout<<"WRRadioScreen::paint size="<<size()<<"\n";
}

void WRRadioScreen::event(CGEvent *e)
{
    CGButtonClickedEvent* clk=dynamic_cast<CGButtonClickedEvent*>(e);
    CGInputScroll* rot=dynamic_cast<CGInputScroll*>(e);
    std::cout<<"WRRadioScreen::event: "<<e->toString()<<", "<<clk<<", "<<rot<<"\n";
    if (clk && (clk->button()==BTN_RADIO_PLAY || clk->button()==BTN_RADIO_ENTER)) {
        std::cout<<"  BTN_RADIO_PLAY-clicked playing="<<m_playing<<" m_playingItem="<<m_playingItem<<"\n";
        int idx=m_stationList->currentItem();
        bool old_playing=m_playing;
        int old_m_playingItem=m_playingItem;
        if (m_playing) {
            stop();
        }

        if (!old_playing || (old_playing&&(idx!=old_m_playingItem))){
            play(idx);
        }
        clk->accept();
    } else if (rot && rot->id()==ROTARY_RADIO_MAIN) {
        std::cout<<"  ROTARY_RADIO_MAIN-turned "<<rot->inc()<<"\n";
        m_stationList->nextItem(rot->inc());
        rot->accept();
    } else {
        CGScreen::event(e);
    }
}

void WRRadioScreen::stop()
{
    m_playing=false;
    std::lock_guard<std::recursive_mutex> lock(mpdtools::getMPDMutex());
    if (mpdtools::getConnection()) {
        std::cout<<"stopping ...\n";
        mpdtools::clearErrors();
        mpd_run_stop(mpdtools::getConnection());
        mpdtools::hadError(true);
        m_playingItem=-1;
    }
}

void WRRadioScreen::play(int idx)
{
    m_playing=true;
    std::lock_guard<std::recursive_mutex> lock(mpdtools::getMPDMutex());
    if (mpdtools::getConnection()) {
        std::cout<<"clearing playlist ...\n";
        mpdtools::clearErrors();
        mpd_run_clear(mpdtools::getConnection());
        mpdtools::hadError(true);

        if (idx>=0 && idx<(long long)m_stations.size()) {
            m_playingItem=idx;
            CGApplication::getInstance().getINI().put<int>("radio.lastStationIdx", idx);
            std::cout<<"sending URI '"<<m_stations[idx].uri<<"' ...\n";
            mpdtools::clearErrors();
            mpd_send_add(mpdtools::getConnection(), m_stations[idx].uri.c_str());
            mpdtools::hadError(true);
            mpdtools::clearErrors();
            mpd_response_finish(mpdtools::getConnection());
            mpdtools::hadError(true);
            std::cout<<"playing ...\n";
            mpdtools::clearErrors();
            mpd_run_play(mpdtools::getConnection());
            mpdtools::hadError(true);
        }
    }
}

void WRRadioScreen::onShow()
{
    int idx=CGApplication::getInstance().getINI().get<int>("radio.lastStationIdx", 0);
    play(idx);
    m_stationList->setCurrentItem(idx);
    std::cout<<" idx="<<idx<<"\n";
}

void WRRadioScreen::onHide()
{
    stop();
}

void WRRadioScreen::addWebradiosFromCONF(const std::string &filename)
{
    if (!boost::filesystem::exists(boost::filesystem::path(filename))) return;
    std::cout<<"parsing webradio-stations from '"<<filename<<"' ... \n";
    try {
        using boost::property_tree::ptree;
        ptree pt;

        read_info(filename, pt);
        int s=0;

        for(auto &v: pt) {
            //std::cout<<"  reading block "<<s<<": "<<v.first<<"\n";
            s++;
            if ((v.first=="stream") || (v.first=="station")) {
                radiostation s;
                s.name=v.second.get<std::string>("name");
                s.uri=v.second.get<std::string>("uri");
                bool found=false;
                for (radiostation& vv: m_stations) {
                    if (vv.name==s.name) {
                        vv.uri=s.uri;
                        found =true;
                        break;
                    }
                }
                if (!found) {
                    //std::cout<<"    adding station '"<<s.name<<"': "<<s.uri<<"\n";
                    m_stations.push_back(s);
                    std::cout<<"    adding station '"<<s.name<<"': "<<s.uri<<"\n";//<<" --> "<<m_stations.size()<<"\n";
                } else {
                    std::cout<<"    updated station '"<<s.name<<"': "<<s.uri<<"\n";
                }
            }
        }
        updateList();
    } catch (std::exception& E) {
        std::cout<<"  error: "<<E.what()<<"\n";
    }
    std::cout<<"parsing webradio-stations from '"<<filename<<"' ... DONE!\n";

}

void WRRadioScreen::updateList()
{
    while ((long long)m_stations.size()<m_stationList->count()) {
        m_stationList->removeItem(0);
    }
    while ((long long)m_stations.size()>m_stationList->count()) {
        m_stationList->addItem("");
    }
    //std::cout<<m_stations.size()<<", "<<m_stationList->count()<<"\n";
    for (size_t i=0; i<m_stations.size(); i++) {
        m_stationList->setItem(i, m_stations[i].name);
    }
}

