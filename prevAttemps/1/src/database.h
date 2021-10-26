#ifndef MEYSQL_DATABASE_H
#define MEYSQL_DATABASE_H

#include "table.h"
#include "utils.h"

namespace MeySQL{
    class Database{
    private:
        size_t size;

        MeySQL::Table** tables;
        char** tableNames;

        MeySQL::row_idtype cur_row_id;
    public:
        Database();
        
        void addTable(const char* tableName, MeySQL::Table* table);

        void read(const char* file);
        void write(const char* file) const;

        row_idtype gen_row_id();
    };
}

#endif