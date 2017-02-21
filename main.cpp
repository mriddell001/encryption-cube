/**
Expected form of input:
0. Program Name
1. Actions file.
  A. Actions file will contain a reference to the type of action to be taken.
    a. Form will be:
      Action                    -> (INT)
      Action FileName           -> (INT) (STRING)
      Action Filename FileName  -> (INT) (STRING) (STRING)
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
      switch (a) {
        case 0:
        {
          string fileName = action.substr(2, action.length()-2);
          fstream istream (fileName, fstream::in);
          cube.initializeCube(istream);
          istream.close();
          break;
        }
        case 1:
        {
          string fileName = action.substr(2, action.length()-2);
          break;
        }
        case 2:
        {
          string fileName = action.substr(2, action.length()-2);
          size_t pos = fileName.find(" ");
          string output = fileName.substr(pos);
          string input = action.substr(0, fileName.length()-(output.length()+1));
          break;
        }
        case 3:
        {
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
