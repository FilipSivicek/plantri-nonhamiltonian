#!/bin/bash

echo "Starting tester"
if [ ! -f "./bin/$1" ]; then
    make plantri_$1
fi

if [ ! -f "./bin/$2" ]; then
    make plantri_$2
fi

if [ ! -d "./output" ]; then
    mkdir ./output
fi

file1=./output/$1_$3.txt
file2=./output/$2_$3.txt
./bin/$1 -a $3 $file1
./bin/$2 -a $3 $file2
echo "The difference is:"
diff $file1 $file2
