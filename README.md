# System-Programming-P1
Project implemented as part of the course Syspro K24 - 2021 - DIT
Vaccine Monitor app developed in C, using data structures like bloom 
filters, linked lists and skip lists.

Mark: 100/100
Final mark: 10/10

How to run:

make

cd build

./testFile.sh virusesFile countriesFile 1000 1  //To create input dir, 1000 = numlines, 1 = duplicates || 0 = no duplicates

./vaccineMonitor -c inputfile -b 100000 //b= size of bloom filter
