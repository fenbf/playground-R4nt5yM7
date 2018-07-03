#!/bin/sh
g++ -std=c++1z -O2 -Wall $1

if [ -f "a.out" ]
then
	echo "TECHIO> terminal -i ./a.out"
	sleep 60
else
	echo "compilation failed"
fi
