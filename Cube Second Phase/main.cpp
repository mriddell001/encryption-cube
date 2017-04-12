/**
Expected form of input:
0. Program Name
1. Text file or Cube file
**/

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

#include "cube.h"

using namespace std;

ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

/**
* main - accept input file of instructions.
* @param {Int} argc - number of arguments.
* @param {Char Array} argv - char arrays containing input.
* @returns {Int}
*/
int main(int argc, char const *argv[]) {
  //File to be encoded.
  string input = argv[1], newname, keyfile, keytxt,
         keyname, crypt_cmd, cube_order;
  int l = input.length(), p = l-4;
  char dot = input[p];
  if (dot != '.') {//If the parameter is of type .cube
    newname = input.substr(0, p-1);
    keyname = newname;
    keyfile = newname + ".key";
    keytxt = newname + ".txt";
    newname += ".txt";
    rename(input.c_str(), newname.c_str());
    rename(keyfile.c_str(), keytxt.c_str());
    fstream cstream (newname, ios::in);
    fstream kstream (keytxt, ios::in);
    int data_size;
    kstream >> data_size;
    getline(kstream, crypt_cmd);
    getline(kstream, cube_order);
    Cube *cube = new Cube(cube_order);
  }
  else {//If the parameter is of type .txt
    newname = input.substr(0, p);
    keyname = newname;
    keyfile = newname + ".key";
    keytxt = newname + "key.txt";
    newname += ".cube";
    fstream istream ("fl.txt", ios::in);
    int l = rand() % 93840 + 1;
    while (l) {getline(istream, crypt_cmd);l--;}
    istream.close();
    Cube *cube = new Cube();
    fstream tstream (input, ios::in);
    cube->initializeCube(tstream);
    tstream.close();
    crypt_cmd = cube->transformationDispatch(crypt_cmd);
    int file_length = filesize(argv[1]);
    file_length+=file_length%48;
    fstream kstream (keytxt, ios::out);
    cube_order = cube->cube_order();
    kstream << file_length << " " << crypt_cmd << " " << cube_order;
    kstream.close();
    rename(keytxt.c_str(), keyfile.c_str());
    //remove(input.c_str());
    fstream cstream (newname, ios::out);
    cube->print(cstream);
    cstream.close();
    //rename(input.c_str(), newname.c_str());
  }
  return 0;
}
