#!/bin/bash

## Tester is used for testing if 2 algorithms generate same output
## Only makes sence to use with programs testing same property.

echo "Starting tester"

if [ ! -d "./bin" ]; then
    mkdir ./bin
fi

if [ ! -f "./bin/$1" ]; then
    make plantri_$1
fi

if [ ! -f "./bin/$2" ]; then
    make plantri_$2
fi

if [ ! -d "./output" ]; then
    mkdir ./output
fi

file1=./output/$1_$3_$4.txt
file2=./output/$2_$3_$4.txt
./bin/$1 -$3 $4 $file1
./bin/$2 -$3 $4 $file2

for last; do true; done

if [ $last = "diff" ]; then
    echo "The difference is:"
    diff $file1 $file2
fi
