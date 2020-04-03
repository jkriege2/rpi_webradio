
#include <string>
#include <iostream>
#include "mpd_tools.h"

void listDir(const std::string& dir, int level=0, int levelMax=-1) {
    if (levelMax>=0 && level>levelMax) return;
    std::string start(2+level*2, ' ');
    std::vector<mpdtools::DirectoryEntry> list=mpdtools::lsLocal(dir);
    for (auto& it: list) {
        if (it.type==mpdtools::EntryType::Directory) {
            std::cout<<start<<"- "<<it.typeAsShortString()<<": '"<<it.name<<"' "<<it.uri<<"\n";
            listDir(it.uri, level+1, levelMax);
        }
    }
    for (auto& it: list) {
        if (it.type!=mpdtools::EntryType::Directory) {
            std::cout<<start<<"- "<<it.typeAsShortString()<<": '"<<it.name<<"' "<<it.uri<<" [ID="<<it.id<<"]\n";
        }
    }
}

int main(int argc, char *argv[])
{
    mpdtools& inst=mpdtools::getInstance();
    std::cout<<"\n\n\n====================================================================\n";
    std::cout<<"ls(\"\", levelMax=3):\n";
    listDir("", 0, 2);
    std::cout<<"\n\n\n====================================================================\n";
    std::cout<<"currentSong:                                "<<inst.getCurrentQueuePosition()+1<<"/"<<inst.getQueueLength()<<"\n";
    inst.play(0);
    std::cout<<"currentSong:                                "<<inst.getCurrentQueuePosition()+1<<"/"<<inst.getQueueLength()<<"\n";
    inst.play(3);
    std::cout<<"currentSong:                                "<<inst.getCurrentQueuePosition()+1<<"/"<<inst.getQueueLength()<<"\n";
    std::cout<<"isPlaying:                                  "<<inst.isPlaying()<<"\n";
    std::cout<<"Random:                                     "<<inst.getRandom()<<"\n";
    std::cout<<"Repeat:                                     "<<inst.getRepeat()<<"\n";
    std::cout<<"Volume:                                     "<<inst.getVolume()<<"%\n";
    std::cout<<"getElapsedPercent:                          "<<inst.getElapsedPercent()<<"%\n";
    std::cout<<"getElapsedTime:                             "<<inst.getElapsedTime()<<"s\n";
    std::cout<<"getTotalTime:                               "<<inst.getTotalTime()<<"s\n";
    std::cout<<"getCurrentTitle:                            "<<inst.getCurrentTitle()<<"\n";
    std::cout<<"getCurrentArtist:                           "<<inst.getCurrentArtist()<<"\n";
    std::cout<<"getCurrentName:                             "<<inst.getCurrentName()<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_ALBUM):          "<<inst.getCurrentSongInfo(MPD_TAG_ALBUM )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_TRACK):          "<<inst.getCurrentSongInfo(MPD_TAG_TRACK )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_NAME):           "<<inst.getCurrentSongInfo(MPD_TAG_NAME )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_GENRE):          "<<inst.getCurrentSongInfo(MPD_TAG_GENRE )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_DATE):           "<<inst.getCurrentSongInfo(MPD_TAG_DATE )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_COMPOSER ):      "<<inst.getCurrentSongInfo(MPD_TAG_COMPOSER  )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_PERFORMER):      "<<inst.getCurrentSongInfo(MPD_TAG_PERFORMER )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_DISC):           "<<inst.getCurrentSongInfo(MPD_TAG_DISC )<<"\n";
    std::cout<<"getCurrentSongInfo(MPD_TAG_ALBUM_ARTIST ):  "<<inst.getCurrentSongInfo(MPD_TAG_ALBUM_ARTIST  )<<"\n";
    std::cout<<"\n\n\n====================================================================\n";
    std::vector<mpdtools::DirectoryEntry> queue=mpdtools::lsQueue();
    std::cout<<"lsQueue():\n";
    for (auto& it: queue) {
        std::cout<<"  - "<<it.typeAsShortString()<<": '"<<it.name<<"' "<<it.uri<<" [ID="<<it.id<<"]\n";
    }
    std::cout<<"\n\n\n====================================================================\n";
    return EXIT_SUCCESS;
}




