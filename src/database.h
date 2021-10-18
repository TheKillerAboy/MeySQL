#ifndef MEYSQL_DATABASE_H
#define MEYSQL_DATABASE_H

#include "table.h"

namespace MeySQL{
    class Database{
    private:
        size_t size;

        MeySQL::Table** tables;
        char** tableNames;
    public:
        Database();
        
        void addTable(const char* tableName, MeySQL::Table* table);

        void read(const char* file);
        void write(const char* file) const;
    };
}

#endif