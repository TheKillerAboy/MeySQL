#include "../src/table.h"
#include "../src/columntypes.h"
#include "../src/row.h"
#include "../src/terminal_renderer.h"

#include <iostream>

using namespace std;

int main(){
    MeySQL::ColumnTypes columnTypes(4);
    columnTypes.set_type(MeySQL::ColumnType::INT, 0);
    columnTypes.set_type(MeySQL::ColumnType::INT, 1);
    columnTypes.set_type(MeySQL::ColumnType::STRING, 2);
    columnTypes.set_type(MeySQL::ColumnType::INT, 3);
    columnTypes.set_name("test0",0);
    columnTypes.set_name("test1",1);
    columnTypes.set_name("test2",2);
    columnTypes.set_name("test3",3);
    MeySQL::Table table(&columnTypes);

    MeySQL::Row* newRow = new MeySQL::Row(&columnTypes);
    newRow->set_cell(1,0);
    newRow->set_cell(2,1);
    newRow->set_cell("Hello_Daar",2);
    newRow->set_cell(4,3);
    table.add_row(newRow);
    table.add_column("Hello",MeySQL::ColumnType::FLOAT);


    MeySQL::TerminalRenderer::renderTable(table, true);

    return 0;
}