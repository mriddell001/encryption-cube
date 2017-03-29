/**
Expected form of input:
0. Program Name
1. Actions file.
  A. Actions file will contain a reference to the type of action to be taken.
    a. Form will be:
      Action                    -> (INT)
      Action FileName           -> (INT) (STRING)
      Action Filename FileName  -> (INT) (STRING) (STRING)
2. Debugging flag.
**/

//data_structure Read & Load
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "cube.h"

using namespace std;

/**
* main - accept input file of instructions.
* @param {Int} argc - number of arguments.
* @param {Char Array} argv - char arrays containing commandline input.
* @returns {Int}
*/
int main() {
  fstream istream ("full_list.txt", fstream::in);
  fstream ostream ("total_output.txt", fstream::out);
  string tmp = "";
  while (getline(istream, tmp)) {
    fstream input ("basic.txt", fstream::in);
    Cube pmt;
    pmt.initializeCube(input);
    pmt.transformationString(tmp);
    pmt.print(ostream);
    ostream << "\t" << tmp << endl;
    input.close();
  }
  istream.close();
  ostream.close();
  return 0;
}
