#ifndef MEYSQL_CELL_H
#define MEYSQL_CELL_H

namespace MeySQL{
    class Cell{
    private:
        void* value;
    public:
        Cell();
        Cell(void* value);
        ~Cell();

        void set_float(float value_);
        void set_int(int value_);
        void set_double(double value_);
        void set_char(char value_);
        void set_string(const char* value_);

        float get_float() const;
        int get_int() const;
        double get_double() const;
        char get_char() const;
        const char* get_string() const;

        bool is_null() const;
    };
}

#endif
