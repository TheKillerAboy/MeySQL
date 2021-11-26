#include "row.h"
#include "rowcell.h"
#include "rowschema.h"

MeySQL::Row::Row():{
}
MeySQL::Row::Row(const MeySQL::RowSchema& rowschema){
    cells.resize(rowschema.get_size());
    for(size_t i = 0; i < cells.size; ++i){
        cells[i] = new MeySQL::RowCell()
    }
}

MeySQL::Row::~Row(){
    for(size t i = 0; i < cells.size; ++i){
        delete cells[i];
    }
}

MeySQL::RowCell* MeySQL::Row::get_index(const size_t& index){
    return cells[index];
}