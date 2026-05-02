#!/bin/bash
make plantri

for i in $(seq 9 $1);
do
    ./plantri -aN $i output/output_times_$i.txt
done
