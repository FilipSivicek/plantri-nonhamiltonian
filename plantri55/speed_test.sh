#!/bin/bash
make plantri
./plantri -aN $1 output/output_speed_generator.txt
./bin/real_no_ladder -ac4 $1 output/output_speed_plantri.txt