#ifndef MEYSQL_CURSOR_H
#define MEYSQL_CURSOR_H

#include <list>
#include "row.h"

namespace MeySQL{
    class Table;

    class Cursor{
    private:
        bool open;
        std::list<Row*>::iterator iter;
        Table* parent_table;
    public:
        Cursor();
        Cursor(const std::list<Row*>::iterator& iter_);

        ~Cursor();

        void close();
        bool eof() const;
        void next();

        bool is_open() const;
    };
}

#endif