#include "wrmusicscreen.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "mpd_tools.h"
#include "cgapplication.h"

WRMusicScreen::WRMusicScreen(CGWidget *parent):
    CGScreen(parent)
{
    m_playingItem=-1;
    //std::cout<<"WRMusicScreen::paint size="<<size()<<"\n";
    //setBackgroundColor(CGColor::ccDarkgray);
    CGLinearLayout* vlay=new CGLinearLayout(this, cgdVertical);
    setLayout(vlay);


    m_musicTree=new CGDirectoryTreeWidget(this);
    m_musicProvider=new WRMPDDirectoryTreeProvider();
    m_musicTree->setProvider(m_musicProvider, true);

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

    vlay->addWidget(m_musicTree, -4);
    vlay->addWidget(wibhlay, -1);
    hlay->layoutWidgets();
    vlay->layoutWidgets();

    m_playing=mpdtools::isPlaying();
}

WRMusicScreen::~WRMusicScreen()
{
    stop();
}

void WRMusicScreen::paint(cairo_t *c)
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
    //std::cout<<"WRMusicScreen::paint size="<<size()<<"\n";
}

void WRMusicScreen::event(CGEvent *e)
{
    CGButtonClickedEvent* clk=dynamic_cast<CGButtonClickedEvent*>(e);
    CGInputScroll* rot=dynamic_cast<CGInputScroll*>(e);
    std::cout<<"WRMusicScreen::event: "<<e->toString()<<", "<<clk<<", "<<rot<<"\n";
    if (clk && clk->button()==BTN_MUSIC_ENTER) {
        std::cout<<"  BTN_MUSIC_ENTER-clicked playing="<<m_playing<<" m_playingItem="<<m_playingItem<<"\n";
        if (m_musicProvider->isDirectory(m_musicTree->currentItem())) {
            m_musicTree->downLevel();
        } else {
            mpdtools::clearQueue();
            mpdtools::addSongToQueue(m_musicProvider->uri(m_musicTree->currentItem()));
            mpdtools::play(0);
        }
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_PLAY) {
        std::cout<<"  BTN_MUSIC_PLAY-clicked playing="<<m_playing<<" m_playingItem="<<m_playingItem<<"\n";

        if (m_musicProvider->isDirectory(m_musicTree->currentItem())) {
            mpdtools::clearQueue();
            mpdtools::addToQueue(mpdtools::searchSongs(m_musicProvider->uri(m_musicTree->currentItem())));
            mpdtools::play(0);
        } else {
            mpdtools::clearQueue();
            mpdtools::addSongToQueue(m_musicProvider->uri(m_musicTree->currentItem()));
            mpdtools::play(0);
        }
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_BACK) {
        std::cout<<"  BTN_MUSIC_BACK-clicked\n";
        m_musicTree->upLevel();
        clk->accept();
    } else if (rot && rot->id()==ROTARY_MUSIC_MAIN) {
        std::cout<<"  ROTARY_MUSIC_MAIN-turned "<<rot->inc()<<"\n";
        m_musicTree->nextItem(rot->inc());
        rot->accept();
    } else {
        CGScreen::event(e);
    }
}

void WRMusicScreen::stop()
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

void WRMusicScreen::play(int idx)
{

}

void WRMusicScreen::onShow()
{
}

void WRMusicScreen::onHide()
{
    stop();
}

void WRMusicScreen::updateList()
{
}

