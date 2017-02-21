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
}
/* Front, Right, Top, Back, Left, Bottom */

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
  //Print faces in order: Front, Right, Top, Back, Left, Bottom
  /* Front
    band(0): 1, 2, 3
    band(2): 2
    band(3): 2
    band(1): 1, 2, 3 */
    stream << bands[0][0] << bands[0][1] << bands[0][2];
    stream << bands[2][1];
    stream << bands[3][1];
    stream << bands[1][0] << bands[1][1] << bands[1][2];

  /* Right
    band(0): 4, 5, 6
    band(4): 5
    band(5): 5
    band(1): 4, 5, 6 */
    stream << bands[0][3] << bands[0][4] << bands[0][5];
    stream << bands[4][4];
    stream << bands[5][4];
    stream << bands[1][3] << bands[1][4] << bands[1][5];

  /* Top
    band(5): 1, 2, 3
    band(2): 11
    band(3): 11
    band(4): 1, 2, 3 */
    stream << bands[5][0] << bands[5][1] << bands[5][2];
    stream << bands[2][10];
    stream << bands[3][10];
    stream << bands[4][0] << bands[4][1] << bands[4][2];

  /* Back
    band(0): 7, 8, 9
    band(2): 8
    band(3): 8
    band(1): 7, 8, 9 */
    stream << bands[0][6] << bands[0][7] << bands[0][8];
    stream << bands[2][7];
    stream << bands[3][7];
    stream << bands[1][6] << bands[1][7] << bands[1][8];

  /* Left
    band(0): 10, 11, 12
    band(5): 11
    band(4): 11
    band(1): 10, 11, 12 */
    stream << bands[0][9] << bands[0][10] << bands[0][11];
    stream << bands[5][10];
    stream << bands[4][10];
    stream << bands[1][9] << bands[1][10] << bands[1][11];

  /* Bottom
    band(4): 9, 8, 7
    band(2): 4
    band(3): 4
    band(5): 9, 8, 7 */
    stream << bands[4][8] << bands[4][7] << bands[4][6];
    stream << bands[2][3];
    stream << bands[3][3];
    stream << bands[5][8] << bands[5][7] << bands[5][6];

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
  for (size_t i = 0; i < a.length(); i++) {
    switch (a[i]) {
      case /* value */0:break;
      case /* value */1:break;
      case /* value */2:break;
      case /* value */3:break;
      case /* value */4:break;
      case /* value */5:break;
      default:
      {
        ofstream err ("error.txt", ofstream::out);
        err << "Error occured in transformationDispatch";
        err.close();
        exit;
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
