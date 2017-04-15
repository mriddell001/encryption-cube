/**
Expected form of input:
0. Program Name
1. Text file or Cube file
**/

#include <bitset>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <time.h>

#include "cube.h"

using namespace std;

string to_base64(string data) {
  string b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  string data64="",binary="", tmp, pmt = data;
  int count = data.length()/2, number;
  for (int i = 0; i < count; i++) {
    tmp = pmt.substr(i*2, 2);
    number = stoi(tmp);
    if (number < 26) {binary += std::bitset<8>(number+65).to_string();}
    else {binary += std::bitset<8>(number+71).to_string();}
    while (binary.length()>5) {
      tmp = binary.substr(0,6);
      binary = binary.substr(6,binary.length()-6);
      number = std::stoi(tmp, nullptr, 2);
      data64 += b64[number];
    }
  }
  return data64;
}

string from_base64(string data) {
  string b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  string rdata="",binary="", tmp;
  int count = data.length(), number;

  for (int i = 0; i < count; i++) {
    size_t index = b64.find(data[i]);
    tmp = std::bitset<8>(index).to_string();
    tmp = tmp.substr(2,6);
    binary += tmp;
    while (binary.length()>7) {
      tmp = binary.substr(0,8);
      binary = binary.substr(8,binary.length()-8);
      number = std::stoi(tmp, nullptr,2);
      if (number > 96) {number-=71; rdata += to_string(number);}
      else {number-=65; if (number < 10) {rdata += "0";} rdata += to_string(number);}
    }
  }
  return rdata;
}

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
    fstream cstream (input, ios::in);
    fstream kstream (keyfile, ios::in);
    int data_size;
    kstream >> data_size;
    kstream >> crypt_cmd;
    kstream >> cube_order;
    kstream.close();
    cube_order = from_base64(cube_order);
    Cube cube = Cube();
    cube.initializeCube(cstream);
    cstream.close();
    cube.transformationDispatch(crypt_cmd);
    fstream tstream (newname, ios::out);
    cube.print(tstream);
    tstream.close();
    remove(input.c_str());
    remove(keyfile.c_str());
  }
  else {//If the parameter is of type .txt
    newname = input.substr(0, p);
    keyname = newname;
    keyfile = newname + ".key";
    keytxt = newname + ".txt";
    newname += ".cube";
    fstream istream ("fl.txt", ios::in);
    srand (time(NULL));
    int l = rand() % 93840 + 1;
    while (l) {getline(istream, crypt_cmd);l--;}
    istream.close();
    Cube cube = Cube();
    fstream tstream (input, ios::in);
    cube.initializeCube(tstream);
    tstream.close();
    crypt_cmd = cube.transformationDispatch(crypt_cmd);
    int file_length = filesize(argv[1]);
    file_length+=file_length%48;
    fstream kstream (keytxt, ios::out);
    cube_order = cube.cube_order();
    cube_order = to_base64(cube_order);
    kstream << file_length << " " << crypt_cmd << " " << cube_order;
    kstream.close();
    rename(keytxt.c_str(), keyfile.c_str());
    //remove(input.c_str());
    fstream cstream (newname, ios::out);
    cube.print(cstream);
    cstream.close();
  }
  return 0;
}
