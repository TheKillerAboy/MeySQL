#ifndef MEYSQL_COLUMNTYPES_H
#define MEYSQL_COLUMNTYPES_H

#include <stdlib.h>

namespace MeySQL{
    enum ColumnType{
        INT,
        CHAR,
        FLOAT,
        DOUBLE,
        STRING
    };

    int get_NULL_INT();
    float get_NULL_FLOAT();
    double get_NULL_DOUBLE();
    char get_NULL_CHAR();
    const char* get_NULL_STRING();

    class ColumnTypes{
    private:
        size_t size;
        ColumnType* columnTypes;
        char** columnNames;
    public:
        ColumnTypes(size_t size);
        ColumnTypes(): ColumnTypes(0){}

        size_t get_size() const;

        void set_type(const ColumnType& columnType, size_t index);
        ColumnType get_type(size_t index);

        void set_name(const char* columnName, size_t index);
        const char* get_name(size_t index);

        void add_column(const char* columnName, const ColumnType& columnType);
    };
}

#endif