#ifndef MEYSQL_GENERATORLIST_H
#define MEYSQL_GENERATORLIST_H

#include "map.h"
#include "generator.h"

namespace MeySQL{
    class GeneratorList:Basic::Map{
    private:
        
    public:
        GeneratorList();
        ~GeneratorList();

        void insert(const char* key, Generator* value);
        Generator* find(const char* key);
    };
}

#endif