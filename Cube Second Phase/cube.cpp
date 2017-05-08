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

/**
* Cube - Initial creation of cube.
* @return - Return Cube
*/
Cube::Cube() {
  for (int i = 0; i < 48; i++) {
    bands[x[i]][y[i]] = i;
  }
  propagate_connections();
}

/**
* Cube - Initial creation of cube.
* @param {fstream} stream - input stream to load cube with data.
* @return - Return Cube
*
*/
Cube::Cube(string cube_order) {
  for (int i = 0; i < 48; i++) {
    string tmp = cube_order.substr(i,1);
    int number = c48.find(tmp);
    istringstream (tmp) >> number;
    bands[x[i]][y[i]] = number;
  }
  propagate_connections();
}

Cube::~Cube() {
  pips.erase(pips.begin(), pips.end());
}

/**
* propagate_connections - Take filled bands and connect related.
*/
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

/**
* overwriteOrder - Take old order and allign to new input order.
* @param {String} a - Previous order of cube.
*/
void Cube::overwriteOrder(string a) {
  string co = cube_order();
  for (int i = 0; i < 48; i++) {
    string os, ns;
    int oi, ni;
    ns = a.substr(i,1);     //The value at index i in string a.
    ni = c48.find(ns);      //Is the number found in c48.

    os = co.substr(ni,1);   //The value at index ni in string co.
    oi = c48.find(os);      //Is the number found in c48.

    bands[x[i]][y[i]] = oi; //Move the value in the old string at the index from the new to the new index.
  }
  propagate_connections();
}

void Cube::primeOrder() {
  string co = cube_order();
  for (int i = 0; i < 48; i++) {
    int index = 
    bands[x[i]][y[i]] = i;
  }
  propagate_connections();
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
  //*********************************PROBLEM IS IN HERE
  for (int i = 0; i < 48; i++) {
    Pip *tmp = new Pip();
    pips.push_back(tmp);
  }
  char ch, pa;
  int index = 0, p;
  while (stream.get(ch)) {
    string str = "";
    str.push_back(ch);
    pips[index]->data += str;
    index++;
    index = index % 48;
  }
  if (index != 0) {
    while(index != 0) {
      p = rand() % 95 + 32;
      pa = '0' + p;
      string pad;
      pad.push_back(pa);
      pips[index]->data += pad;
      index++;
      index = index % 48;
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
void Cube::deconstructCube(ostream& stream) {
  print(stream);
}

/**
* transformationDispatch - function to take string of orders ()
* @param {String} a - string of faces to be opperated on
* @param {String} b - string indication clockwise or counterclockwise.
*/
string Cube::transformationDispatch(string a) {
  string b = a;
  int n = a.length();
  for (int i = 0; i < n; i++) {
    if (i < n/2) {swap(b[i], b[n-i-1]);}
    string ab = a.substr(i,1);
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
  for (int i = 0; i < n; i++) {
    if (b[i]%2==1) {
      b[i]++;
    }
    else {
      b[i]--;
    }
  }
  return b;
}


/**
* clockwise - function that takes an instruction for which face to opperate on
*             and it preforms the shifting of the indicators in the clockwise
*             direction
* @param {Int} a - numerical indicator of which face to manipulate.
*
* Notes: All cases are complete. Next step is to confirm by testing each case.
*        Case 0 is confirmed. Entire function needs reworked with vector instead
*        of array.
*/
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
  x.erase(x.begin(),x.end());
  y.erase(y.begin(),y.end());
}


/**
* counterclockwise - function that takes an instruction for which face to
*                    opperate on and it preforms the shifting of the indicators
*                    in the counterclockwise direction
* @param {Int} a - numerical indicator of which face to manipulate.
*
* Notes: This function cheats by calling the clockwise function three times.
*        This works because the changes are equal.
*/
void Cube::counterclockwise(int a) {clockwise(a); clockwise(a); clockwise(a);}


/**
* threeBack - accepts a band to move three elements to the back of the array.
* @param {Int} a - numerical indicator of which face to manipulate.
*/
void Cube::threeBack(int a) {
  vector<int> v;
  for (int i = 0; i < 3; i++) {v.push_back(bands[a][i]);}
  for (int i = 3; i < 12; i++) {bands[a][i-3] = bands[a][i];}
  for (int i = 9; i < 12; i++) {bands[a][i] = v[i-9];}
  v.erase(v.begin(),v.end());
}


/**
* threeFront - accepts a band to move three elements to the front of the array.
* @param {Int} a - numerical indicator of which face to manipulate.
*/
void Cube::threeFront(int a) {
  vector<int> v;
  for (int i = 9; i < 12; i++) {v.push_back(bands[a][i]);}
  for (int i = 8; i > -1; i--) {bands[a][i+3] = bands[a][i];}
  for (int i = 0; i < 3; i++) {bands[a][i] = v[i];}
  v.erase(v.begin(),v.end());
}


/**
* print - outputs the data on the cube in the face order that it was entered.
* @param {fstream} stream - output stream to send the data from the cube.
*
* Notes: If the face order is changed then this hard coding will not work. this
*        only works in the case where the input order is: Front, Right, Top,
*        Back, Left, Bottom.
*                   #################
*                   #   Top         #
*                   #   16  17  18  #
*                   #   19  $   20  #
*                   #   21  22  23  #
* ####################################################
* #   Left          #   Front       #   Right        #
* #   32  33  34    #   0   1   2   #   8   9   10   #
* #   35  $   36    #   3   $   4   #   11  $   12   #
* #   37  38  39    #   5   6   7   #   13  14  15   #
* ####################################################
*                   #   Bottom      #
*                   #   40  41  42  #
*                   #   43  $   44  #
*                   #   45  46  47  #
*                   #################
*                   #   Back        #
*                   #   31  30  29  #
*                   #   28  $   27  #
*                   #   26  25  24  #
*                   #################
*/
void Cube::print(ostream& stream) {
  string print_order = cube_order(), tmp, output_string = "";
  int index;
  for (int i = 0; i < 48; i++) {
    tmp = print_order[i];
    index = c48.find(tmp);
    output_string += pips[index]->data;
  }
  stream << output_string;
}

/**
* screenprint - calls print with cout.
*
* Notes: If the face order is changed then this hard coding will not work. this
*        only works in the case where the input order is: Front, Right, Top,
*        Back, Left, Bottom.
*/
void Cube::screenprint() {
  print(cout);
}

string Cube::cube_order() {
  string d_order = "", pmt;
  int tmp;
  for (int i = 0; i < 48; i++) {
    tmp = bands[x[i]][y[i]];
    d_order += c48[tmp];
  }
  return d_order;
}

void Cube::print_bands(ostream& stream) {
  for (int i = 0; i < 6; i++) {
    for (int k = 0; k < 12; k++) {
      cout << bands[i][k] << "\t";
    }
    cout << endl;
  }
}
