#ifndef MEYSQL_ROW_H
#define MEYSQL_ROW_H

#include <vector>
#include "rowcell.h"

namespace MeySQL{
    class Row{
    private:
        std::vector<RowCell*> cells;
        size_t size;
    public:
        Row();
        Row(const RowSchema& rowschema);
        
        ~Row();

        RowCell* get_index(const size_t& index);
    }
}

#endif