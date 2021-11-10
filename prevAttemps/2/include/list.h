#ifndef MEYSQL_BASIC_LIST_H
#define MEYSQL_BASIC_LIST_H

#include "listnode.h"

namespace MeySQL{
    namespace Basic{
        class List{
        private:
            ListNode* front;
            ListNode* back;
        public:
            List();
            ~List();

            ListNode* get_front() const;
            ListNode* get_back() const;

            void push_back(ListNode* node);

            static void next_node(const ListNode* current);
        };
    }
}

#endif