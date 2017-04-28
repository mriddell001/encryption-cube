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
crypt: b64.o cube.o locality.o main.o
	g++ -std=c++11 -Wall -pedantic -g -o crypt main.o cube.o b64.o locality.o

main.o: b64.h cube.h locality.h main.cpp
	g++ -std=c++11 -Wall -pedantic -g -c main.cpp

cube.o: cube.h cube.cpp
	g++ -std=c++11 -Wall -pedantic -g -c cube.cpp

b64.o: b64.h b64.cpp
	g++ -std=c++11 -Wall -pedantic -g -c b64.cpp

locality.o: locality.h locality.cpp
	g++ -std=c++11 -Wall -pedantic -g -c locality.cpp

clean:
	rm -f crypt crypt.exe main.o b64.o cube.o locality.o basic.cube basic.key
