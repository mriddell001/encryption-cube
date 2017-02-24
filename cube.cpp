//Cube.cpp
#include "cube.h"
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

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
  print(stream);
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
    int x, y;
    x = a[i];
    y = b[i];
    switch (x) {
      case 0:{ if(y == 0){clockwise(x,y);} else{counterclockwise(x,y);} break;}
      case 1:{ if(y == 0){clockwise(x,y);} else{counterclockwise(x,y);} break;}
      case 2:{ if(y == 0){clockwise(x,y);} else{counterclockwise(x,y);} break;}
      case 3:{ if(y == 0){clockwise(x,y);} else{counterclockwise(x,y);} break;}
      case 4:{ if(y == 0){clockwise(x,y);} else{counterclockwise(x,y);} break;}
      case 5:{ if(y == 0){clockwise(x,y);} else{counterclockwise(x,y);} break;}
      default:
      {
        ofstream err ("error.txt", ofstream::out);
        err << "Error occured in transformationDispatch";
        err.close();
        break;
      }
    }
  }
}

bool Cube::clockwise(int a, int b) {
  /*
    Top - Back, Right, Front, Left
      0(0-11) = 0(3-11,0-2)
      2(9-11) = 4(2-0)
      3(9-11) = 5(2-0)
      4(0-2) = 3(9-11)
      5(0-2) = 2(9-11)
    Bottom - Front, Right, Back, Left
      1(0-11) = 1(3-11,0-2)
      2(3-5) = 4(8-6)
      3(3-5) = 5(8-6)
      4(6-8) = 3(3-5)
      5(6-8) = 2(3-5)
    Left - Top, Front, Bottom, Back
      2(0-11) = 2(3-11,0-2)
      0(9-11) = 4(9-11)
      1(9-11) = 5(9-11)
      4(9-11) = 1(11-9)
      5(9-11) = 0(11-9)
    Right - Top, Back, Bottom, Front
      3(0-11) = 3(3-11,0-2)
      0(9-11) = 4(9-11)
      1(9-11) = 5(9-11)
      4(9-11) = 1(11-9)
      5(9-11) = 0(11-9)
    Back - Top, Left, Bottom, Right
      4(0-11) = 4(3-11,0-2)
      0(6-8) = 2(8-6)
      1(6-8) = 3(8-6)
      2(6-8) = 0(6-8)
      3(6-8) = 1(6-8)
    Front - Top, Right, Bottom, Left
      5(0-11) = 5(3-11,0-2)
      0(0-2) = 2(2-0)
      1(0-2) = 3(2-0)
      2(0-2) = 1(0-2)
      3(0-2) = 0(0-2)
  */
  return true;
}

bool Cube::counterclockwise(int a, int b) {
  /* INCORRECT - NEEDS CORRECTION
    Top - Back, Right, Front, Left
      band(0)(0-11)
    Bottom - Front, Right, Back, Left
      band(1)(0-11)
    Left - Top, Front, Bottom, Back
      band(2)(0-11)
    Right - Top, Back, Bottom, Front
      band(3)(0-11)
    Back - Top, Left, Bottom, Right
      band(4)(0-11)
    Front - Top, Right, Bottom, Left
      band(5)(0-11)
  */
  return true;
}

void Cube::print(fstream& stream) {
  vector<int> v;
  //Print faces in order: Front, Right, Top, Back, Left, Bottom
  /* Front - band(0): 1, 2, 3 | band(2): 2 | band(3): 2 | band(1): 1, 2, 3 */
    v.push_back(bands[0][0]); v.push_back(bands[0][1]); v.push_back(bands[0][2]);
    v.push_back(bands[2][1]);
    v.push_back(bands[3][1]);
    v.push_back(bands[1][0]); v.push_back(bands[1][1]); v.push_back(bands[1][2]);

  /* Right - band(0): 4, 5, 6 | band(4): 5 | band(5): 5 | band(1): 4, 5, 6 */
    v.push_back(bands[0][3]); v.push_back(bands[0][4]); v.push_back(bands[0][5]);
    v.push_back(bands[4][4]);
    v.push_back(bands[5][4]);
    v.push_back(bands[1][3]); v.push_back(bands[1][4]); v.push_back(bands[1][5]);

  /* Top - band(5): 1, 2, 3 | band(2): 11 | band(3): 11 | band(4): 1, 2, 3 */
    v.push_back(bands[5][0]); v.push_back(bands[5][1]); v.push_back(bands[5][2]);
    v.push_back(bands[2][10]);
    v.push_back(bands[3][10]);
    v.push_back(bands[4][0]); v.push_back(bands[4][1]); v.push_back(bands[4][2]);

  /* Back - band(0): 7, 8, 9 | band(2): 8 | band(3): 8 | band(1): 7, 8, 9 */
    v.push_back(bands[0][6]); v.push_back(bands[0][7]); v.push_back(bands[0][8]);
    v.push_back(bands[2][7]);
    v.push_back(bands[3][7]);
    v.push_back(bands[1][6]); v.push_back(bands[1][7]); v.push_back(bands[1][8]);

  /* Left - band(0): 10, 11, 12 | band(5): 11 | band(4): 11 | band(1): 10, 11, 12 */
    v.push_back(bands[0][9]); v.push_back(bands[0][10]); v.push_back(bands[0][11]);
    v.push_back(bands[5][10]);
    v.push_back(bands[4][10]);
    v.push_back(bands[1][9]); v.push_back(bands[1][10]); v.push_back(bands[1][11]);

  /* Bottom - band(4): 9, 8, 7 | band(2): 4 | band(3): 4 | band(5): 9, 8, 7 */
    v.push_back(bands[4][8]); v.push_back(bands[4][7]); v.push_back(bands[4][6]);
    v.push_back(bands[2][3]);
    v.push_back(bands[3][3]);
    v.push_back(bands[5][8]); v.push_back(bands[5][7]); v.push_back(bands[5][6]);

    for (auto it = begin(v); it != end(v); ++it) {
      stream << pips[*it-1]->data;
    }
}
