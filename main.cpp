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
int main(int argc, char const *argv[]) {
  bool debugging = false;
  if (argc > 2) {
    string flag = argv[2];
    if (flag == "-d") {debugging = true;}
  }
  fstream astream (argv[1], ios::in);
  if (astream.is_open()) {
    Cube cube;
    string action;
    stringstream ss;
    int a;
    while (getline(astream, action)) {
      ss.clear();
      ss << action[0];
      ss >> a;
      if (debugging) {cout << "main switch: ";}
      switch (a) {
        case 0: //INPUT FILE
        {
          if (debugging) {cout << "0\n";}
          string fileName = action.substr(2, action.length()-2);
          fstream istream (fileName, fstream::in);
          cube.initializeCube(istream);
          istream.close();
          break;
        }
        case 1: //TRANSFORM CUBE
        {
          if (debugging) {cout << "1\n";}
          string fileName = action.substr(2, action.length()-2);
          fstream istream (fileName, fstream::in);
          cube.transformationStream(istream);
          istream.close();
          if (debugging) {cube.print_bands();}
          break;
        }
        case 2: //OUTPUT FILE
        {
          if (debugging) {cout << "2\n";}
          string fileName = action.substr(2, action.length()-2);
          fstream ostream (fileName, fstream::out);
          cube.print(ostream);
          ostream.close();
          break;
        }
        case 3: //PRINT TO OUTPUT FILE
        {
          if (debugging) {cout << "3\n";}
          fstream ostream ("output.txt", fstream::out);
          cube.print(ostream);
          ostream.close();
          break;
        }
        case 4: //PRINT TO SCREEN
        {
          if (debugging) {cout << "4\n";}
          cube.print();
          break;
        }
        default:
        break;
      }
    }
    astream.close();
  }
  else {
    cout << "Could not open instruction file.\n";
  }
  return 0;
}
