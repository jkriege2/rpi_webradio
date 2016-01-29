#include "wrmpddirectorytreeprovider.h"

WRMPDDirectoryTreeProvider::WRMPDDirectoryTreeProvider(const std::string &uri):
{
    cd(uri);
}

WRMPDDirectoryTreeProvider::~WRMPDDirectoryTreeProvider()
{

}

int WRMPDDirectoryTreeProvider::count() const
{
    return m_list.count();
}

int WRMPDDirectoryTreeProvider::level() const
{
    return m_uriSplit.size();
}

std::string WRMPDDirectoryTreeProvider::itemName(int i, const std::string &defaultName) const
{
    if (i<0 || i>=m_list.size()) {
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
    if (i<0 || i>=m_list.size()) {
        return m_list[i].type==mpdtools::EntryType::Directory;
    }
    return false;
}

std::vector<std::string> WRMPDDirectoryTreeProvider::parentNames(int maxLevel, const std::string &defaultItem) const
{
    std::vector<std::string> res;
    for (size_t i=m_uriSplit.size()-1; i>=0; i--) {
        res.push_back(m_uriSplit[i]);
    }
    return res;
}

void WRMPDDirectoryTreeProvider::cd(const std::string &uri)
{
    std::cout<<"WRMPDDirectoryTreeProvider::cd(uri):\n";
    m_uri=uri;
    m_uriSplit.clear();
    std::string c;
    for (size_t i=0; i<uri.size(); i++) {
        if (uri[i]=='/') {
            m_uriSplit.push_back(c);
            c="";
        } else {
            c+=uri[i];
        }
    }
    if (c.size()>0) m_uriSplit.push_back(c);
    m_list=mpdtools::lsLocal(uri);
}

