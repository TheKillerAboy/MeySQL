#ifndef MEYSQL_TABLELINK_H
#define MEYSQL_TABLELINK_H

#include "tableheader.h"
#include "table.h"

namespace MeySQL{
    class TableLink{
    private:
        Type primaryType, foreignType;
        Table* primaryTable, foreignTable;
        //TODO: implement maping from prim to sets of forign key record ids
        //TODO: implement speed effienct varients for types
    public:
        TableLink();
        ~TableLink();
    };
}

#endif