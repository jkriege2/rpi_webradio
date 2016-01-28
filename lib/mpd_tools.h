#ifndef MPD_TOOLS_H
#define MPD_TOOLS_H

#include <string>
#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <regex>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>
#include <atomic>


class mpdtools {
    public:
        static mpdtools& getInstance();
        /** \brief mutex to get access to the MPD */
        static std::recursive_mutex& getMPDMutex();
        static struct mpd_connection * getConnection();

        /** \brief return \c true, if mpd is playing */
        static bool isPlaying();
        /** \brief elapsed time in seconds */
        static float getElapsedTime();
        /** \brief total time in seconds */
        static float getTotalTime();
        /** \brief get current title */
        static std::string getCurrentTitle();
        /** \brief get current author */
        static std::string getCurrentArtist();
        /** \brief get current name */
        static std::string getCurrentName();
        /** \brief get current song info */
        static std::string getCurrentSongInfo(enum mpd_tag_type type);
        /** \brief check for errors */
        static bool hadError(bool showMessage=true);
        /** \brief clear errors */
        static void clearErrors();

    protected:
        mpdtools();
        ~mpdtools();

        struct mpd_connection *m_conn;
        void freeConn();

        /** \brief mutex to get access to the MPD */
        std::recursive_mutex mpd_mutex;
        /** \brief thread that keeps the MPD-conection alive */
        std::thread* mpd_keepalivethread;
        /** \brief flag to step the thread mpd_keepalivethread */
        std::atomic<bool> mpd_stopthread;
        /** \brief initialize the MPD tools */
        void init();
        /** \brief d-initialize the MPD tools */
        void deinit();
    private:
        static void mpdtools_keepAliveThreadFun(mpdtools *tools);
};
#endif // MPD_TOOLS_H
