#include "precomp.h"
#include "wrmpddirectorytreeprovider.h"

WRMPDDirectoryTreeProvider::WRMPDDirectoryTreeProvider(const std::string &uri)
{
    cd(uri);
}

WRMPDDirectoryTreeProvider::~WRMPDDirectoryTreeProvider()
{

}

int WRMPDDirectoryTreeProvider::count() const
{
    return m_list.size();
}

int WRMPDDirectoryTreeProvider::level() const
{
    return m_uriSplit.size();
}

std::string WRMPDDirectoryTreeProvider::itemName(int i, const std::string &defaultName) const
{
    if (i>=0 && i<(long)m_list.size()) {
        return m_list[i].name;
    }
    return defaultName;
}

bool WRMPDDirectoryTreeProvider::upLevel()
{
    if (!hasParent()) return false;
    std::string dir;
    for (size_t i=0; i<m_uriSplit.size()-1; i++) {
        if (dir.size()>0 && dir[dir.size()-1]!='/') dir += '/';
        dir+=m_uriSplit[i];
    }
    cd(dir);
    return true;
}

bool WRMPDDirectoryTreeProvider::downLevel(int i)
{
    if (hasChildren(i)) {
        cd(m_list[i].uri);
        return true;
    }
    return false;
}

bool WRMPDDirectoryTreeProvider::hasParent() const
{
    return m_uriSplit.size()>0;
}

bool WRMPDDirectoryTreeProvider::hasChildren(int i) const
{
    if (i>=0 && i<(long)m_list.size()) {
        return m_list[i].type==mpdtools::EntryType::Directory;
    }
    return false;
}

bool WRMPDDirectoryTreeProvider::isDirectory(int i) const
{
    if (i>=0 && i<(long)m_list.size()) {
        return m_list[i].type==mpdtools::EntryType::Directory;
    }
    return false;
}

bool WRMPDDirectoryTreeProvider::isPlaylist(int i) const
{
    if (i>=0 && i<(long)m_list.size()) {
        return m_list[i].type==mpdtools::EntryType::Playlist;
    }
    return false;
}

std::vector<std::string> WRMPDDirectoryTreeProvider::parentNames(int maxLevel, const std::string &defaultItem) const
{
    std::vector<std::string> res;
    if (m_uriSplit.size()>0) {
        for (int i=m_uriSplit.size()-1; i>=0; i--) {
            //std::cout<<i<<"/"<<m_uriSplit.size()<<": "<<m_uriSplit.at(i)<<"\n";
            if ((long)res.size()<maxLevel || maxLevel<0) res.push_back(m_uriSplit[i]);
        }
    }
    return res;
}

std::string WRMPDDirectoryTreeProvider::uri(int i) const
{
    if (i>=0 && i<(long)m_list.size()) {
        return m_list[i].uri;
    }
    return std::string();
}

void WRMPDDirectoryTreeProvider::cd(const std::string &uri)
{
    //std::cout<<"WRMPDDirectoryTreeProvider::cd("<<uri<<"):\n";
    m_uri=uri;
    m_uriSplit.clear();
    std::string c;
    for (size_t i=0; i<uri.size(); i++) {
        if (uri[i]=='/') {
            if (c.size()>0) m_uriSplit.push_back(c);
            c="";
        } else {
            c+=uri[i];
        }
    }
    if (c.size()>0) m_uriSplit.push_back(c);
    m_list=mpdtools::lsLocal(uri);
    if (m_list.size()>0) {
        for (long i=m_list.size()-1; i>=0; i--) {
            if (m_list[i].type!=mpdtools::EntryType::Playlist && m_list[i].type!=mpdtools::EntryType::Directory && m_list[i].type!=mpdtools::EntryType::Song) {
                m_list.erase(m_list.begin()+i);
            }
        }
    }
    /*for (auto& it: m_list) {
        std::cout<<"  - "<<it.name<<", "<<it.uri<<"\n";
    }
    std::cout<<"WRMPDDirectoryTreeProvider::cd("<<uri<<") ... DONE!\n";*/
    //std::cout<<"WRMPDDirectoryTreeProvider::cd("<<uri<<"): m_list.size="<<m_list.size()<<"\n";
}

void WRMPDDirectoryTreeProvider::update()
{
    cd(m_uri);
}

std::string WRMPDDirectoryTreeProvider::getBaseURI() const
{
    return m_uri;
}

