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

        bool set_bool(bool value_);
        char set_char(char value_);
        int set_int(int value_);
        float set_float(float value_);
        double set_double(double value_);
        const char* set_string(const char* value_);

        void set_null();
    };
}

#endif