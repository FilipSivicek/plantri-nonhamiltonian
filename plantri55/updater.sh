#!/bin/bash

for var in "$@"
do
    make plantri_$var
done