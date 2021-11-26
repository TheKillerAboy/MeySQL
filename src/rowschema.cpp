#include "rowschema.h"
#include "celltype.h"

MeySQL::RowSchema::RowSchema():MeySQL::RowSchema(0){
}
MeySQL::RowSchema::RowSchema(const size_t& size){
    set_size(size);
}

MeySQL::RowSchema::~RowSchema(){
}

MeySQL::CellType MeySQL::RowSchema::get_index(const size_t& index) const{
    return schema[index];
}

size_t MeySQL::RowSchema::get_size() const{
    return schema.size();
}

void MeySQL::RowSchema::set_index(const size_t& index, const CellType& type){
    schema[index] = type;
}

void MeySQL::RowSchema::set_size(const size_t& size){
    schema.resize(size);
}