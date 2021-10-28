#ifndef MEYSQL_DATABASE_H
#define MEYSQL_DATABASE_H

#include "tablelist.h"
#include "generatorlist.h"
#include "generator.h"
#include "tablelinklist.h"

namespace MeySQL{
    class Database{
    private:
        TableList* tableList;
        GeneratorList* generatorList;
        TableLinkList* tableLinkList;
        
        Generator* recordGenerator; 
    public:
        Database();
        ~Database();

        TableList* get_tableList() const;
        GeneratorList* get_generatorList() const;
        TableLinkList* getTableLinkList() const;
    };
}

#endif