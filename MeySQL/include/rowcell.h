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

        void set_bool(const bool& value_);
        void set_char(const char& value_);
        void set_int(const int& value_);
        void set_float(const float& value_);
        void set_double(const double& value_);
        void set_string(const char* value_);

        void set_null();
    };
}

#endif