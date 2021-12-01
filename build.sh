#!/bin/bash

DELETE=false
RUN=0
ENABLE_BUILD_ERROR_FLAGS=false
SKIPSTYLE=false

while getopts dres flag
do
    case "${flag}" in
        d) DELETE=true;;
        r) RUN=$((RUN+1));;
        e) ENABLE_BUILD_ERROR_FLAGS=true;;
        s) SKIPSTYLE=true;;
    esac
done

if [ "$SKIPSTYLE" = false ]; then
    printf "###Formatting###\n(use -s to skip this)\n\n"
    astyleoptions="--style=attach -RNKjSxC80"
    ./thirdparty/astyle/astyle $astyleoptions "src/*.cpp"
    ./thirdparty/astyle/astyle $astyleoptions "include/*.h"
    printf "\n###Formatting###\n"
fi;

if [ "$RUN" -eq 2 ]; then
    echo "Only running"
    ./build/MeySQL
    exit 0
fi

#add run type to not compile thridparty

if [ "$DELETE" = true ]; then
    read -p 'You are about to delete built, you sure? (Y/[n]): ' dsurevar
    dsurevar=${dsurevar:-n}
    if [ "$dsurevar" = "Y" ]; then
        rm -rf ./build
        echo "Removed folder"
    else
        echo "Stoping build"
        exit 0
    fi;
fi;

if [ ! -d ./build ]; then
    mkdir ./build
fi;

# set local CC and CXX variables if running clang to gcc variants (macos)

export ENABLE_BUILD_ERROR_FLAGS;

cd build
cmake ..
cmake --build .

if [ $? -eq 0 ]; then
    if [ "$RUN" -eq 1 ]; then
    echo "Running"
    ./MeySQL
    fi;
fi;