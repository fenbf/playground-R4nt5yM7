#!/bin/sh
g++ -std=c++1z -O2 -Wall $1 -pthread
./a.out
#echo "TECHIO> terminal -i ./a.out"
#sleep 60
