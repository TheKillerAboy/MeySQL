#include "table.h"
#include "cursor.h"

MeySQL::Table::Table(){
    cursor = nullptr;
}
MeySQL::Table::Table(const MeySQL::RowSchema& rowschema_){
    cursor = nullptr;
    rowschema = rowschema_;
}

MeySQL::Table::~Table(){
    if(cursor != nullptr){
        delete cursor;
    }
}

MeySQL::RowSchema& MeySQL::Table::get_rowschema(){
    return rowschema;
}

MeySQL::Cursor* MeySQL::Table::get_cursor(){
    if(is_cursor_open()){
        throw "Cursor is currently open";
    }
    if(cursor != nullptr){
        delete cursor;
    }
    cursor = new Cursor();
    // TODO: add constructor parameters
    return cursor;
}

bool MeySQL::Table::is_cursor_open() const{
    return cursor == nullptr || cursor->is_open();
}

bool MeySQL::Table::is_eof(const std::list<Row*>::iterator& iter) const{
    return iter == rows.end();
}