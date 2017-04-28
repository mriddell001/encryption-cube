//Cube.cpp
#include "cube.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>


using namespace std;

Cube::Cube() {
  int x[48] = {0,0,0,2,3,1,1,1,0,0,0,5,4,1,1,1,4,4,4,2,3,5,5,5,0,0,0,3,2,1,1,1,
               0,0,0,4,5,1,1,1,5,5,5,2,3,4,4,4};
  int y[48] = {0,1,2,1,1,0,1,2,3,4,5,4,4,3,4,5,0,1,2,10,10,0,1,2,6,7,8,7,7,6,7,
               8,9,10,11,10,10,9,10,11,8,7,6,4,4,8,7,6};

  for (int i = 0; i < 48; i++) {
    bands[x[i]][y[i]] = i;
  }
  propagate_connections();
}

void Cube::reset() {
  int x[48] = {0,0,0,2,3,1,1,1,0,0,0,5,4,1,1,1,4,4,4,2,3,5,5,5,0,0,0,3,2,1,1,1,
               0,0,0,4,5,1,1,1,5,5,5,2,3,4,4,4};
  int y[48] = {0,1,2,1,1,0,1,2,3,4,5,4,4,3,4,5,0,1,2,10,10,0,1,2,6,7,8,7,7,6,7,
               8,9,10,11,10,10,9,10,11,8,7,6,4,4,8,7,6};

  for (int i = 0; i < 48; i++) {
    bands[x[i]][y[i]] = i;
  }
  propagate_connections();
}

void Cube::propagate_connections() {
  int a, b, c, d, v, w, x, y;
  for (int i = 0; i < 6; i++) {
    if ((i+1)%3==0) {
      if (i<4) {a = 4; b = 5;}
      else {a = 5; b = 4;}
    }
    else {a = 0; b = 1;}

    if ((i+2)%3==0) {
      if (i<3) {c = 5; d = 4;}
      else {c = 4; d = 5;}
    }
    else {
      if (i!=3) {c = 2; d = 3;}
      else {c = 3; d = 2;}
    }

    switch (i) {
      case 1: {x = 3; y = 5; break;}
      case 3: {x = 6; y = 8; break;}
      case 4: {x = 9; y = 11; break;}
      case 5: {x = 8; y = 6; break;}
      default: {x = 0; y = 2;break;}
    }
    switch (i) {
      case 0: {v = 0; w = 2; break;}
      case 2: {v = 9; w = 11; break;}
      case 3: {v = 8; w = 6; break;}
      case 4: {v = 11; w = 9; break;}
      default: {v = 3; w = 5; break;}
    }
    bands[c][v] = bands[a][x];
    bands[d][v] = bands[a][y];
    bands[c][w] = bands[b][x];
    bands[d][w] = bands[b][y];
  }
}

void Cube::stringCube() {
  string b48 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv";
  for (int i = 0; i < 48; i++) {
    Pip *tmp = new Pip();
    pips.push_back(tmp);
    pips[i]->data = b48[i];
  }
}

string Cube::transformationDispatch(string a) {
  int n = a.length();
  for (int i = 0; i < n; i++) {
    int x = a[i];
    int y = x;

    x -= 65;
    y = x%2;
    x = x/2;
    switch (x) {
      case 0:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 1:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 2:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 3:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 4:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
      case 5:{ if(y == 0){clockwise(x);} else{counterclockwise(x);} break;}
    }
  }
  string b = print();
  reset();
  return b;
}

