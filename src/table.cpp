#include "table.h"
#include "row.h"

void MeySQL::Table::add_row(Row* row) {
    rows->add_row(row);
}

size_t MeySQL::Table::get_size() const {
    return row_size;
}

MeySQL::Table::Table(MeySQL::ColumnTypes* columnTypes) {
    rows = new MeySQL::Rows();
    row_size = columnTypes->get_size();
    this->columnTypes = columnTypes;
}

MeySQL::Table::Table(){
    row_size = 0;
}

void MeySQL::Table::add_column(const char* columnName, const MeySQL::ColumnType& columnType) {
    columnTypes->add_column(columnName, columnType);
    MeySQL::Cursor cursor = get_cursor();
    while(!cursor.eof()){
        cursor.get()->add_cell(columnTypes);
        cursor.next();
    }
}

MeySQL::Cursor MeySQL::Table::get_cursor() const {
    MeySQL::Cursor cursor(rows);
    return cursor;    
}

MeySQL::ColumnTypes* MeySQL::Table::getColumnTypes() const {
    return columnTypes;    
}
