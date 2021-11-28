#!/bin/bash

DELETE=false
RUN=0
ENABLE_BUILD_ERROR_FLAGS=false

while getopts dre flag
do
    case "${flag}" in
        d) DELETE=true;;
        r) RUN=$((RUN+1));;
        e) ENABLE_BUILD_ERROR_FLAGS=true;;
    esac
done

if [ "$RUN" -eq 2 ]; then
    echo "Only running"
    ./build/MeySQL
    exit 0
fi

if [ "$DELETE" = true ]; then
    rm -rf ./build
    echo "Removed Folder"
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