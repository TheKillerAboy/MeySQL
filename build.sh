#!/bin/bash

delete='false'
run='false'

while getopts dr flag
do
    case "${flag}" in
        d) delete='true';;
        r) run='true';;
    esac
done

if [ "$delete" = "true" ]; then
    rm -rf ./build
    echo "Removed Folder"
fi;

if [ ! -d ./build ]; then
    mkdir ./build
fi;

# set local CC and CXX variables if running clang to gcc variants (macos)

cd build
cmake ..
cmake --build .

if [ "$run" = "true" ]; then
    echo "Running"
    ./MeySQL
fi;