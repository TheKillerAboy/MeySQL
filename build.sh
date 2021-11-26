#!/bin/bash
if [!-d ./build]; then
    mkdir ./build
fi;

cd build
cmake ..
cmake --build .

echo -n "Run build ([y]/n)? "
read answer
answer=${answer:-y}

if [ "$answer" != "${answer#[Yy]}" ] ;then
    ./MeySQL
fi