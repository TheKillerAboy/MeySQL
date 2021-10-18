#include "database.h"
#include "table.h"
#include "utils.h"

MeySQL::Database::Database() {
    size = 0;

    tables = new MeySQL::Table*[0];
    tableNames = new char*[0];
}

void MeySQL::Database::addTable(const char* tableName, MeySQL::Table* table) {
    char** tbnstmp;
    tbnstmp = MeySQL::Utils::copyArrayAddElementCString(tbnstmp, tableNames, size, tableName);
    tableNames = tbnstmp;

    MeySQL::Table** tbstmp;
    tbstmp = MeySQL::Utils::copyArrayAddElement(tbstmp, tables, size, table);
    tables = tbstmp;

    size++;
}
