#!/bin/bash
make plantri
./plantri -aN $1 output_verifier.txt
./bin/no_ladder -ac4 $1 correct.txt
/usr/bin/python3 verifier.py
