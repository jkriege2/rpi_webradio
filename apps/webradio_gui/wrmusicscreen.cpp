#include "precomp.h"
#include "wrmusicscreen.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "rpi_tools.h"
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

    m_labelArtist=new CGMarqueeLabel(0,0,24,9,wibvlayt);
    m_labelArtist->setText("line 1 ...");
    m_labelArtist->setFontSize(12);
    //m_label1->setBackgroundColor(CGColor::ccGray50);
    m_labelTitle=new CGMarqueeLabel(0,0,24,14,wibvlayt);
    m_labelTitle->setText("line 2 ...");
    m_labelTitle->setFontSize(14);
    m_labelTitle->setBold(true);
    //m_label2->setBackgroundColor(CGColor::ccGray25);


    CGWidget* wibhlayQ=new CGWidget(0,0,width()-32, 24, wibvlayt);
    //wibhlay->setFrameColor(CGColor("blue"));
    CGLinearLayout* hlayQ=new CGLinearLayout(wibhlayQ, cgdHorizontal);
    wibhlayQ->setLayout(hlayQ);

    m_labelQ=new CGLabel(0,0,12,10,wibhlayQ);
    m_labelQ->setText("0/0");
    m_labelQ->setFontSize(9);
    m_progress=new CGProgressBar(0,0,24,10, wibhlayQ);
    m_progress->setFontSize(9);
    m_labelRandom=new CGLabel(0,0,20,12,wibhlayQ);
    m_labelRandom->setText(" R");//\xE2\xA4\xA8"); // \x2931 \x2928
    m_labelRandom->setFontSize(12);
    m_labelRandom->setTextColor(CGColor::ccGray25);
    m_labelRepeat=new CGLabel(0,0,20,12,wibhlayQ);
    m_labelRepeat->setText(" \xE2\x86\xBB");//\x21BB
    m_labelRepeat->setFontSize(14);
    m_labelRepeat->setTextColor(CGColor::ccGray25);
    hlayQ->addWidget(m_labelQ, -3);
    hlayQ->addWidget(m_progress, -8);
    hlayQ->addWidget(m_labelRandom, -2);
    hlayQ->addWidget(m_labelRepeat, -2);

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
    onHide();
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
        sprintf(queue, "# %d / %d", mpdtools::getCurrentQueuePosition()+1, mpdtools::getQueueLength());
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
        rpi_softblink_set_amplitude(LED_PLAY_BUTTON, LED_PLAY_BUTTON_ON_AMPLITUDE);
        rpi_softblink_set_offset(LED_PLAY_BUTTON, LED_PLAY_BUTTON_ON_OFFSET);
    } else {
        m_playState->setImageSymbol(CGSymbol::iPause);
        m_labelArtist->setText("---");
        m_labelTitle->setText(" ... not playing ...");
        m_progress->setRange(0,100);
        m_progress->setValue(0);
        m_progress->setUserText("", true);
        m_labelQ->setText("--/--");
        //std::cout<<"m_label1:   "<<m_labelArtist->absX()<<", "<<m_labelArtist->absY()<<" ; "<<m_labelArtist->width()<<", "<<m_labelArtist->height()<<" / "<<m_labelArtist->parent()->absX()<<", "<<m_labelArtist->parent()->absY()<<" ; "<<m_labelArtist->parent()->width()<<", "<<m_labelArtist->parent()->height()<<"\n";
        //std::cout<<"m_label2:   "<<m_labelTitle->absX()<<", "<<m_labelTitle->absY()<<" ; "<<m_labelTitle->width()<<", "<<m_labelTitle->height()<<" / "<<m_labelTitle->parent()->absX()<<", "<<m_labelTitle->parent()->absY()<<" ; "<<m_labelTitle->parent()->width()<<", "<<m_labelTitle->parent()->height()<<"\n";
        //std::cout<<"m_labelQ:   "<<m_labelQ->absX()<<", "<<m_labelQ->absY()<<" ; "<<m_labelQ->width()<<", "<<m_labelQ->height()<<" / "<<m_labelQ->parent()->absX()<<", "<<m_labelQ->parent()->absY()<<" ; "<<m_labelQ->parent()->width()<<", "<<m_labelQ->parent()->height()<<"\n";
        //std::cout<<"m_progress: "<<m_progress->absX()<<", "<<m_progress->absY()<<" ; "<<m_progress->width()<<", "<<m_progress->height()<<" / "<<m_progress->parent()->absX()<<", "<<m_progress->parent()->absY()<<" ; "<<m_progress->parent()->width()<<", "<<m_progress->parent()->height()<<"\n";
        rpi_softblink_set_amplitude(LED_PLAY_BUTTON, LED_PLAY_BUTTON_OFF_AMPLITUDE);
        rpi_softblink_set_offset(LED_PLAY_BUTTON, LED_PLAY_BUTTON_OFF_OFFSET);

    }
    if (mpdtools::getRandom()) m_labelRandom->setTextColor(CGColor::ccWhite);
    else  m_labelRandom->setTextColor(CGColor::ccGray10);
    if (mpdtools::getRepeat()) m_labelRepeat->setTextColor(CGColor::ccWhite);
    else  m_labelRepeat->setTextColor(CGColor::ccGray10);

    CGScreen::paint(c);
    //std::cout<<"WRMusicScreen::paint size="<<size()<<"\n";
}

