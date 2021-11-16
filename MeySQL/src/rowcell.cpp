#include "rowcell.h"
#include "celltype.h"
#include <cstring>

MeySQL::RowCell::RowCell():MeySQL::RowCell(nullptr, MeySQL::CellType::NULLTYPE){
}
MeySQL::RowCell::RowCell(void* value, CellType type){
    this->value = value;
    this->type = type;
}

MeySQL::RowCell::~RowCell(){
    set_null();
}

bool MeySQL::RowCell::get_bool() const{
    return *(bool*)value;
}
char MeySQL::RowCell::get_char() const{
    return *(char*)value;
}
int MeySQL::RowCell::get_int() const{
    return *(int*)value;
}
float MeySQL::RowCell::get_float() const{
    return *(float*)value;
}
double MeySQL::RowCell::get_double() const{
    return *(double*)value;
}
const char* MeySQL::RowCell::get_string() const{
    return (char*)value;
}

void MeySQL::RowCell::set_bool(const bool& value_){
    set_null();
    value = new bool;
    *(bool*)value = value_;
}
void MeySQL::RowCell::set_char(const char& value_){
    set_null();
    value = new char;
    *(char*)value = value_;
}
void MeySQL::RowCell::set_int(const int& value_){
    set_null();
    value = new int;
    *(int*)value = value_;
}
void MeySQL::RowCell::set_float(const float& value_){
    set_null();
    value = new float;
    *(float*)value = value_;
}
void MeySQL::RowCell::set_double(const double& value_){
    set_null();
    value = new double;
    *(double*)value = value_;
}
void MeySQL::RowCell::set_string(const char* value_){
    set_null();
    value = new char[std::strlen(value_) + 1];
    std::strcpy((char*)value, value_);
}

void MeySQL::RowCell::set_null(){
    switch(type){
        case BOOL:
            delete (bool*)value;
            break;
        case CHAR:
            delete (char*)value;
            break;
        case INT:
            delete (int*)value;
            break;
        case FLOAT:
            delete (float*)value;
            break;
        case DOUBLE:
            delete (double*)value;
            break;
        case STRING:
            delete[] (char*)value;
            break;
        case NULLTYPE:
            break;
    }
}