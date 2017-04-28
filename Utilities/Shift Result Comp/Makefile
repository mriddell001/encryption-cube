# Makefile for captsone
#
# If this file is in the directory with your program, you can compile your
# program using the following command:
#
#   $ make
#
# When you are done with this assignment, delete all the files generated
# by the compiler (you can always recreate them if you need them)
#
#   $ make clean
#
# It is a good idea to understand how make works
#
# Commands all have the following format:
#    file_to_be_created: list_of_files_the_file_to_left_is_create_from
#    <tab>the command that generates this file
#
# Compiler options
#    the arguments after g++ specify specific options for the compiler
#    -Wall        ==> print all warnings
#    -pedantic    ==> print warnings when non-standard C++ is used
#    -g           ==> keep additional information to aid in debugging
#    -o           ==> specify the output filename
#    -c           ==> compile only (create a .o file)
combo: combinations.o
	g++ -std=c++11 -Wall -pedantic -g -o combo combinations.o

combinations.o: combinations.cpp
	g++ -std=c++11 -Wall -pedantic -g -c combinations.cpp

clean:
	rm -f combo combo.exe combinations.o output0.txt output1.txt output2.txt output3.txt output4.txt output5.txt
