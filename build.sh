#!/bin/bash

DELETE=false
RUN=false
ENABLE_BUILD_ERROR_FLAGS=false

while getopts dre flag
do
    case "${flag}" in
        d) DELETE=true;;
        r) RUN=true;;
        e) ENABLE_BUILD_ERROR_FLAGS=true;;
    esac
done

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
    if [ "$RUN" = true ]; then
    echo "Running"
    ./MeySQL
    fi;
fi;