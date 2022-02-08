all: main

main:
	@echo " Compile vaccineMonitor ...";
	
	gcc -I ./include -o build/vaccineMonitor examples/main.c src/bloomfilter.c src/bloomFunctions.c src/BST.c src/mainQuestionsFunctions.c src/skipListFunctions.c src/StartersAndHelpFunctions.c

