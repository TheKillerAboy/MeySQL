#ifndef MEYSQL_TABLELINK_H
#define MEYSQL_TABLELINK_H

#include "tableheader.h"
#include "table.h"

namespace MeySQL{
    class TableLink{
    private:
        Table* primaryTable, foreignTable;
	size_t primaryIndex, foreignIndex;

	//TODO Add prim lookup for forgns
	//TODO Add prim to forgns links
    public:
        TableLink();
        ~TableLink();
    };
}

#endif
