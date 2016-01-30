#ifndef WRMusicScreen_H
#define WRMusicScreen_H

#include <chrono>
#include "cgscreen.h"
#include "cgtreewidget.h"
#include "cglayout.h"
#include "cglabel.h"
#include "cgtwostatimage.h"
#include "cgprogressbar.h"
#include "global.h"
#include "wrmpddirectorytreeprovider.h"
#include "cgdirectorytreewidget.h"
#include "mpd_tools.h"

/** \brief a screen for music player */
class WRMusicScreen : public CGScreen
{
    public:
        WRMusicScreen(CGWidget* parent=NULL);
        ~WRMusicScreen();

        virtual void paint(cairo_t *c);

        void updateList();
        virtual void event(CGEvent* e);


    protected:
        std::chrono::system_clock::time_point last_paint;
        CGDirectoryTreeWidget* m_musicTree;
        CGImage* m_playState;
        CGLabel* m_labelArtist;
        CGLabel* m_labelTitle;
        CGLabel* m_labelQ;
        CGLabel* m_labelRandom;
        CGLabel* m_labelRepeat;
        CGProgressBar* m_progress;
        WRMPDDirectoryTreeProvider* m_musicProvider;
        bool m_playing;
        int m_lastQueueItem;
        std::vector<mpdtools::DirectoryEntry> m_lastQueue;
        std::string m_lastURI;


        void stop();
        void play(int index);
        void playLast();

        virtual void onShow();
        virtual void onHide();
};

#endif // WRMusicScreen_H
