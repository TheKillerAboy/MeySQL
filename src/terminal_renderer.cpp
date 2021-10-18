#include "terminal_renderer.h"
#include <iostream>
#include <cstring>

void MeySQL::TerminalRenderer::renderTable(const MeySQL::Table& table, bool header) {
    if(header){
        for(int i = 0; i < table.getColumnTypes()->get_size(); ++i){
            std::cout<<table.getColumnTypes()->get_name(i)<<' ';
        }
        std::cout<<'\n';
    }    
    MeySQL::Cursor cursor = table.get_cursor();
    cursor.begin();
    while(!cursor.eof()){
        for(int i = 0; i < table.getColumnTypes()->get_size(); ++i){
            bool isNULL = false;
            switch(table.getColumnTypes()->get_type(i)){
                case INT:
                    isNULL = *(int*)cursor.get()->get_cell(i) == MeySQL::get_NULL_INT();
                    break;
                case STRING:
                    isNULL = std::strcmp((char*)cursor.get()->get_cell(i), MeySQL::get_NULL_STRING()) == 0;
                    break;
                case CHAR:
                    isNULL = *(char*)cursor.get()->get_cell(i) == MeySQL::get_NULL_CHAR();
                    break;
                case FLOAT:
                    isNULL = *(float*)cursor.get()->get_cell(i) == MeySQL::get_NULL_FLOAT();
                    break;
                case DOUBLE:
                    isNULL = *(double*)cursor.get()->get_cell(i) == MeySQL::get_NULL_DOUBLE();
                    break;
            }
            if(!isNULL){
                switch(table.getColumnTypes()->get_type(i)){
                    case INT:
                        std::cout<<*(int*)cursor.get()->get_cell(i)<<' ';
                        break;
                    case STRING:
                        std::cout<<(char*)cursor.get()->get_cell(i)<<' ';
                        break;
                    case CHAR:
                        std::cout<<*(char*)cursor.get()->get_cell(i)<<' ';
                        break;
                    case FLOAT:
                        std::cout<<*(float*)cursor.get()->get_cell(i)<<' ';
                        break;
                    case DOUBLE:
                        std::cout<<*(double*)cursor.get()->get_cell(i)<<' ';
                        break;
                }
            }
            else{
                std::cout<<"NULL ";
            }
        }
        std::cout<<'\n';
        cursor.next();
    }
}
