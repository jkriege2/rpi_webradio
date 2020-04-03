#include "mpd_tools.h"

class mpdtools_functionguard {
    public:
        mpdtools_functionguard(const std::string& msg): msg(msg) {
            std::cout<<msg<<std::endl;
        }
        ~mpdtools_functionguard() {
            std::cout<<msg<<" ... DONE!\n";
        }

    private:
        std::string msg;
};

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
            mpd_response_finish(inst.m_conn);
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
            mpd_response_finish(inst.m_conn);
            return res;
        }
        mpd_response_finish(inst.m_conn);
        return 0;
    }
    return 0;
}

float mpdtools::getElapsedPercent()
{
    return float(getElapsedTime())/float(getTotalTime())*100.0;
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
            mpd_response_finish(inst.m_conn);
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

std::string mpdtools::getCurrentAlbum()
{
    return getCurrentSongInfo(MPD_TAG_ALBUM);
}

std::string mpdtools::getCurrentName()
{
    return getCurrentSongInfo(MPD_TAG_NAME);
}

std::string mpdtools::getCurrentDate()
{
    return getCurrentSongInfo(MPD_TAG_DATE);
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

int mpdtools::getVolume()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return -1;
    struct mpd_status *status = mpd_run_status(inst.m_conn);
    int res=mpd_status_get_volume(status);
    mpd_status_free(status);
    return res;
}

void mpdtools::setVolume(int volume)
{
    if (volume<0) volume=0;
    if (volume>100) volume=100;
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return;
    mpd_run_set_volume(inst.m_conn, volume);
}

bool mpdtools::getRepeat()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return -1;
    struct mpd_status *status = mpd_run_status(inst.m_conn);
    bool res=mpd_status_get_repeat(status);
    mpd_status_free(status);
    return res;

}

void mpdtools::setRepeat(bool val)
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    mpd_run_repeat(inst.m_conn, val);
}

bool mpdtools::getRandom()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return -1;
    struct mpd_status *status = mpd_run_status(inst.m_conn);
    bool res=mpd_status_get_random(status);
    mpd_status_free(status);
    return res;

}

void mpdtools::setRandom(bool val)
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    mpd_run_random(inst.m_conn, val);
}

void mpdtools::clearQueue()
{
    //mpdtools_functionguard guard("mpdtools::clearQueue()");
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    mpd_run_clear(inst.m_conn);
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

void mpdtools::pause(bool pause)
{
    //mpdtools_functionguard guard("mpdtools::pause("+std::to_string(pause)+")");
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        mpd_send_pause(inst.m_conn, pause);
        mpd_response_finish(inst.m_conn);
    }
}

void mpdtools::stop()
{
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        mpd_run_stop(inst.m_conn);
    }
}


std::vector<mpdtools::DirectoryEntry> mpdtools::lsLocal(const std::string& path)
{
    //mpdtools_functionguard guard("mpdtools::lsLocal("+path+")");
    clearErrors();
    std::vector<mpdtools::DirectoryEntry> res;
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return res;
    mpd_send_list_meta(inst.m_conn, path.c_str());
    struct mpd_entity *entity;
    while ((entity = mpd_recv_entity(inst.m_conn)) != NULL) {
        const struct mpd_directory *dir;
        const struct mpd_song *song;
        const struct mpd_playlist *playlist;

        enum mpd_entity_type type = mpd_entity_get_type(entity);
        mpdtools::DirectoryEntry e;
        switch (type) {
            case MPD_ENTITY_TYPE_DIRECTORY:
                dir = mpd_entity_get_directory(entity);
                if (dir) {
                    e.type=mpdtools::EntryType::Directory;
                    e.uri=mpd_directory_get_path(dir);
                    e.name=extractFilename(e.uri);
                    res.push_back(e);
                }
                break;

            case MPD_ENTITY_TYPE_SONG:
                song = mpd_entity_get_song(entity);
                if (song) {
                    e.type=mpdtools::EntryType::Song;
                    e.uri=mpd_song_get_uri(song);
                    const char* c=mpd_song_get_tag(song, MPD_TAG_NAME, 0);
                    if (c) e.name=c;
                    c=mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
                    if (c) e.title=c;
                    c=mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
                    if (c) e.artist=c;
                    e.duration_s=mpd_song_get_duration(song);
                    e.id=mpd_song_get_id(song);
                    e.name=extractFilename(e.uri);
                    res.push_back(e);
                }
                break;

            case MPD_ENTITY_TYPE_PLAYLIST:
                playlist = mpd_entity_get_playlist(entity);
                if (playlist) {
                    e.type=mpdtools::EntryType::Playlist;
                    e.uri=mpd_playlist_get_path(playlist);
                    e.name=extractFilename(e.uri);
                    res.push_back(e);
                }
                break;
            default:
                break;
        }

        mpd_entity_free(entity);
    }
    mpd_response_finish(inst.m_conn);
    return res;
}

std::vector<mpdtools::DirectoryEntry> mpdtools::searchSongs(const std::string &path)
{
    //mpdtools_functionguard guard("mpdtools::searchSongs("+path+")");
    std::vector<DirectoryEntry> list;
    searchSongs(path, list);
    return list;
}

