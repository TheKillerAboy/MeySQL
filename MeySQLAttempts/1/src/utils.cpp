#include "utils.h"


char** MeySQL::Utils::copyArrayAddElementCString(char** dest, char** src, size_t size, const char* element) {
    dest = new char*[size+1];
    for(int i = 0; i < size; ++i){
        dest[i] = new char[std::strlen(src[i])+1];
        strcpy(dest[i], src[i]);
    }
    dest[size] = new char[std::strlen(element)+1];
    strcpy(dest[size], element);
    for(int i = 0; i < size; ++i){
        delete[] src[i];
    }
    delete[] src;
    return dest;
}