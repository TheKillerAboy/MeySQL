#ifndef MEYSQL_BASIC_LISTNODE_H
#define MEYSQL_BASIC_LISTNODE_H

namespace MeySQL{
    namespace Basic{
        class ListNode{
        private:
            ListNode* link;
            void* value;
        public:
            ListNode();
            ListNode(void* value_);
            ListNode(ListNode* link_, void* value_);

            virtual ~ListNode();

            void set_link(ListNode* link_);
            void set_value(void* value);

            ListNode* get_link() const;
            void* get_value() const;
        };
    }
}

#endif