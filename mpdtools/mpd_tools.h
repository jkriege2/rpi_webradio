#ifndef MPD_TOOLS_H
#define MPD_TOOLS_H

#include <string>
#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/song.h>
#include <mpd/directory.h>
#include <mpd/playlist.h>
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
        /** \brief elapsed time in percent of total length */
        static float getElapsedPercent();
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
        /** \brie return the current volume */
        static int getVolume();
        /** \brief set the volume */
        static void setVolume(int volume);
        /** \brie return the repeat-state */
        static bool getRepeat();
        /** \brief set the repeat-state */
        static void setRepeat(bool val);
        /** \brie return the Random-state */
        static bool getRandom();
        /** \brief set the Random-state */
        static void setRandom(bool val);
        /** \brief check for errors */
        static bool hadError(bool showMessage=true);
        /** \brief clear errors */
        static void clearErrors();
        /** \brief pause playback */
        static void pause(bool pause=true);

        enum class EntryType {
            Song,
            Directory,
            Playlist,
            UNKNOWN
        };

        struct DirectoryEntry {
            DirectoryEntry();
            EntryType type;
            std::string typeAsShortString() const;
            std::string typeAsString() const;
            std::string name;
            std::string title;
            std::string uri;
            std::string artist;
            std::string id;
            float duration_s;
        };

        /** \brief list directory (non-recursive) */
        static std::vector<DirectoryEntry> lsLocal(const std::string &path);
        /** \brief find all songs in (and below) directory */
        static std::vector<DirectoryEntry> searchSongs(const std::string &path);
        /** \brief list the current queue */
        static std::vector<DirectoryEntry> lsQueue();
        /** \brief clear the current queue */
        static void clearQueue();
        /** \brief add song to queue */
        static void addSongToQueue(const std::string& uri);
        /** \brief add song to queue */
        static void addToQueue(const std::vector<DirectoryEntry>& urilist);
        /** \brief return the number of the currently played song in the queue (or -1) */
        static int getCurrentQueuePosition();
        /** \brief return the length of the queue */
        static int getQueueLength();
        /** \brief play the i-th song in the queue */
        static void play(int idx=0);
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
        static std::string extractFilename(const std::string& s);
        static void searchSongs(const std::string &path, std::vector<DirectoryEntry>& list);
    private:
        static void mpdtools_keepAliveThreadFun(mpdtools *tools);
};
#endif // MPD_TOOLS_H
