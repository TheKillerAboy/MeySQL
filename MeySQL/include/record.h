#ifndef MEYSQL_RECORD_H
#define MEYSQL_RECORD_H

#include "generator.h"
#include "cellarray.h"

namespace MeySQL{
    class Record{
    private:
        GeneratorType id;
        CellArray* cells;
    public:
        Record();
        Record(GeneratorType id_, CellArray* cells_);
        ~Record();

        CellArray* get_cells() const;
    };
}

#endif