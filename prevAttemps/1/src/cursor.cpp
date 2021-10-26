#include "cursor.h"

#include <iostream>

void MeySQL::Cursor::next() {
    current = rows->next(current);
}

MeySQL::Row* MeySQL::Cursor::get() const {
    return current->get();
}

MeySQL::Cursor::Cursor(MeySQL::Rows* rows) {
    this->rows = rows;
    begin();
}

void MeySQL::Cursor::begin() {
    current = rows->start();    
}

bool MeySQL::Cursor::eof() const {
    return current == NULL;    
}
