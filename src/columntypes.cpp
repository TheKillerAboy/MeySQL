#include "columntypes.h"
#include "utils.h"
#include <cstring>

MeySQL::ColumnTypes::ColumnTypes(size_t size) {
    this->size = size;
    columnTypes = new MeySQL::ColumnType[size];
    columnNames = new char*[size];
}

size_t MeySQL::ColumnTypes::get_size() const {
    return size;
}

void MeySQL::ColumnTypes::add_column(const char* columnName, const ColumnType& columnType) {
    ColumnType* newCT;
    newCT = MeySQL::Utils::copyArrayAddElement<ColumnType>(newCT, columnTypes, size, columnType);
    columnTypes = newCT;

    char** newCN;
    newCN = MeySQL::Utils::copyArrayAddElementCString(newCN, columnNames, size, columnName);
    columnNames = newCN;
    
    size++;
}

void MeySQL::ColumnTypes::set_type(const ColumnType& columnType, size_t index) {
    columnTypes[index] = columnType;    
}

MeySQL::ColumnType MeySQL::ColumnTypes::get_type(size_t index) {
    return columnTypes[index];
}

void MeySQL::ColumnTypes::set_name(const char* columnName, size_t index) {
    delete[] columnNames[index];
    columnNames[index] = new char[std::strlen(columnName)+1];
    strcpy(columnNames[index], columnName);    
}

const char* MeySQL::ColumnTypes::get_name(size_t index) {
    return columnNames[index];    
}

int MeySQL::get_NULL_INT(){
    return -9999;
}
float MeySQL::get_NULL_FLOAT(){
    return -9999;
}
double MeySQL::get_NULL_DOUBLE(){
    return -9999;
}
char MeySQL::get_NULL_CHAR(){
    return '\a';
}
const char* MeySQL::get_NULL_STRING(){
    return "\a";
}