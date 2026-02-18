#!/bin/bash
./plantri -aN $1
./bin/no_ladder -ac4 $1 correct.txt
 /usr/bin/python3 /home/filip/Desktop/univerzita/semester3/rocnikovyProjekt/plantri55/verifier.py