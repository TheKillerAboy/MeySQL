#ifndef MEYSQL_GENERATOR_H
#define MEYSQL_GENERATOR_H

namespace MeySQL{
    typedef unsigned long long int GeneratorType;

    class Generator{
    private:
        GeneratorType value;
    public:
        GeneratorType next();

        Generator();
        Generator(GeneratorType value);

        ~Generator();
    };
}

#endif