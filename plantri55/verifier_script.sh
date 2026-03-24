#!/bin/bash
make plantri
./plantri -aN $1 output_verifier/output_my_gen.txt
./bin/no_ladder -ac4 $1 output_verifier/output_plantri.txt
/usr/bin/python3 verifier.py
