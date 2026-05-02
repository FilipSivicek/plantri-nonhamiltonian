#!/bin/bash
make plantri

for i in $(seq 9 $1);
do
    ./bin/real_no_ladder -a $i output/output_times_real_ladder_$i.txt
done
