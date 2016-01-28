#include "mpd_tools.h"

mpdtools::mpdtools():
    m_conn(NULL),
    mpd_keepalivethread(NULL),
    mpd_stopthread(false)
{
    init();
}

mpdtools::~mpdtools()
{
    deinit();
}

void mpdtools::freeConn()
{
    std::lock_guard<std::recursive_mutex> lock(mpd_mutex);
    if (m_conn) {
        mpd_connection_free(m_conn);
        m_conn=NULL;
        std::cout<<"connection to mpd-server closed ...\n";
    }
}

mpdtools &mpdtools::getInstance()
{
    static mpdtools tools;
    return tools;
}

std::recursive_mutex &mpdtools::getMPDMutex()
{
    return getInstance().mpd_mutex;
}

mpd_connection *mpdtools::getConnection()
{
    return getInstance().m_conn;
}

bool mpdtools::isPlaying()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        struct mpd_status * status;
        mpd_send_status(inst.m_conn);
        if ((status = mpd_recv_status(inst.m_conn))!=NULL) {
            bool res= mpd_status_get_state(status) == MPD_STATE_PLAY;
            mpd_response_finish(inst.m_conn);
            mpd_status_free(status);
            return res;
        }
        mpd_response_finish(inst.m_conn);
        return false;
    }
    return false;
}

float mpdtools::getElapsedTime()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        struct mpd_status * status;
        mpd_send_status(inst.m_conn);
        if ((status = mpd_recv_status(inst.m_conn))!=NULL) {
            float res= mpd_status_get_elapsed_time(status);
            mpd_response_finish(inst.m_conn);
            mpd_status_free(status);
            return res;
        }
        mpd_response_finish(inst.m_conn);
        return 0;
    }
    return 0;
}

float mpdtools::getTotalTime()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        struct mpd_status * status;
        mpd_send_status(inst.m_conn);
        if ((status = mpd_recv_status(inst.m_conn))!=NULL) {
            float res= mpd_status_get_total_time(status);
            mpd_response_finish(inst.m_conn);
            mpd_status_free(status);
            return res;
        }
        mpd_response_finish(inst.m_conn);
        return 0;
    }
    return 0;
}

std::string mpdtools::getCurrentTitle()
{
    return getCurrentSongInfo(MPD_TAG_TITLE);
}

std::string mpdtools::getCurrentArtist()
{
    return getCurrentSongInfo(MPD_TAG_ARTIST);
}

std::string mpdtools::getCurrentName()
{
    return getCurrentSongInfo(MPD_TAG_NAME);
}

std::string mpdtools::getCurrentSongInfo(mpd_tag_type type)
{
    std::string res;
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        struct mpd_song * song;
        mpd_send_current_song(inst.m_conn);
        if ((song = mpd_recv_song(inst.m_conn))!=NULL) {
            const char *value;
            int i=0;
            while ((value = mpd_song_get_tag(song, type, i++)) != NULL) {
                res+=value;
            }
        }
        mpd_response_finish(inst.m_conn);
        if (song) mpd_song_free(song);
    }
    return res;
}

bool mpdtools::hadError(bool showMessage)
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        mpd_error err=mpd_connection_get_error(inst.m_conn);
        if (err!=MPD_ERROR_SUCCESS) {
            if (showMessage) std::cout<<"libmpdclient: error: "<<mpd_connection_get_error_message(inst.m_conn)<<"\n";
            return true;
        }
    }
    return false;
}

void mpdtools::clearErrors()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        mpd_connection_clear_error(inst.m_conn);
    }
}

void mpdtools::mpdtools_keepAliveThreadFun(mpdtools* tools) {
    bool done=false;
    while(!done) {
        {
            std::lock_guard<std::recursive_mutex> lock(tools->mpd_mutex);
            if (tools->m_conn) {
                mpd_error err=mpd_connection_get_error(tools->m_conn);
                if (err==MPD_ERROR_CLOSED || err==MPD_ERROR_RESOLVER || err==MPD_ERROR_SYSTEM || err==MPD_ERROR_OOM) {
                    std::cout<<"libmpdclient: error: "<<mpd_connection_get_error_message(tools->m_conn)<<"\n";
                    tools->freeConn();
                }
            } else {
                std::cout<<"initializing libmpdclient ... connecting to mpd-server\n";
                tools->m_conn = mpd_connection_new(NULL, 0, 6600);
                if (mpd_connection_get_error(tools->m_conn) != MPD_ERROR_SUCCESS) {
                    std::cout<<"error initializing libmpdclient: "<<mpd_connection_get_error_message(tools->m_conn)<<"\n";
                    tools->freeConn();
                } else {
                    auto version=mpd_connection_get_server_version(tools->m_conn);
                    std::cout<<"  mpd-server version: "<<version[0]<<"."<<version[1]<<"."<<version[2]<<"\n";
                    std::cout<<"initializing libmpdclient ... connected to mpd-server\n";
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (tools->mpd_stopthread.load()) done=true;
    }
    tools->freeConn();
}

void mpdtools::init()
{
    std::cout<<"initializing libmpdclient ...\n";
    if (!mpd_keepalivethread) {
        std::lock_guard<std::recursive_mutex> lock(mpd_mutex);
        std::cout<<"initializing libmpdclient ... starting keep-alive thread\n";
        mpd_keepalivethread=new std::thread(
                                std::bind(
                                    mpdtools::mpdtools_keepAliveThreadFun, this)
                                );
        std::cout<<"initializing libmpdclient ... started keep-alive thread\n";




    }
    std::cout<<"initializing libmpdclient ... OK!\n";
}

void mpdtools::deinit()
{
    if (mpd_keepalivethread) {
        std::cout<<"deinitializing libmpdclient ... \n";
        mpd_stopthread=true;
        mpd_keepalivethread->join();

        delete mpd_keepalivethread;
        mpd_keepalivethread=NULL;
        std::cout<<"deinitializing libmpdclient ... OK!\n";
    }
}


