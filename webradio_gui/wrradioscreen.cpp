#include "precomp.h"
#include "wrradioscreen.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include "mpd_tools.h"
#include "rpi_tools.h"
#include "cgapplication.h"

WRRadioScreen::WRRadioScreen(CGWidget *parent):
    CGScreen(parent)
{
    m_playingItem=-1;
    //std::cout<<"WRRadioScreen::paint size="<<size()<<"\n";
    //setBackgroundColor(CGColor::ccDarkgray);
    CGLinearLayout* vlay=new CGLinearLayout(this, cgdVertical);
    setLayout(vlay);


    m_stationList=new CGListWidget<radiostation>(this);


    CGWidget* wibhlay=new CGWidget(this);
    //wibhlay->setFrameColor(CGColor("blue"));
    CGLinearLayout* hlay=new CGLinearLayout(wibhlay, cgdHorizontal);
    wibhlay->setLayout(hlay);

    CGWidget* wibvlayt=new CGWidget(wibhlay);
    //wibvlayt->setFrameColor(CGColor("red"));
    CGLinearLayout* vlayt=new CGLinearLayout(wibvlayt, cgdVertical);
    wibvlayt->setLayout(vlayt);
    m_playState=new CGImage(0,0,28,28, wibhlay);
    m_playState->setImageSymbol(CGSymbol::iPlayAnimated);

    m_labelInfo=new CGMarqueeLabel(0,0,24,9,wibvlayt);
    m_labelInfo->setText("line 2 ...");
    m_labelInfo->setFontSize(12);
    //m_label1->setBackgroundColor(CGColor::ccGray50);
    m_labelName=new CGMarqueeLabel(0,0,24,14,wibvlayt);
    m_labelName->setText("line 1 ...");
    m_labelName->setFontSize(14);
    m_labelName->setBold(true);
    //m_label2->setBackgroundColor(CGColor::ccGray25);


    m_labelElapsed=new CGLabel(0,0,12,10,wibvlayt);
    m_labelElapsed->setText("0/0");
    m_labelElapsed->setFontSize(9);

    vlayt->addWidget(m_labelName, -14);
    vlayt->addWidget(m_labelInfo, -12);
    vlayt->addWidget(m_labelElapsed, -8);
    vlayt->addWidget(new CGWidget(wibvlayt), -3);

    hlay->addWidget(m_playState, -5);
    hlay->addWidget(new CGWidget(wibhlay), -1);
    hlay->addWidget(wibvlayt, -25);

    vlay->addWidget(m_stationList, -3);
    vlay->addWidget(wibhlay, -1); // 1/5 2/10 4/20

    hlay->layoutWidgets();
    vlayt->layoutWidgets();
    hlay->layoutWidgets();
    vlay->layoutWidgets();

    addWebradiosFromCONF("webradio_stations.ini");
    addWebradiosFromCONF("~/.webradio_gui/webradio_stations.ini");
    addWebradiosFromCONF("/etc/webradio_stations.ini");
    addWebradiosFromCONF("~/webradio_stations.ini");
    addWebradiosFromCONF(CGApplication::getInstance().getINI().get<std::string>("radio.stations", ""));
    for (int i=0; i<10; i++) {
        addWebradiosFromCONF(CGApplication::getInstance().getINI().get<std::string>("radio.stations"+std::to_string(i+1), ""));
    }

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
        mpdtools::clearErrors();
        m_labelName->setText(mpdtools::getCurrentName());
        mpdtools::clearErrors();
        std::string title=mpdtools::getCurrentTitle();
        std::string artist=mpdtools::getCurrentArtist();
        std::string date=mpdtools::getCurrentDate();
        std::string album=mpdtools::getCurrentAlbum();
        std::string txt=(title.size()<=0)?std::string("???"):title;
        if (artist.size()>0 || date.size()>0 || album.size()>0) {
            txt+=" [";
            if (artist.size()>0) txt+=artist;
            if (date.size()>0) {
                if (txt.size()>2) txt+="; ";
                txt+=date;
            }
            if (album.size()>0) {
                if (txt.size()>2) txt+="; ";
                txt+=album;
            }
            txt+=" ]";
        }

        m_labelInfo->setText(txt);

        float el=mpdtools::getElapsedTime();
        char elapsed[1024];
        sprintf(elapsed, "    elapsed: %02d:%02d", (int)floor(el/60), int(el)%60);
        m_labelElapsed->setText(elapsed);

        //std::cout<<"PLAYING "<<txt<<"\n\n";
        rpi_softblink_set_amplitude(LED_PLAY_BUTTON, LED_PLAY_BUTTON_ON_AMPLITUDE);
        rpi_softblink_set_offset(LED_PLAY_BUTTON, LED_PLAY_BUTTON_ON_OFFSET);
    } else {
        m_playState->setImageSymbol(CGSymbol::iPause);
        m_labelName->setText(" ... not playing ...");
        m_labelInfo->setText("");
        m_labelElapsed->setText("    -- / --");
        rpi_softblink_set_amplitude(LED_PLAY_BUTTON, LED_PLAY_BUTTON_OFF_AMPLITUDE);
        rpi_softblink_set_offset(LED_PLAY_BUTTON, LED_PLAY_BUTTON_OFF_OFFSET);
        //std::cout<<"NOT PLAYING\n";
    }
    mpdtools::clearErrors();
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
        std::cout<<"  ROTARY_RADIO_MAIN-turned "<<rot->inc()<<" oldstation="<<m_stationList->currentItem()<<", "<<m_stationList->item(m_stationList->currentItem())<<"\n";
        m_stationList->nextItem(rot->inc());
        std::cout<<"     -> newstation="<<m_stationList->currentItem()<<", "<<m_stationList->item(m_stationList->currentItem())<<"\n";
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

        if (idx>=0 && idx<(long long)m_stationList->count()) {
            m_playingItem=idx;
            CGApplication::getInstance().getINI().put<int>("radio.lastStationIdx", idx);
            CGApplication::getInstance().saveINI();
            std::cout<<"sending URI '"<<m_stationList->itemData(idx).uri<<"' ...\n";
            mpdtools::clearErrors();
            mpd_send_add(mpdtools::getConnection(), m_stationList->itemData(idx).uri.c_str());
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
    std::cout<<"WRRadioScreen::onShow()\n";
    int idx=CGApplication::getInstance().getINI().get<int>("radio.lastStationIdx", 0);
    play(idx);
    m_stationList->setCurrentItem(idx);
    //std::cout<<" idx="<<idx<<"\n";
}

void WRRadioScreen::onHide()
{
    std::cout<<"WRRadioScreen::onHide()\n";
    stop();
}

void WRRadioScreen::addWebradiosFromCONF(const std::string &filename)
{
    if (filename.size()<=0) return;
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
                for (int i=0; i<m_stationList->count(); i++) {
                    if (m_stationList->item(i)==s.name) {
                        m_stationList->setItem(i, s.name, s);
                        found =true;
                        break;
                    }
                }
                if (!found) {
                    //std::cout<<"    adding station '"<<s.name<<"': "<<s.uri<<"\n";
                    m_stationList->addItem(s.name, s);
                    std::cout<<"    adding station '"<<s.name<<"': "<<s.uri<<"\n";//<<" --> "<<m_stations.size()<<"\n";
                } else {
                    std::cout<<"    updated station '"<<s.name<<"': "<<s.uri<<"\n";
                }
            }
        }
        // sort, ascending order, case-insensitive
        m_stationList->sort(true);
    } catch (std::exception& E) {
        std::cout<<"  error: "<<E.what()<<"\n";
    }
    std::cout<<"parsing webradio-stations from '"<<filename<<"' ... DONE!\n";

}


