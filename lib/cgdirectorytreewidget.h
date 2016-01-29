#ifndef CGDirectoryTreeWidget_H
#define CGDirectoryTreeWidget_H

#include "cgframe.h"
#include <vector>
#include <string>
#include "cgfontprops.h"
#include "cgscrollbar.h"
#include "cgtreebase.h"

/** \brief a widget that displays a tree of items of type CGDirectoryTree::TreeProvider */
class CGDirectoryTreeWidget: public CGTreeBase
{
    public:
        class TreeProvider {
            public:
                TreeProvider() {}
                virtual ~TreeProvider() {}
                virtual int count() const=0;
                virtual int level() const=0;
                virtual std::string itemName(int i, const std::string& defaultName=std::string()) const=0;
                virtual bool upLevel()=0;
                virtual bool downLevel(int i)=0;
                virtual bool hasParent() const=0;
                virtual bool hasChildren(int idx) const=0;
                virtual std::vector<std::string> parentNames(int maxLevel=-1, const std::string& defaultItem=std::string()) const=0;
                virtual std::string parentName(const std::string& defaultItem=std::string()) const;
        };

        explicit CGDirectoryTreeWidget(CGWidget* parent=NULL);
        explicit CGDirectoryTreeWidget(int x, int y, int width, int height, CGWidget* parent=NULL);
        virtual ~CGDirectoryTreeWidget();

        inline TreeProvider* provider() const {
            return m_provider;
        }
        void setProvider(TreeProvider* p, bool ownsProviderObject);

        virtual void downLevel();
        virtual void upLevel();
        virtual void clear();
        virtual int count() const;
        virtual std::string itemName(int i, const std::string& defaultItem=std::string()) const;
        virtual bool hasChildren(int i) const;
        virtual int currentLevel() const;
        virtual bool hasParent() const;
        virtual std::vector<std::string> parentItemNames(int maxLevel=-1, const std::string& defaultItem=std::string()) const;



    protected:

        bool m_ownsProvider;
        TreeProvider* m_provider;
};


#endif // CGDirectoryTreeWidget_H
