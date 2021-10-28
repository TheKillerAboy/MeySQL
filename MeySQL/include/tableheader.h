#ifndef MEYSQL_TABLEHEADER_H
#define MEYSQL_TABLEHEADER_H

#include "pointerarray.h"

namespace MeySQL{
    enum Type{
        INT,
        FLOAT,
        DOUBLE,
        CHAR,
        STRING
    };

    class TableHeader{
    private:
        Basic::PointerArray columnNames;
        Type* columnTypes;
    public:
        TableHeader();
        ~TableHeader();
    };
}

#endif