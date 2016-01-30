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
    m_lastQueueItem=-1;
    last_paint = std::chrono::system_clock::now();
    //std::cout<<"WRMusicScreen::paint size="<<size()<<"\n";
    //setBackgroundColor(CGColor::ccDarkgray);
    CGLinearLayout* vlay=new CGLinearLayout(this, cgdVertical);
    setLayout(vlay);


    m_musicTree=new CGDirectoryTreeWidget(this);
    m_musicProvider=new WRMPDDirectoryTreeProvider();
    m_musicTree->setProvider(m_musicProvider, true);

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

    m_labelArtist=new CGLabel(0,0,24,9,wibvlayt);
    m_labelArtist->setText("line 1 ...");
    m_labelArtist->setFontSize(12);
    //m_label1->setBackgroundColor(CGColor::ccGray50);
    m_labelTitle=new CGLabel(0,0,24,14,wibvlayt);
    m_labelTitle->setText("line 2 ...");
    m_labelTitle->setFontSize(14);
    m_labelTitle->setBold(true);
    //m_label2->setBackgroundColor(CGColor::ccGray25);


    CGWidget* wibhlayQ=new CGWidget(wibvlayt);
    //wibhlay->setFrameColor(CGColor("blue"));
    CGLinearLayout* hlayQ=new CGLinearLayout(wibhlayQ, cgdHorizontal);
    wibhlayQ->setLayout(hlayQ);

    m_labelQ=new CGLabel(0,0,12,10,wibhlayQ);
    m_labelQ->setText("0/0");
    m_labelQ->setFontSize(9);
    m_progress=new CGProgressBar(0,0,24,10, wibhlayQ);
    m_progress->setFontSize(9);
    hlayQ->addWidget(m_labelQ, -2);
    hlayQ->addWidget(m_progress, -8);

    vlayt->addWidget(m_labelArtist, -12);
    vlayt->addWidget(m_labelTitle, -14);
    vlayt->addWidget(wibhlayQ, -8);
    vlayt->addWidget(new CGWidget(wibvlayt), -3);

    hlay->addWidget(m_playState, -5);
    hlay->addWidget(new CGWidget(wibhlay), -1);
    hlay->addWidget(wibvlayt, -25);

    vlay->addWidget(m_musicTree, -3);
    vlay->addWidget(wibhlay, -1); // 1/5 2/10 4/20

    hlayQ->layoutWidgets();
    hlay->layoutWidgets();
    vlayt->layoutWidgets();
    hlayQ->layoutWidgets();
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

    std::chrono::system_clock::time_point n = std::chrono::system_clock::now();
    if ((n-last_paint).count()>1) {
        last_paint=n;
        m_musicProvider->update();
    }
    if ((m_playing=mpdtools::isPlaying())) {
        m_playState->setImageSymbol(CGSymbol::iPlayAnimated);
        mpdtools::clearErrors();
        char elapsed[128];
        char queue[128];
        mpdtools::clearErrors();
        float el=mpdtools::getElapsedTime();
        float tot=mpdtools::getTotalTime();
        mpdtools::hadError(true);
        sprintf(elapsed, "%02d:%02d / %02d:%02d", (int)floor(el/60), int(el)%60, (int)floor(tot/60), int(tot)%60);
        sprintf(queue, "#%d / %d", mpdtools::getCurrentQueuePosition()+1, mpdtools::getQueueLength());
        std::string artist=mpdtools::getCurrentArtist();
        std::string album=mpdtools::getCurrentAlbum();
        if (album.size()>0) {
            if (artist.size()>0) artist += " / ";
            artist+=album;
        }
        m_labelArtist->setText(artist);
        std::string txt=mpdtools::getCurrentTitle();
        mpdtools::clearErrors();
        if (txt.size()==0) txt=mpdtools::getCurrentName();
        if (txt.size()==0) txt="???";
        mpdtools::clearErrors();
        m_labelTitle->setText(txt);
        m_labelQ->setText(queue);
        m_progress->setRange(0,100);
        m_progress->setValue(mpdtools::getElapsedPercent());
        m_progress->setUserText(elapsed, true);
    } else {
        m_playState->setImageSymbol(CGSymbol::iPause);
        m_labelArtist->setText("---");
        m_labelTitle->setText(" ... not playing ...");
        m_progress->setRange(0,100);
        m_progress->setValue(0);
        //std::cout<<"m_label1:   "<<m_labelArtist->absX()<<", "<<m_labelArtist->absY()<<" ; "<<m_labelArtist->width()<<", "<<m_labelArtist->height()<<" / "<<m_labelArtist->parent()->absX()<<", "<<m_labelArtist->parent()->absY()<<" ; "<<m_labelArtist->parent()->width()<<", "<<m_labelArtist->parent()->height()<<"\n";
        //std::cout<<"m_label2:   "<<m_labelTitle->absX()<<", "<<m_labelTitle->absY()<<" ; "<<m_labelTitle->width()<<", "<<m_labelTitle->height()<<" / "<<m_labelTitle->parent()->absX()<<", "<<m_labelTitle->parent()->absY()<<" ; "<<m_labelTitle->parent()->width()<<", "<<m_labelTitle->parent()->height()<<"\n";
        //std::cout<<"m_labelQ:   "<<m_labelQ->absX()<<", "<<m_labelQ->absY()<<" ; "<<m_labelQ->width()<<", "<<m_labelQ->height()<<" / "<<m_labelQ->parent()->absX()<<", "<<m_labelQ->parent()->absY()<<" ; "<<m_labelQ->parent()->width()<<", "<<m_labelQ->parent()->height()<<"\n";
        //std::cout<<"m_progress: "<<m_progress->absX()<<", "<<m_progress->absY()<<" ; "<<m_progress->width()<<", "<<m_progress->height()<<" / "<<m_progress->parent()->absX()<<", "<<m_progress->parent()->absY()<<" ; "<<m_progress->parent()->width()<<", "<<m_progress->parent()->height()<<"\n";

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
        std::cout<<"  BTN_MUSIC_ENTER-clicked playing="<<m_playing<<"\n";
        if (m_musicProvider->isDirectory(m_musicTree->currentItem())) {
            m_musicTree->downLevel();
        } else {
            mpdtools::clearQueue();
            mpdtools::addSongToQueue(m_musicProvider->uri(m_musicTree->currentItem()));
            mpdtools::play(0);
        }
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_PLAY) {
        std::cout<<"  BTN_MUSIC_PLAY-clicked playing="<<m_playing<<"\n";

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
    m_lastQueueItem=mpdtools::getCurrentQueuePosition();
    std::cout<<"stopping ... m_lastQueueItem="<<m_lastQueueItem<<"\n";
    mpdtools::stop();
    mpdtools::clearErrors();
    m_playing=mpdtools::isPlaying();
}

void WRMusicScreen::onShow()
{
    std::cout<<"WRMusicScreen::onShow()\n";
    if (m_lastQueueItem>=0 && m_lastQueueItem<mpdtools::getQueueLength()) {
        std::cout<<"playing ... m_lastQueueItem="<<m_lastQueueItem<<"\n";
        mpdtools::play(m_lastQueueItem);
        mpdtools::clearErrors();
        m_playing=mpdtools::isPlaying();
    }
}

void WRMusicScreen::onHide()
{
    std::cout<<"WRMusicScreen::onShow()\n";
    stop();
}

void WRMusicScreen::updateList()
{
}

