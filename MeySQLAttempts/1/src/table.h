#ifndef MEYSQL_TABLE_H
#define MEYSQL_TABLE_H

#include <stdlib.h>
#include "columntypes.h"
#include "row.h"
#include "rows.h"
#include "cursor.h"

namespace MeySQL{
    class Table{
    private:
        size_t row_size;
        MeySQL::Rows* rows;
        MeySQL::ColumnTypes* columnTypes;
    public:
        MeySQL::Cursor get_cursor() const;
        void add_row(Row* row);

        size_t get_size() const;

        MeySQL::ColumnTypes* getColumnTypes()const;

        Table();
        Table(MeySQL::ColumnTypes* columnTypes);
        
        void add_column(const char* columnName, const MeySQL::ColumnType& columnType);
    };
}

#endif