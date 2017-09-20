#!/bin/sh
g++ -std=c++1z -O2 -Wall -pedantic $1 -lstdc++fs -pthread
./a.out $2 $3 $4 $5
echo comparing "correct_output.csv" with $5
cmp --silent correct_output.csv $5 || echo "files are different!" 
#echo "TECHIO> terminal -i ./a.out"
#sleep 60
