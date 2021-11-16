#ifndef MEYSQL_ROWSCHEMA_H
#define MEYSQL_ROWSCHEMA_H

#include <vector>
#include "celltype.h"

namespace MeySQL{
    class RowSchema{
    private:
        std::vector<CellType> schema;
    public:
        RowSchema();
        RowSchema(const size_t& size);

        ~RowSchema();


        CellType get_index(const size_t& index) const;

        size_t get_size() const;

        void set_index(const size_t& index, const CellType& type);

        void set_size(const size_t& size);
    }
}

#endif