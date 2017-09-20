/*
sample code, just to start, it's run with the following commands:

g++ -std=c++1z -O2 -Wall $1 -lstdc++fs
./a.out $2 $3 $4 $5
echo comparing "correct_output.csv" with $5
cmp --silent correct_output.csv $5 || echo "files are different!" 

where 
  $1 - cpp file name
  $2 - name of input csv
  $3 - column name
  $4 - replacement string
  $5 - output file name

*/


#include <string>  
#include <iostream>  


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
		std::cout << argv[i] << "\n";
}