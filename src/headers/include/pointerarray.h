#ifndef MEYSQL_POINTERARRAY_H
#define MEYSQL_POINTERARRAY_H

#include <stdlib.h>

namespace MeySQL{
    namespace Basic{
        class PointerArray{
        private:
            void** values;
        public:
            PointerArray();
            ~PointerArray();

            void* get_index(size_t index) const;
        };
    }
}

#endif