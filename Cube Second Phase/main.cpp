/**
Expected form of input:
0. Program Name
1. Text file or Cube file
**/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

#include "b64.h"
#include "cube.h"
#include "locality.h"

using namespace std;

/**
* filesize - Return the size of a file.
* @param {Const Char*} filename - Name of file.
* @returns {pos_type}
*/
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
int main(int argc, char const *argv[]) {//Rework to include multiple input orders.
  //File to be encoded.
  B64 b64;
  Locality loc;
  vector<string> vo;
  vector<string> vi;
  string input = argv[1], newname, keyfile, keytxt, crypt_cmd, cube_order;
  int l = input.length(), p = l-4;
  int runs = 0;
  char dot = input[p];
  if (dot != '.') {//If the parameter is of type .cube
    newname = input.substr(0, p-1);
    keyfile = newname + ".key";
    keytxt = newname + ".txt";
    newname += ".txt";
    fstream cstream (input, ios::in);
    fstream kstream (keyfile, ios::in);
    int data_size;
    kstream >> data_size;
    kstream >> runs;
    kstream >> cube_order;
    kstream >> crypt_cmd;
    kstream.close();

    fstream tstream (newname, ios::out);
    cube_order = b64.from_base64(cube_order);
    Cube cube = Cube();
    cube.initializeCube(cstream);
    cstream.close();
    cube.transformationDispatch(crypt_cmd);
    cube.print(tstream);
    tstream.close();
    remove(input.c_str());
    remove(keyfile.c_str());
  }
  else {//If the parameter is of type .txt
    srand (time(NULL));
    //runs = rand() % 25 + 1;
    runs = 1;
    int max = 0;
    newname = input.substr(0, p);
    keyfile = keytxt = newname;
    keyfile += ".key";
    keytxt += ".txt";
    newname += ".cube";

    vector<int> array;
    vector<int>::iterator it;
    vector<string>::iterator itt;
    for (int i = 0; i < runs; i++) {
      cube_order = loc.randGen(&vo);
      vo.push_back(cube_order);
      int l = rand() % 8170656;
      if (l > max) {max = l;}
      array.push_back(l);
      vi.push_back(to_string(l));
    }
    fstream istream ("sl.txt", ios::in);
    for (int i = 0; i < max+1; i++) {
      it = find(array.begin(),array.end(),i);
      getline(istream, crypt_cmd);
      if (it!=array.end()) {
        itt = find(vi.begin(),vi.end(),to_string(i));
        int j = distance(vi.begin(),itt);
        vi[j] = crypt_cmd;
      }
    }
    array.erase(array.begin(),array.end());
    istream.close();

    int file_length = filesize(argv[1]);
    file_length+=file_length%48;
    string output = "";

    Cube cube = Cube();
    for (int i = 0; i < runs; i++) {
      string o = "";
      //cube_order = vo[i];
      crypt_cmd = vi[i];
      //cube.overwriteOrder(cube_order);
      //cube_order = b64.to_base64(cube_order);
      crypt_cmd = cube.transformationDispatch(crypt_cmd);
      output = "\t" + crypt_cmd;
    }
    cube_order = b64.to_base64(cube.cube_order());
    output = "\t" + cube_order + output;
    vi.erase(vi.begin(),vi.end());
    vo.erase(vo.begin(),vo.end());
    fstream tstream (input, ios::in);
    cube.initializeCube(tstream);
    tstream.close();

    fstream kstream (keytxt, ios::out);
    kstream << file_length << "\t" << runs << "\t" << output;
    kstream.close();
    rename(keytxt.c_str(), keyfile.c_str());
    fstream cstream (newname, ios::out);
    cube.print(cstream);
    cstream.close();
  }
  return 0;
}
