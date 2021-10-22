#ifndef MEYSQL_CURSOR_H
#define MEYSQL_CURSOR_H

#include "listnode.h"
#include "list.h"
#include "record.h"

namespace MeySQL{
    class Cursor{
    private:
        Basic::ListNode* current;
        Basic::List* records;
    public:
        Cursor(Basic::List* node);
        ~Cursor();

        void next();
        bool eof() const;
        Record* get() const;
        void start();
    };
}

#endif