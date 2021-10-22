#ifndef MEYSQL_TABLE_H
#define MEYSQL_TABLE_H

#include "tableheader.h"
#include "recordlist.h"

namespace MeySQL{
    class Table{
    private:
        TableHeader* tableHeader;
        RecordList* recordList;
    public:
        Table();
        ~Table();

        TableHeader* get_tableHeader() const;
        RecordList* get_recordList() const;
    };
}

#endif