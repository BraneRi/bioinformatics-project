#!/bin/bash
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib -o debrujin.exe main.cpp graph_construction.cpp models.cpp -lsdsl -ldivsufsort -ldivsufsort64

for VARIABLE in 0 1 2 3 4 5 6 8 9
do
	./debrujin.exe input_output_files/input_$VARIABLE.fa
done
