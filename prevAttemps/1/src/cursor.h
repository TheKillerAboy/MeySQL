#ifndef MEYSQL_CURSOR_H
#define MEYSQL_CURSOR_H

#include "rows.h"

namespace MeySQL{
    class Cursor{
    private:
        MeySQL::Rows* rows;
        MeySQL::RowNode* current;
    public:
        void next();
        MeySQL::Row* get() const;
        void begin();

        bool eof()const;

        Cursor(MeySQL::Rows* rows);
    };
}

#endif