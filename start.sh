#!/bin/bash
g++ -std=c++11 -o debrujin.exe main.cpp graph_construction.cpp models.cpp
./debrujin.exe simple_example.txt
