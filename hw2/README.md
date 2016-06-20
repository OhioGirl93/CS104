## HW2


######Instructions for Grader

All of Problem 1 and Problem 6 is in hw2.txt.

A makefile is included to compile main.cpp, main2.cpp, main3.cpp, and postfix.cpp.

To compile llistdbl.cpp, llistbl.h, and main.cpp, type into command line: make main
This compiles llistdbl to a .o file, which is then compiled with main.cpp again.
To run main.cpp which is a test file for llistdbl, type into command line: ./main

To compile alistint.cpp, alistint.h, and main2.cpp, type into command line: make main2
This compiles alistint to a .o file, which is then compiled with main2.cpp again.
To run main2.cpp which is a test file for alistint, type into command line: ./main2

To compile stackdbl.cpp, stackdbl.h, and main3.cpp, type into command line: make main3
This compiles stackdbl to a .o file, which is then compiled with main3.cpp again.
To run main3.cpp which is a test file for stackdbl, type into command line: ./main3

To compile stackdbl.o, llistdbl.o, and postfix.cpp, type into command line: make postfix
This compliles the two .o files which are used in postfix, and then compiles postfix.cpp
To run postfix.cpp, there must be an input file and an output file. 
Given these two files, type into command line: ./postfix (inputfile name).in (outputfile name).out
When given an equation written with +, -, *, or / operators in postfix style in the input file, the program will take the equation, given they are separated by lines, and calculate the answer or output "invalid" if the equation is not in postfix notation.
