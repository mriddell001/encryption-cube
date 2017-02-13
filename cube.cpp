//Cube.cpp
#include "cube.h"
#include <string>
#include <vector>
#include <fstream>

/************************/
/*   Debug only:   */
#include <iostream>
/************************/

using namespace std;

Cube::Cube() {
  int nums[72] = {1,2,3,9,10,11,25,26,27,33,34,35,6,7,8,14,15,16,30,31,32,40,41,
                  42,1,4,6,41,44,46,25,28,30,17,20,22,3,5,8, 43,45,48, 27,29,32,
                  19,21,24,22,23,24,9,12,14,43,42,41,40,37,35,17,18,19,11,13,16,
                  48,47,46,38,36,33};
  int j = -1;
  int l = 0;
  for (size_t i = 0; i < 48; i++) {
    if ((i % 8) == 0) {j++;}
    Pip *tmp = new Pip(i, j);
    pips.push_back(tmp);
  }
  for (size_t i = 0; i < 6; i++) {
    for (size_t k = 0; k < 12; k++) {
        bands[i][k] = nums[l];
        l++;
    }
  }
  /* Front, Right, Top, Back, Left, Bottom */
}

void Cube::initializeCube(fstream& stream) {
  char ch;
  int index = 0;
  while (stream.get(ch)) {
    string str;
    str.push_back(ch);
    pips[index]->data += str;

    index++;
    index = index % 48;
  }
}

void Cube::deconstructCube(fstream& stream) {
  //Print faces in order:
  /* Front, Right, Top, Back, Left, Bottom */
}

void Cube::transformationStream(fstream& stream) {
  char face;
  char direction;
  string a, b;

  while (stream.get(face)) {
    stream.get(direction);
    a.push_back(face);
    b.push_back(direction);
  }

}

void Cube::transformationDispatch(string a, string b) {
  for (size_t i = 0; i < a.count; i++) {
    switch (a[i]) {
      case /* value */:
      case /* value */:
      case /* value */:
      case /* value */:
      case /* value */:
      case /* value */:
      default:
      {
        ofstream err ("error.txt", ofstream::out);
        err << "Error occured in transformationDispatch";
        err.close();
        exit 1;
      }
    }
  }
}

void Cube::print() {
  for (size_t i = 0; i < 48; i++) {
    cout << pips[i]->data;
  }
  cout << endl;
}
