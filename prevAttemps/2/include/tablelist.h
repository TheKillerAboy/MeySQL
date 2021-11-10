#ifndef MEYSQL_TABLELIST_H
#define MEYSQL_TABLELIST_H

#include "map.h"
#include "table.h"

namespace MeySQL{
    class TableList:Basic::Map{
    private:
        
    public:
        TableList();
        ~TableList();

        void insert(const char* key, Table* value);
        Table* find(const char* key);
    };
}

#endif