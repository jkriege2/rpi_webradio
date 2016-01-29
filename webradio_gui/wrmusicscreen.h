#ifndef WRMusicScreen_H
#define WRMusicScreen_H

#include "cgscreen.h"
#include "cgtreewidget.h"
#include "cglayout.h"
#include "cglabel.h"
#include "cgtwostatimage.h"
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
        CGDirectoryTreeWidget* m_musicTree;
        CGImage* m_playState;
        CGLabel* m_label;
        WRMPDDirectoryTreeProvider* m_musicProvider;
        bool m_playing;
        int m_playingItem;

        void stop();
        void play(int index);

        virtual void onShow();
        virtual void onHide();
};

#endif // WRMusicScreen_H
