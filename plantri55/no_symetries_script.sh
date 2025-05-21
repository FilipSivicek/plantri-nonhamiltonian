#!/bin/bash

if [ -f "test.out" ]; then
	rm "test.out"
	touch "test.out"
fi

for i in $(seq 3 $1);
do
	./bin/plantri -a $i ./my_work/text_files/whole_set.txt 
	./bin/plantri -aV $i ./my_work/text_files/only_symetries.txt
	./bin/no_symetry -a $i ./my_work/text_files/no_symetries.txt
	python3 ./my_work/no_symetry_checker.py >> test.out
done

