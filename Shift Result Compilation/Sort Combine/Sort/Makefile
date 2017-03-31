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
sort: sort_map.o
	g++ -std=c++11 -Wall -pedantic -g -o sort sort_map.o

strip: strip.o
		g++ -std=c++11 -Wall -pedantic -g -o strip strip.o

sort_map.o: sort_map.cpp
	g++ -std=c++11 -Wall -pedantic -g -c sort_map.cpp

strip.o: strip.cpp
	g++ -std=c++11 -Wall -pedantic -g -c strip.cpp

clean:
	rm -f sc sort.exe sort_map.o t_sorted.txt

cleaner:
	rm -f sc strip strip.exe sort.exe strip.o sort_map.o t_sorted.txt correct_inputs.txt
