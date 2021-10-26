#ifndef MEYSQL_UTILS_H
#define MEYSQL_UTILS_H

#include <stdlib.h>
#include <cstring>

namespace MeySQL{
    typedef unsigned long long int row_idtype;
    namespace Utils{
        template<typename T>
        T* copyArrayAddElement(T* dest, T*src, size_t size,const T& element){
            dest = new T[size+1];
            std::memcpy(dest, src, size*sizeof(T));
            dest[size] = element;
            delete[] src;
            return dest;
        }
        char** copyArrayAddElementCString(char** dest, char** src, size_t size, const char* element);
    }
}

#endif