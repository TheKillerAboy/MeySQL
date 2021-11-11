#ifndef MEYSQL_TABLELINKLIST_H
#define MEYSQL_TABLELINKLIST_H

#include "list.h"
#include "listnode.h"
#include "table.h"
#include "tablelink.h"

namespace MeySQL{
    class TableLinkList:Basic::List{
    private:

    public:
        TableLinkList();
        ~TableLinkList();

        void push_back(TableLink* tableLink);

        TableLinkList* get_primary_links(Table* table) const;
        TableLinkList* get_foreign_links(Table* table) const;
        TableLink* get_tableLink(Table* primaryTable, Table* foreignTable) const;
        static TableLink* get(Basic::ListNode* node);
    };
}

#endif