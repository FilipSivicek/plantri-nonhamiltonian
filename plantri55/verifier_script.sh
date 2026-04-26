#!/bin/bash
make plantri
./plantri -aN $1 output_verifier/output_my_gen_$1.txt
./bin/no_ladder -ac4 $1 output_verifier/output_plantri_$1.txt
/usr/bin/python3 verifier.py
