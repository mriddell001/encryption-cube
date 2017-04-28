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

  fstream istream ("output.txt", fstream::in);
  fstream ostream ("unique.txt", fstream::out);
  string input;
  while (getline(istream,input)) {
    string tmp = cube.transformationDispatch(input);
    ret = s.insert(tmp);
    if (ret.second==true) {
      ostream << input << endl;
    }
  }
  istream.close();
  ostream.close();
  //rename("sortput.txt", "output.txt");
  return 0;
}
