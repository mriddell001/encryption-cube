#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>

#include "cube.h"

using namespace std;

int main() {
  Cube cube = Cube();
  cube.stringCube();
  set<string> s;
  pair<set<string>::iterator,bool> ret;

  fstream istream ("unique.txt", fstream::in);
  fstream ostream ("cube_input.txt", fstream::out);
  fstream sstream ("seven.txt", fstream::out);
  string input;
  while (getline(istream,input)) {
    string tmp = cube.transformationDispatch(input);
    ostream << tmp << "\t" << input << endl;
    if (input.length() == 7) {sstream << input << endl;}
  }
  istream.close();
  ostream.close();
  sstream.close();
  //rename("sortput.txt", "output.txt");
  return 0;
}