void WRMusicScreen::event(CGEvent *e)
{
    CGButtonClickedEvent* clk=dynamic_cast<CGButtonClickedEvent*>(e);
    CGInputScroll* rot=dynamic_cast<CGInputScroll*>(e);
    std::cout<<"WRMusicScreen::event: "<<e->toString()<<", "<<clk<<", "<<rot<<"\n";
    if (clk && clk->button()==BTN_MUSIC_ENTER) {
        std::cout<<"  BTN_MUSIC_ENTER-clicked playing="<<m_playing<<"\n";
        if (m_musicProvider->hasChildren(m_musicTree->currentItem())) {
            m_musicTree->downLevel();
        } else {
            play(m_musicTree->currentItem());
        }
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_PLAY) {
        std::cout<<"  BTN_MUSIC_PLAY-clicked playing="<<m_playing<<"\n";
        play(m_musicTree->currentItem());
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_BACK) {
        std::cout<<"  BTN_MUSIC_BACK-clicked\n";
        m_musicTree->upLevel();
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_Q_NEXT) {
        std::cout<<"  BTN_MUSIC_Q_NEXT-clicked\n";
        int curr=mpdtools::getCurrentQueuePosition();
        int len=mpdtools::getQueueLength();
        if (curr+1<len) {
            mpdtools::play(curr+1);
        }
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_Q_PREV) {
        std::cout<<"  BTN_MUSIC_Q_PREV-clicked\n";
        int curr=mpdtools::getCurrentQueuePosition();
        if (curr-1>=0) {
            mpdtools::play(curr-1);
        }
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_RANDOM) {
        std::cout<<"  BTN_MUSIC_RANDOM-clicked\n";
        bool curr=mpdtools::getRandom();
        mpdtools::setRandom(!curr);
        clk->accept();
    } else if (clk && clk->button()==BTN_MUSIC_REPEAT) {
        std::cout<<"  BTN_MUSIC_REPEAT-clicked\n";
        bool curr=mpdtools::getRepeat();
        mpdtools::setRepeat(!curr);
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
    m_lastQueue=mpdtools::lsQueue();
    m_lastQueueItem=mpdtools::getCurrentQueuePosition();
    std::cout<<"stopping ... m_lastQueueItem="<<m_lastQueueItem<<"\n";
    mpdtools::stop();
    mpdtools::clearErrors();
    m_playing=mpdtools::isPlaying();
}

void WRMusicScreen::play(int index)
{
    mpdtools::clearQueue();
    std::string uri=m_musicProvider->uri(index);
    int qsize=mpdtools::getQueueLength();
    if (m_lastURI==uri && qsize>0) {
        if (mpdtools::isPlaying()) {
            stop();
        } else {
            playLast();
        }
    } else {
        m_lastURI=uri;
        if (m_musicProvider->isDirectory(index)) {
            mpdtools::addToQueue(mpdtools::searchSongs(uri));
        } else if (m_musicProvider->isPlaylist(index)) {
            mpdtools::loadPlaylist(uri);
        } else {
            mpdtools::addSongToQueue(uri);
        }
        mpdtools::play(0);
    }
}

void WRMusicScreen::playLast()
{
    if (m_lastQueueItem>=0 && m_lastQueueItem<(long)m_lastQueue.size()) {
        mpdtools::play(m_lastQueueItem);
    } else {
        mpdtools::play(m_lastQueueItem=0);
    }
}

void WRMusicScreen::onShow()
{
    std::cout<<"WRMusicScreen::onShow()\n";
    mpdtools::stop();
    mpdtools::clearQueue();
    if (m_lastQueue.size()>0) {
        std::cout<<"playing ... m_lastQueueItem="<<m_lastQueueItem<<"\n";
        mpdtools::addToQueue(m_lastQueue);
        playLast();
    } else {
        m_musicProvider->cd(CGApplication::getInstance().getINI().get<std::string>("music.lastBaseURI", ""));
        m_musicTree->setCurrentItem(CGApplication::getInstance().getINI().get<int>("music.lastTreeIndex", 0));
    }
    mpdtools::clearErrors();
    m_playing=mpdtools::isPlaying();
}

void WRMusicScreen::onHide()
{
    std::cout<<"WRMusicScreen::onHide()\n";
    CGApplication::getInstance().getINI().put<std::string>("music.lastBaseURI", m_musicProvider->getBaseURI());
    CGApplication::getInstance().getINI().put<int>("music.lastTreeIndex", m_musicTree->currentItem());
    CGApplication::getInstance().saveINI();
    stop();
}

void WRMusicScreen::updateList()
{
}

