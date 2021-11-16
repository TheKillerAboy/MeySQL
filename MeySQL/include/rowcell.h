#ifndef MEYSQL_ROWCELL_H
#define MEYSQL_ROWCELL_H

#include "celltype.h"

namespace MeySQL{
    class RowCell{
    private:
        void* value;
        CellType type;
    public:
        RowCell();
        RowCell(void* value, CellType type);

        ~RowCell();

        bool get_bool() const;
        char get_char() const;
        int get_int() const;
        float get_float() const;
        double get_double() const;
        const char* get_string() const;

        bool set_bool();
        char set_char();
        int set_int();
        float set_float();
        double set_double();
        const char* set_string();

        void set_null();
    };
}

#endif