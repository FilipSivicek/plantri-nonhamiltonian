#!/bin/bash

## Tester is used for testing if 2 algorithms generate same output
## Only makes sence to use with programs testing same property.
## First argument is name of first program, second is name of second program.
## Third argument are switches to be used for plantri. Fourth argument is number of vertices
## Fifth argument is optional. If it is diff, then difference between outputs is displayed
echo "Starting tester"

if [ ! -d "./bin" ]; then
    mkdir ./bin
fi

if [ ! -f "./bin/$1" ]; then
    make plantri_$1
fi

if [ -f "./bin/$1" ]; then
    program_mod_time_1=$(stat -c %Y ./my_work/$1.c)
    source_mod_time_1=$(stat -c %Y "./bin/$1")
    if [[ $program_mod_time_1 -gt $source_mod_time_1 ]]; then
        make plantri_$1
    fi
fi

if [ ! -f "./bin/$2" ]; then
    make plantri_$2
fi

if [ -f "./bin/$2" ]; then
    program_mod_time_2=$(stat -c %Y ./my_work/$2.c)
    source_mod_time_2=$(stat -c %Y "./bin/$2")
    if [[ $program_mod_time_2 -gt $source_mod_time_2 ]]; then
        make plantri_$2
    fi
fi

if [ ! -d "./output" ]; then
    mkdir ./output
fi

file1=./output/$1_$3_$4.txt
file2=./output/$2_$3_$4.txt
./bin/$1 -$3 $4 $file1
./bin/$2 -$3 $4 $file2

if [ $# -gt 4 ]; then
    if [ $5 = "diff" ]; then
        echo "The difference is:"
        diff $file1 $file2
    fi
fi
