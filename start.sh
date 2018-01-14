#!/bin/bash
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib -o debrujin.exe main.cpp graph_construction.cpp models.cpp -lsdsl -ldivsufsort -ldivsufsort64
./debrujin.exe simple_example.txt
