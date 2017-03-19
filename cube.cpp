//Cube.cpp
#include "cube.h"
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;


/**
* Cube - Initial creation of cube.
*
* Notes: May be impacted by changing load order. Check when project reaches
*        applicable phase in development.
*/
Cube::Cube() {
  int nums[72] = {1,2,3,9,10,11,25,26,27,33,34,35,6,7,8,14,15,16,30,31,32,40,41,
                  42,1,4,6,41,44,46,25,28,30,17,20,22,3,5,8, 43,45,48, 27,29,32,
                  19,21,24,22,23,24,9,12,14,43,42,41,40,37,35,17,18,19,11,13,16,
                  48,47,46,38,36,33};
  int j = -1;
  int l = 0;
  for (int i = 0; i < 48; i++) {
    if ((i % 8) == 0) {j++;}
    Pip *tmp = new Pip(i, j);
    pips.push_back(tmp);
  }
  for (int i = 0; i < 6; i++) {
    for (int k = 0; k < 12; k++) {
        bands[i][k] = nums[l];
        l++;
    }
  }
}


/**
* initializeCube - function to take input stream and load cube with strings of
*                  data in the order: Front, Right, Top, Back, Left, Bottom
* @param {fstream} stream - input stream to load cube with data.
*
* Notes: Will be impacted by changing load order. Check when project reaches
*        applicable phase in development.
*/
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
  if (index != 0) {
    for (int i = 0; i < 48; i++) {
      pips[i]->data += " ";
    }
  }
}


/**
* deconstructCube - function to print cube to output file.
* @param {fstream} stream - output stream to offload cube data.
*
* Notes: Deconstruction cube should also call the destructor for the cube. This
*        still needs to be implimented.
*/
void Cube::deconstructCube(fstream& stream) {
  print(stream);
}


/**
* transformationStream - accept input file of cube manipulations.
* @param {fstream} stream - input stream of cube transformations.
*/
void Cube::transformationStream(fstream& stream) {
  char face;
  char direction;
  string a, b, nl;

  a = "";
  b = "";

  while (stream.get(face)) {
    stream.get(direction);
    a += face;
    b += direction;
    if (stream.peek() != EOF) {
      stream.get(nl);
    }
  }
  transformationDispatch(a, b);
}


/**
* transformationDispatch - function to take string of orders ()
* @param {String} a - string of faces to be opperated on
* @param {String} b - string indication clockwise or counterclockwise.
*/
void Cube::transformationDispatch(string a, string b) {
  for (int i = 0; i < a.length(); i++) {
    int x, y;
    x = (int)(a[i]);
    y = (int)(b[i]);
    switch (x) {
      case 0:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 1:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 2:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 3:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 4:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 5:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      default:
      {//If input if formatted correctly, this should never trigger.
        ofstream err ("error.txt", ofstream::out);
        err << "Error occured in transformationDispatch";
        err.close();
        break;
      }
    }
  }
}


