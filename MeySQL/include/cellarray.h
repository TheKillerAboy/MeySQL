#ifndef MEYSQL_CELLARRAY_H
#define MEYSQL_CELLARRAY_H

#include "pointerarray.h"
#include "cell.h"

namespace MeySQL{
    class CellArray:Basic::PointerArray{
    private:

    public:
        CellArray();
        ~CellArray();

        Cell* get_index(size_t index);
    };
}

#endif