void mpdtools::searchSongs(const std::string &path, std::vector<mpdtools::DirectoryEntry> &list)
{
    //mpdtools_functionguard guard("mpdtools::searchSongs("+path+", list("+std::to_string(list.size())+") )");
    std::vector<mpdtools::DirectoryEntry> listSongs=mpdtools::lsLocal(path);
    for (auto& it: listSongs) {
        if (it.type==mpdtools::EntryType::Song) {
            list.push_back(it);
        }
    }

    for (auto& it: listSongs) {
        if (it.type==mpdtools::EntryType::Directory) {
            searchSongs(it.uri, list);
        }
    }
}
std::vector<mpdtools::DirectoryEntry> mpdtools::lsQueue()
{
    //mpdtools_functionguard guard("mpdtools::lsQueue()");
    clearErrors();
    std::vector<mpdtools::DirectoryEntry> res;
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return res;

    mpd_send_list_queue_meta(inst.m_conn);
    struct mpd_song *song;
    while ((song = mpd_recv_song(inst.m_conn)) != NULL) {
        if (song) {
            mpdtools::DirectoryEntry e;
            e.type=mpdtools::EntryType::Song;
            e.uri=mpd_song_get_uri(song);
            const char* c=mpd_song_get_tag(song, MPD_TAG_NAME, 0);
            if (c) e.name=c;
            c=mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
            if (c) e.title=c;
            c=mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
            if (c) e.artist=c;
            e.duration_s=mpd_song_get_duration(song);
            e.id=mpd_song_get_id(song);
            e.name=extractFilename(e.uri);
            res.push_back(e);
        }
        mpd_song_free(song);
    }
    mpd_response_finish(inst.m_conn);
    return res;
}

void mpdtools::addSongToQueue(const std::string &uri)
{
    //mpdtools_functionguard guard("mpdtools::addSongToQueue("+uri+")");
    mpdtools::DirectoryEntry e;
    e.uri=uri;
    e.type=mpdtools::EntryType::Song;
    std::vector<mpdtools::DirectoryEntry> list;
    list.push_back(e);
    addToQueue(list);
}

void mpdtools::addToQueue(const std::vector<mpdtools::DirectoryEntry> &urilist)
{
    //mpdtools_functionguard guard("mpdtools::addSongToQueue("+std::to_string(urilist.size())+")");
    clearErrors();
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return ;
    mpd_command_list_begin(inst.m_conn, false);
    for (auto& it: urilist) {
        mpd_send_add(inst.m_conn, it.uri.c_str());
    }
    mpd_command_list_end(inst.m_conn);
    mpd_response_finish(inst.m_conn);
}


void mpdtools::loadPlaylist(const std::string &playlist)
{
    clearErrors();
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (!inst.m_conn) return ;
    mpd_run_load(inst.m_conn, playlist.c_str());
}

int mpdtools::getCurrentQueuePosition()
{
    //mpdtools_functionguard guard("mpdtools::getCurrentQueuePosition()");
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        struct mpd_status * status;
        mpd_send_status(inst.m_conn);
        if ((status = mpd_recv_status(inst.m_conn))!=NULL) {
            int res= mpd_status_get_song_pos(status);
            mpd_response_finish(inst.m_conn);
            mpd_status_free(status);
            mpd_response_finish(inst.m_conn);
            return res;
        }
        mpd_response_finish(inst.m_conn);
        return -1;
    }
    return -1;
}

int mpdtools::getQueueLength()
{
    //mpdtools_functionguard guard("mpdtools::getQueueLength()");
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        struct mpd_status * status;
        mpd_send_status(inst.m_conn);
        if ((status = mpd_recv_status(inst.m_conn))!=NULL) {
            int res= mpd_status_get_queue_length(status);
            mpd_response_finish(inst.m_conn);
            mpd_status_free(status);
            mpd_response_finish(inst.m_conn);
            return res;
        }
        mpd_response_finish(inst.m_conn);
        return -1;
    }
    return -1;
}

void mpdtools::play(int idx)
{
    //mpdtools_functionguard guard("mpdtools::play("+std::to_string(idx)+")");
    clearErrors();
    mpdtools& inst=getInstance();
    std::lock_guard<std::recursive_mutex> lock(inst.mpd_mutex);
    if (inst.m_conn) {
        if (idx<0) {
            mpd_run_play(inst.m_conn);
        } else {
            mpd_run_play_pos(inst.m_conn, idx);
        }
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

std::string mpdtools::extractFilename(const std::string &s)
{
    std::string res;
    auto p=s.find_last_of('/');
    if (p==std::string::npos) {
        return s;
    } else {
        return s.substr(p+1);
    }
    return s;
}




mpdtools::DirectoryEntry::DirectoryEntry():
    type(mpdtools::EntryType::UNKNOWN),
    duration_s(0)
{

}

std::string mpdtools::DirectoryEntry::typeAsShortString() const
{
    switch(type) {
        case mpdtools::EntryType::Song:
            return "SONG";
        case mpdtools::EntryType::Directory:
            return "DIR ";
        case mpdtools::EntryType::Playlist:
            return "PLST";
        case mpdtools::EntryType::UNKNOWN:
            return "UNKN";
    }
    return "UNKN";
}


std::string mpdtools::DirectoryEntry::typeAsString() const
{
    switch(type) {
        case mpdtools::EntryType::Song:
            return "SONG";
        case mpdtools::EntryType::Directory:
            return "DIRECTORY";
        case mpdtools::EntryType::Playlist:
            return "PLAYLIST";
        case mpdtools::EntryType::UNKNOWN:
            return "UNKNOWN";
    }
    return "UNKOWN";
}
