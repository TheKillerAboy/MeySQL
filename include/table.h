#ifndef MEYSQL_TABLE_H
#define MEYSQL_TABLE_H

#include <list>
#include "row.h"
#include "rowschema.h"
#include "cursor.h"

namespace MeySQL{
    class Table{
    private:
        std::list<Row*> rows;
        RowSchema rowschema;
        Cursor* cursor;
    public:
        Table();
        Table(const RowSchema& rowschema_);

        ~Table();

        RowSchema& get_rowschema();

        Cursor* get_cursor();

        bool is_cursor_open() const;

        bool is_eof(const std::list<Row*>::iterator& iter) const;
    };
}

#endif