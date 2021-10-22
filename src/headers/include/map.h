#ifndef MEYSQL_BASIC_MAP_H
#define MEYSQL_BASIC_MAP_H

#include "list.h"

namespace MeySQL{
    namespace Basic{
        class Map: List{
        private:
            
        public:
            Map();
            ~Map();

            void insert(const char* key, void* value);
            void* find(const char* key);
        };
    }
}

#endif