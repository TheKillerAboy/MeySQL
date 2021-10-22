#ifndef MEYSQL_BASIC_MAPNODE_H
#define MEYSQL_BASIC_MAPNODE_H

namespace MeySQL{
    namespace Basic{
        class MapNode{
        private:
            char* key;
            void* value;
        public:
            MapNode();
            MapNode(const char* key_);
            MapNode(const char* key_, void* value_);
            ~MapNode();

            void set_key(const char* key_);
            void set_value(void* value);

            const char* get_key() const;
            void* get_value() const;
        };
    }
}

#endif