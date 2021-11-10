#ifndef MEYSQL_RECORDLIST_H
#define MEYSQL_RECORDLIST_H

#include "list.h"
#include "record.h"
#include "cursor.h"

namespace MeySQL{
    class RecordList{
    private:
        Basic::List* records;
    public:
        RecordList();
        ~RecordList();

        void add_record(Record* record);
        Cursor* get_cursor();
    };
}

#endif