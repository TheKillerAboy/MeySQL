#include "row.h"
#include "utils.h"
#include <cstring>
#include <string>

void* MeySQL::Row::get_cell(size_t index) const {
    return cells[index];
}
void MeySQL::Row::set_cell(const char* value, size_t index) {
    deinitialize_cell(MeySQL::ColumnType::STRING, index);
    cells[index] = new char[std::strlen(value)+1];
    std::strcpy((char*)cells[index], value);
}
void MeySQL::Row::set_cell(const std::string& value, size_t index) {
    set_cell(value.c_str(), index);
}
void MeySQL::Row::set_cell(int value, size_t index) {
    *(int*)cells[index] = value; 
}
void MeySQL::Row::set_cell(float value, size_t index) {
    *(float*)cells[index] = value; 
}
void MeySQL::Row::set_cell(double value, size_t index) {
    *(double*)cells[index] = value; 
}

MeySQL::Row::Row(MeySQL::ColumnTypes* types) {
    cells = new void*[types->get_size()];
    initialize_cells(types);
}

void MeySQL::Row::add_cell(MeySQL::ColumnTypes* types) {
    void** newCells = new void*[types->get_size()];
    for(int i =0; i < types->get_size()-1; ++i){
        switch (types->get_type(i))
        {
            case INT:
                newCells[i] = new int;
                *(int*)newCells[i] = *(int*)cells[i];
                break;
            case FLOAT:
                newCells[i] = new float;
                *(float*)newCells[i] = *(float*)cells[i];
                break;
            case CHAR:
                newCells[i] = new char;
                *(char*)newCells[i] = *(char*)cells[i];
                break;
            case DOUBLE:
                newCells[i] = new double;
                *(double*)newCells[i] = *(double*)cells[i];
                break;
            case STRING:
                newCells[i] = new char[std::strlen((char*)cells[i])+1];
                std::strcpy((char*)newCells[i], (char*)cells[i]);
                break;
        }
    }
    int li = types->get_size()-1;
    switch (types->get_type(li))
    {
        case INT:
            newCells[li] = new int;
            *(int*)newCells[li] = MeySQL::get_NULL_INT();
            break;
        case FLOAT:
            newCells[li] = new float;
            *(float*)newCells[li] = MeySQL::get_NULL_FLOAT();
            break;
        case CHAR:
            newCells[li] = new char;
            *(char*)newCells[li] = MeySQL::get_NULL_CHAR();
            break;
        case DOUBLE:
            newCells[li] = new double;
            *(double*)newCells[li] = MeySQL::get_NULL_DOUBLE();
            break;
        case STRING:
            newCells[li] = new char[2];
            std::strcpy((char*)newCells[li],MeySQL::get_NULL_STRING());
            break;
    }
    for(int i = 0; i < types->get_size()-1; ++i){
        deinitialize_cell(types->get_type(i), i);
    }
    delete[] cells;
    cells = newCells;
}

void MeySQL::Row::initialize_cell(MeySQL::ColumnType type, size_t index) {
    switch(type){
        case INT:
            cells[index] = new int;
            break;
        case FLOAT:
            cells[index] = new float;
            break;
        case DOUBLE:
            cells[index] = new double;
            break;
        case STRING:
            cells[index] = new char;
            *(char*)cells[index] = '\0';
            break;
        case CHAR:
            cells[index] = new char;
            break;
    }
}

void MeySQL::Row::initialize_cells(MeySQL::ColumnTypes* types) {
    for(int i = 0; i < types->get_size(); ++i){
        initialize_cell(types->get_type(i), i);
    }    
}

void MeySQL::Row::deinitialize_cell(MeySQL::ColumnType type, size_t index) {
    switch(type){
        case INT:
            delete (int*) cells[index];
            break;
        case FLOAT:
            delete (float*) cells[index];
            break;
        case DOUBLE:
            delete (double*) cells[index];
            break;
        case STRING:
            delete[] (char*) cells[index];
            break;
        case CHAR:
            delete (char*) cells[index];
            break;
    }
}

void MeySQL::Row::deinitialize_cells(MeySQL::ColumnTypes* types) {
    for(int i = 0; i < types->get_size(); ++i){
        deinitialize_cell(types->get_type(i), i);
    } 
}