/**
* clockwise - function that takes an instruction for which face to opperate on
*             and it preforms the shifting of the indicators in the clockwise
*             direction
* @param {Int} a - numerical indicator of which face to manipulate.
*
* Notes: cases including function threeFront are incomplete, cases containing
*        threeBack are complete.
*/
void Cube::clockwise(int a) {
  int x[3];
  int y[3];
  switch (a) {
    case 0://Top - Back, Right, Front, Left
    {//0(0-11) = 0(3-11,0-2)
      threeBack(a);
      for (int i = 9; i < 12; i++) {//5(0-2) => 2(9-11) && 4(0-2) => 3(9-11)
        x[i-9] = bands[2][i];
        y[i-9] = bands[3][i];
        bands[2][i] = bands[5][i-9];
        bands[3][i] = bands[4][i-9];
      }
      for (int i = 0; i < 3; i++) {//2(11-9) => 4(0-2) && 3(11-9) => 5(0-2)
        bands[4][i] = x[2-i];
        bands[5][i] = y[2-i];
      }
      bands[2][0] = bands[a][0];
      bands[2][8] = bands[a][8];
      bands[3][0] = bands[a][2];
      bands[3][8] = bands[a][6];
      bands[4][3] = bands[a][5];
      bands[4][11] = bands[a][9];
      bands[5][3] = bands[a][3];
      bands[5][11] = bands[a][11];
      break;
    }
    case 1://Bottom - Front, Right, Back, Left
    {//1(0-11) = 1(9-11,0-8)
      //Take the last three elements and move them to the front of the array.
      threeFront(a);
      for (int i = 3; i < 6; i++) {//4(8-6) => 2(3-5) && 5(8-6) => 3(3-5)
        x[i-3] = bands[2][i];
        y[i-3] = bands[3][i];
        bands[2][i] = bands[4][11-i];
        bands[3][i] = bands[5][11-i];
      }
      for (int i = 6; i < 9; i++) {//2(5-3) => 5(6-8) && 3(11-9) => 4(0-2)
        bands[5][i] = x[8-i];
        bands[4][i] = y[8-i];
      }
      bands[2][2] = bands[a][0];
      bands[2][6] = bands[a][8];
      bands[3][2] = bands[a][2];
      bands[3][6] = bands[a][6];
      bands[4][5] = bands[a][5];
      bands[4][9] = bands[a][9];
      bands[5][5] = bands[a][3];
      bands[5][9] = bands[a][11];
      break;
    }
    case 2://Left - Top, Front, Bottom, Back
    {//2(0-11) = 2(9-11,0-8)
      //Take the last three elements and move them to the front of the array.
      threeFront(a);
      for (int i = 9; i < 12; i++) {//5(9-11) => 1(9-11) && 4(9-11) => 0(9-11)
        x[i-9] = bands[0][i];
        y[i-9] = bands[1][i];
        bands[0][i] = bands[4][i];
        bands[1][i] = bands[5][i];
      }
      for (int i = 9; i < 12; i++) {//0(11-9) => 5(9-11) && 3(11-9) => 4(9-11)
        bands[5][i] = x[11-i];
        bands[4][i] = y[11-i];
      }
      bands[0][0] = bands[a][0];
      bands[0][8] = bands[a][8];
      bands[1][0] = bands[a][2];
      bands[1][8] = bands[a][6];
      bands[4][0] = bands[a][9];
      bands[4][8] = bands[a][5];
      bands[5][0] = bands[a][11];
      bands[5][8] = bands[a][6];
      break;
    }
    case 3://Right - Top, Back, Bottom, Front
    {//3(0-11) = 3(3-11,0-2)
      threeBack(a);
      for (int i = 3; i < 6; i++) {//0(3-5) => 4(3-5) && 1(3-5) => 5(3-5)
        x[i-3] = bands[4][i];
        y[i-3] = bands[5][i];
        bands[4][i] = bands[0][i];
        bands[5][i] = bands[1][i];
      }
      for (int i = 3; i < 6; i++) {//5(5-3) => 0(3-5) && 4(5-3) => 1(3-5)
        bands[1][i] = x[8-i];
        bands[0][i] = y[8-i];
      }
      bands[0][2] = bands[a][0];
      bands[0][6] = bands[a][8];
      bands[1][2] = bands[a][2];
      bands[1][6] = bands[a][6];
      bands[4][2] = bands[a][9];
      bands[4][6] = bands[a][5];
      bands[5][2] = bands[a][11];
      bands[5][6] = bands[a][3];
      break;
    }
    case 4://Back - Top, Left, Bottom, Right
    {//4(0-11) = 4(3-11,0-2)
      threeBack(a);
      for (int i = 6; i < 9; i++) {//0(8-6) => 2(6-8) && 1(8-6) => 3(6-8)
        x[i-6] = bands[2][i];
        y[i-6] = bands[3][i];
        bands[2][i] = bands[0][14-i];
        bands[3][i] = bands[1][14-i];
      }
      for (int i = 6; i < 9; i++) {//2(6-8) => 1(6-8) && 3(6-8) => 0(6-8)
        bands[1][i] = x[i-6];
        bands[0][i] = y[i-6];
      }
      bands[0][5] = bands[a][3];
      bands[0][9] = bands[a][11];
      bands[1][5] = bands[a][5];
      bands[1][9] = bands[a][9];
      bands[2][5] = bands[a][8];
      bands[2][9] = bands[a][0];
      bands[3][5] = bands[a][6];
      bands[3][9] = bands[a][2];
      break;
    }
    case 5://Front - Top, Right, Bottom, Left
    {//5(0-11) = 5(9-11,0-8)
      //Take the last three elements and move them to the front of the array.
      threeFront(a);
      for (int i = 0; i < 3; i++) {//5(9-11) => 1(9-11) && 4(9-11) => 0(9-11)
        x[i] = bands[2][i];
        y[i] = bands[3][i];
        bands[2][i] = bands[1][i];
        bands[3][i] = bands[0][i];
      }
      for (int i = 0; i < 3; i++) {//0(11-9) => 5(9-11) && 3(11-9) => 4(9-11)
        bands[0][i] = x[2-i];
        bands[1][i] = y[2-i];
      }
      bands[0][3] = bands[a][3];
      bands[0][11] = bands[a][11];
      bands[1][3] = bands[a][5];
      bands[1][11] = bands[a][2];
      bands[2][3] = bands[a][8];
      bands[2][11] = bands[a][0];
      bands[3][3] = bands[a][6];
      bands[3][11] = bands[a][2];
      break;
    }
  }
  return true;
}


/**
* main - accept input file of instructions.
* @param {Int} argc - number of arguments.
* @param {Char Array} argv - char arrays containing commandline input.
* @returns {Int}
*/
void Cube::counterclockwise(int a) {
  clockwise(a);
  clockwise(a);
  clockwise(a);
  return true;
}


/**
* main - accept input file of instructions.
* @param {Int} argc - number of arguments.
* @param {Char Array} argv - char arrays containing commandline input.
* @returns {Int}
*/
void Cube::threeBack(int a) {
  int swap[3];
  for (int i = 0; i < 3; i++) {
    swap[i] = bands[a][i];
  }
  for (int i = 3; i < 10; i++) {
    bands[a][i] = bands[a][i+1];
  }
  for (int i = 10; i < 13; i++) {
    bands[a][i] = swap[i-10];
  }
  return true;
}


/**
* main - accept input file of instructions.
* @param {Int} argc - number of arguments.
* @param {Char Array} argv - char arrays containing commandline input.
* @returns {Int}
*/
void Cube::threeFront(int a) {
  int swap[3];
  for (int i = 9; i < 12; i++) {
    swap[i] = bands[a][i];
  }
  for (int i = 11; i > 2; i++) {
    bands[a][i] = bands[a][i-3];
  }
  for (int i = 0; i < 3; i++) {
    bands[a][i] = swap[i];
  }
  return true;
}


/**
* main - accept input file of instructions.
* @param {Int} argc - number of arguments.
* @param {Char Array} argv - char arrays containing commandline input.
* @returns {Int}
*/
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
