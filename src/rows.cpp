#include "rows.h"

MeySQL::Rows::Rows() {
    begin = NULL;
    end = NULL;    
}

MeySQL::RowNode::RowNode(MeySQL::Row* value, MeySQL::RowNode* next) {
    this->next_ = next;
    this->value = value;
}

MeySQL::Row* MeySQL::RowNode::get() const {
    return value;
}

void MeySQL::Rows::add_row(MeySQL::Row* row) {
    RowNode* newNode = new RowNode(row, NULL);
    if(begin == NULL){
        begin = newNode;
    }
    else{
        end->set_next(newNode);
    }
    end = newNode;
}

MeySQL::RowNode* MeySQL::Rows::next(const MeySQL::RowNode* node) {
    if(node == NULL){
        return NULL;
    }
    return node->next();
}

MeySQL::RowNode* MeySQL::Rows::start() const {
    return begin;
}

MeySQL::Rows& MeySQL::Rows::operator=(const MeySQL::Rows& rhs){
    return *this;
}

MeySQL::RowNode* MeySQL::RowNode::next() const {
    return next_;    
}

void MeySQL::RowNode::set_next(MeySQL::RowNode* next) {
        next_ = next;
}
