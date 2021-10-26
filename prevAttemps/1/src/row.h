#ifndef MEYSQL_ROW_H
#define MEYSQL_ROW_H

#include <stdlib.h>
#include <string>
#include "columntypes.h"
#include "database.h"
#include "utils.h"

namespace MeySQL{
    class Row{
    private:
        MeySQL::row_idtype row_id;
        void** cells;
    public:
        void* get_cell(size_t index) const;
        void set_cell(int value,size_t index);
        void set_cell(float value,size_t index);
        void set_cell(double value,size_t index);
        void set_cell(const char* value, size_t index);
        void set_cell(const std::string& value, size_t index);

        void initialize_cell(MeySQL::ColumnType type, size_t index);
        void initialize_cells(MeySQL::ColumnTypes* types);
        
        void deinitialize_cell(MeySQL::ColumnType type, size_t index);
        void deinitialize_cells(MeySQL::ColumnTypes* types);

        Row(MeySQL::ColumnTypes* types);
        Row(const MeySQL::Database* db, MeySQL::ColumnTypes* types);
        Row(row_idtype id, MeySQL::ColumnTypes* types);

        void add_cell(MeySQL::ColumnTypes* type);
    };
}

// #include "row.t.h"

#endif