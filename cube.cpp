//Cube.cpp
#include "cube.h"
#include <string>
#include <vector>
#include <fstream>

/*   Debug only:   */
#include <iostream>

using namespace std;

Cube::Cube() {
  for (size_t i = 0; i < 48; i++) {
    Pip *tmp = new Pip(i);
    pips.push_back(tmp);
  }
}

void Cube::initializeCube(fstream& stream) {
  char ch;
  int index = 0;
  while (stream.get(ch)) {
    cout << ch << " " << index << endl;
    string str;
    str.push_back(ch);
    pips[index]->data += str;

    index++;
    index = index % 48;
  }
}

void Cube::print() {
  for (size_t i = 0; i < 48; i++) {
    cout << pips[i]->data;
  }
  cout << endl;
}
