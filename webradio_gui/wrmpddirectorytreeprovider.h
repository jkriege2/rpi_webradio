#ifndef WRMPDDIRECTORYTREEPROVIDER_H
#define WRMPDDIRECTORYTREEPROVIDER_H

#include "cgdirectorytreewidget.h"
#include "mpd_tools.h"

class WRMPDDirectoryTreeProvider : public CGDirectoryTreeWidget::CGTreeBase
{
    public:
        WRMPDDirectoryTreeProvider(const std::string& uri=std::string());
        ~WRMPDDirectoryTreeProvider();
        virtual int count() const;
        virtual int level() const;
        virtual std::string itemName(int i, const std::string& defaultName=std::string()) const;
        virtual bool upLevel();
        virtual bool downLevel();
        virtual bool hasParent() const;
        virtual bool hasChildren(int idx) const;
        virtual std::vector<std::string> parentNames(int maxLevel=-1, const std::string& defaultItem=std::string()) const;
    protected:
        void cd(const std::string& uri);
        std::vector<std::string> m_uriSplit;
        std::string m_uri;
        std::vector<mpdtools::DirectoryEntry> m_list;
};

#endif // WRMPDDIRECTORYTREEPROVIDER_H
