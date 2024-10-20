#!/bin/bash

if [ ! -d "./bin" ]; then
    mkdir ./bin
fi

for var in "$@"
do
    make plantri_$var
done