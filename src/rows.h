#ifndef MEYSQL_ROWS_H
#define MEYSQL_ROWS_H

#include "row.h"

namespace MeySQL{
    class RowNode{
    private:
        MeySQL::Row* value;
        RowNode* next_;
    public:
        RowNode(MeySQL::Row* value, RowNode* next);
        MeySQL::Row* get() const;
        MeySQL::RowNode* next() const;
        void set_next(MeySQL::RowNode* next);
    };

    class Rows{
    private:
        RowNode* begin;
        RowNode* end;
    public:
        static RowNode* next(const RowNode* node);
        RowNode* start() const;

        Rows();
        Rows(const Rows& rhs);
        Rows& operator=(const Rows& rhs);

        void add_row(MeySQL::Row* row);
    };
}

#endif