#include "cursor.h"
#include "table.h"

MeySQL::Cursor::Cursor(){}
MeySQL::Cursor::Cursor(const std::list<Row*>::iterator& iter_){
    open = true;
    iter = iter_;
}

MeySQL::Cursor::~Cursor(){
    close();
}

void MeySQL::Cursor::close(){
    open = false;
}
bool MeySQL::Cursor::eof() const{
    return parent_table->is_eof(std::next(iter));
}
void MeySQL::Cursor::next(){
    ++iter;
}

bool MeySQL::Cursor::is_open() const{
    return open;
}