void Cube::clockwise(int a) {
  vector<int> x;
  vector<int> y;
  switch (a) {
    case 0://Top - Back, Right, Front, Left
    {//0(0-11) = 0(3-11,0-2)
      threeBack(a);
      for (int i = 0; i < 3; i++) {//2(11-9) => 4(0-2) && 3(11-9) => 5(0-2)
        x.push_back(bands[4][i]);
        y.push_back(bands[5][i]);
        bands[4][i] = bands[2][11-i];
        bands[5][i] = bands[3][11-i];
      }
      for (int i = 9; i < 12; i++) {//4(0-2) => 3(9-11) && 5(0-2) => 2(9-11)
        bands[3][i] = x[i-9];
        bands[2][i] = y[i-9];
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
        x.push_back(bands[2][i]);
        y.push_back(bands[3][i]);
        bands[2][i] = bands[4][11-i];
        bands[3][i] = bands[5][11-i];
      }
      for (int i = 6; i < 9; i++) {//2(3-5) => 5(6-8) && 3(3-5) => 4(6-8)
        bands[5][i] = x[i-6];
        bands[4][i] = y[i-6];
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
        x.push_back(bands[0][i]);
        y.push_back(bands[1][i]);
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
      bands[5][8] = bands[a][3];
      break;
    }
    case 3://Right - Top, Back, Bottom, Front
    {//3(0-11) = 3(3-11,0-2)
      threeBack(a);
      for (int i = 3; i < 6; i++) {//0(3-5) => 4(3-5) && 1(3-5) => 5(3-5)
        x.push_back(bands[0][i]);
        y.push_back(bands[1][i]);
        bands[0][i] = bands[5][8-i];
        bands[1][i] = bands[4][8-i];
      }
      for (int i = 3; i < 6; i++) {//5(5-3) => 0(3-5) && 4(5-3) => 1(3-5)
        bands[4][i] = x[i-3];
        bands[5][i] = y[i-3];
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
      for (int i = 6; i < 9; i++) {//3(6-8) => 0(6-8) && 2(6-8) => 1(6-8)
        x.push_back(bands[0][i]);
        y.push_back(bands[1][i]);
        bands[0][i] = bands[3][i];
        bands[1][i] = bands[2][i];
      }
      for (int i = 6; i < 9; i++) {//0(6-8) => 2(8-6) && 1(6-8) => 3(8-6)
        bands[2][i] = x[8-i];
        bands[3][i] = y[8-i];
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
      for (int i = 0; i < 3; i++) {//1(0-2) => 2(0-2) && 0(0-2) => 3(0-2)
        x.push_back(bands[2][i]);
        y.push_back(bands[3][i]);
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
      bands[1][11] = bands[a][9];
      bands[2][3] = bands[a][8];
      bands[2][11] = bands[a][0];
      bands[3][3] = bands[a][6];
      bands[3][11] = bands[a][2];
      break;
    }
  }
  x.erase (x.begin(),x.begin()+3);
  y.erase (y.begin(),y.begin()+3);
}

void Cube::counterclockwise(int a) {clockwise(a); clockwise(a); clockwise(a);}

void Cube::threeBack(int a) {
  vector<int> v;
  for (int i = 0; i < 3; i++) {v.push_back(bands[a][i]);}
  for (int i = 3; i < 12; i++) {bands[a][i-3] = bands[a][i];}
  for (int i = 9; i < 12; i++) {bands[a][i] = v[i-9];}
  v.erase (v.begin(),v.begin()+3);
}

void Cube::threeFront(int a) {
  vector<int> v;
  for (int i = 9; i < 12; i++) {v.push_back(bands[a][i]);}
  for (int i = 8; i > -1; i--) {bands[a][i+3] = bands[a][i];}
  for (int i = 0; i < 3; i++) {bands[a][i] = v[i];}
  v.erase (v.begin(),v.begin()+3);
}

string Cube::print() {
  string print_order = cube_order(), tmp, output_string = "";
  int index;
  for (int i = 0; i < 48; i++) {
    tmp = print_order.substr(i*2,2);
    index = stoi(tmp);
    output_string += pips[index]->data;
  }
  string a, b, c, d, abcd;
  a = output_string.substr(0,8);
  b = output_string.substr(11,2);
  c = output_string.substr(35,2);
  d = output_string.substr(24,8);
  abcd = a + b + c + d;
  return abcd;
  //return output_string;
}

string Cube::cube_order() {
  string d_order = "", pmt;
  int x[48] = {0,0,0,2,3,1,1,1,0,0,0,5,4,1,1,1,4,4,4,2,3,5,5,5,0,0,0,3,2,1,1,1,
               0,0,0,4,5,1,1,1,5,5,5,2,3,4,4,4};
  int y[48] = {0,1,2,1,1,0,1,2,3,4,5,4,4,3,4,5,0,1,2,10,10,0,1,2,6,7,8,7,7,6,7,
               8,9,10,11,10,10,9,10,11,8,7,6,4,4,8,7,6};
  int tmp;
  for (int i = 0; i < 48; i++) {
    tmp = bands[x[i]][y[i]];
    if (tmp < 10) {d_order += "0";}
    d_order += to_string(tmp);
  }
  return d_order;
}
