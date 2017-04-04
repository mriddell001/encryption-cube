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
* @return - Return Cube
*
* Notes: May be impacted by changing load order. Check when project reaches
*        applicable phase in development. Current load order: Front, Right, Top,
*        Back, Left, Bottom
*
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
*                   #   26  25  24  # <- Top Left Corner
*                   #################
*/
Cube::Cube() {
  int nums[72] = {0,  1,  2,  8,  9,  10, 24, 25, 26, 32, 33, 34,  //Band 0
                  5,  6,  7,  13, 14, 15, 29, 30, 31, 37, 38, 39,  //Band 1
                  0,  3,  5,  40, 43, 45, 31, 28, 26, 16, 19, 21,  //Band 2
                  2,  4,  7,  42, 44, 47, 29, 27, 24, 18, 20, 23,  //Band 3
                  16, 17, 18, 10, 12, 15, 47, 46, 45, 37, 35, 32,  //Band 4
                  21, 22, 23,  8, 11, 13, 42, 41, 40, 39, 36, 34}; //Band 5
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 12; j++) {
        bands[i][j] = nums[i*12+j];
    }
  }
}

/**
* Cube - Initial creation of cube.
* @param {fstream} stream - input stream to load cube with data.
* @return - Return Cube
*
*/
Cube::Cube(string cube_order) {
  int nums[72];
  for (int i = 0; i < 72; i++) {
    string tmp = "" + cube_order[i*2] + cube_order[i*2+1];
    int pmt = stoi(tmp);
    nums[i] = pmt;
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 12; j++) {
        bands[i][j] = nums[i*12+j];
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
  for (int i = 0; i < 48; i++) {
    Pip *tmp = new Pip();
    pips.push_back(tmp);
  }
  char ch;
  int index = 0;
  while (stream.get(ch)) {
    string str = "";
    str.push_back(ch);
    pips[index]->data += str;
    index++;
    index = index % 48;
  }
  if (index != 0) {
    while(index != 0) {
      pips[index]->data += " ";
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
void Cube::deconstructCube(fstream& stream) {
  print(stream);
}

/**
* transformationString - accept input string of cube manipulations.
* @param {string} stream - input string of cube transformations.
*/
void Cube::transformationString(string stream) {
  string a = "", b = "";

  if ((stream.length() % 2) == 0) {
    int slen = stream.length();
    for (int i = 0; i < slen; i++) {
      a += stream[i];
      b += stream[i+1];
      i++;
    }
  }
  else {
    string tmp = stream.substr(0, stream.length()-1);
    int tlen = tmp.length();
    for (int i = 0; i < tlen; i++) {
      a += stream[i];
      b += stream[i+1];
      i++;
    }
  }
  transformationDispatch(a, b);
}

/**
* transformationStream - accept input file of cube manipulations.
* @param {fstream} stream - input stream of cube transformations.
*/
void Cube::transformationStream(fstream& stream) {
  string a = "", b = "", tmp = "";

  while (getline(stream, tmp)) {
    a += tmp[0];
    b += tmp[1];
  }
  transformationDispatch(a, b);
}


/**
* transformationDispatch - function to take string of orders ()
* @param {String} a - string of faces to be opperated on
* @param {String} b - string indication clockwise or counterclockwise.
*/
void Cube::transformationDispatch(string a, string b) {
  for (unsigned int i = 0; i < a.size(); i++) {
    int x, y;
    x = a[i] - '0';
    y = b[i] - '0';
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
  x.erase (x.begin(),x.begin()+3);
  y.erase (y.begin(),y.begin()+3);
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
  v.erase (v.begin(),v.begin()+3);
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
  v.erase (v.begin(),v.begin()+3);
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
void Cube::print(fstream& stream) {
  vector<int> v;
  //Print faces in order: Front, Right, Top, Back, Left, Bottom
  /* Front - band(0): 0, 1, 2 | band(2): 1 | band(3): 1 | band(1): 0, 1, 2 */
  v.push_back(bands[0][0]); v.push_back(bands[0][1]); v.push_back(bands[0][2]);
  v.push_back(bands[2][1]);
  v.push_back(bands[3][1]);
  v.push_back(bands[1][0]); v.push_back(bands[1][1]); v.push_back(bands[1][2]);

/* Right - band(0): 3, 4, 5 | band(5): 4 | band(4): 4 | band(1): 3, 4, 5 */
  v.push_back(bands[0][3]); v.push_back(bands[0][4]); v.push_back(bands[0][5]);
  v.push_back(bands[5][4]);
  v.push_back(bands[4][4]);
  v.push_back(bands[1][3]); v.push_back(bands[1][4]); v.push_back(bands[1][5]);

/* Top - band(4): 0, 1, 2 | band(2): 10 | band(3): 10 | band(5): 0, 1, 2 */
  v.push_back(bands[4][0]); v.push_back(bands[4][1]); v.push_back(bands[4][2]);
  v.push_back(bands[2][10]);
  v.push_back(bands[3][10]);
  v.push_back(bands[5][0]); v.push_back(bands[5][1]); v.push_back(bands[5][2]);

/* Back - band(0): 6, 7, 8 | band(2): 7 | band(3): 7 | band(1): 6, 7, 8 */
  v.push_back(bands[0][6]); v.push_back(bands[0][7]); v.push_back(bands[0][8]);
  v.push_back(bands[3][7]);
  v.push_back(bands[2][7]);
  v.push_back(bands[1][6]); v.push_back(bands[1][7]); v.push_back(bands[1][8]);

/* Left - band(0): 9, 10, 11 | band(4): 10 | band(5): 10 | band(1): 9, 10, 11 */
  v.push_back(bands[0][9]); v.push_back(bands[0][10]); v.push_back(bands[0][11]);
  v.push_back(bands[4][10]);
  v.push_back(bands[5][10]);
  v.push_back(bands[1][9]); v.push_back(bands[1][10]); v.push_back(bands[1][11]);

/* Bottom - band(5): 8, 7, 6 | band(2): 4 | band(3): 4 | band(4): 8, 7, 6 */
  v.push_back(bands[5][8]); v.push_back(bands[5][7]); v.push_back(bands[5][6]);
  v.push_back(bands[2][4]);
  v.push_back(bands[3][4]);
  v.push_back(bands[4][8]); v.push_back(bands[4][7]); v.push_back(bands[4][6]);

    int index;
    for (auto it = begin(v); it!=end(v); ++it) {
      index = *it;
      stream << pips[index]->data;
    }
    v.erase (v.begin(),v.begin()+48);
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
void Cube::print() {
  vector<int> v;
  //Print faces in order: Front, Right, Top, Back, Left, Bottom
  /* Front - band(0): 0, 1, 2 | band(2): 1 | band(3): 1 | band(1): 0, 1, 2 */
  v.push_back(bands[0][0]); v.push_back(bands[0][1]); v.push_back(bands[0][2]);
  v.push_back(bands[2][1]);
  v.push_back(bands[3][1]);
  v.push_back(bands[1][0]); v.push_back(bands[1][1]); v.push_back(bands[1][2]);

/* Right - band(0): 3, 4, 5 | band(5): 4 | band(4): 4 | band(1): 3, 4, 5 */
  v.push_back(bands[0][3]); v.push_back(bands[0][4]); v.push_back(bands[0][5]);
  v.push_back(bands[5][4]);
  v.push_back(bands[4][4]);
  v.push_back(bands[1][3]); v.push_back(bands[1][4]); v.push_back(bands[1][5]);

/* Top - band(4): 0, 1, 2 | band(2): 10 | band(3): 10 | band(5): 0, 1, 2 */
  v.push_back(bands[4][0]); v.push_back(bands[4][1]); v.push_back(bands[4][2]);
  v.push_back(bands[2][10]);
  v.push_back(bands[3][10]);
  v.push_back(bands[5][0]); v.push_back(bands[5][1]); v.push_back(bands[5][2]);

/* Back - band(0): 6, 7, 8 | band(2): 7 | band(3): 7 | band(1): 6, 7, 8 */
  v.push_back(bands[0][6]); v.push_back(bands[0][7]); v.push_back(bands[0][8]);
  v.push_back(bands[3][7]);
  v.push_back(bands[2][7]);
  v.push_back(bands[1][6]); v.push_back(bands[1][7]); v.push_back(bands[1][8]);

/* Left - band(0): 9, 10, 11 | band(4): 10 | band(5): 10 | band(1): 9, 10, 11 */
  v.push_back(bands[0][9]); v.push_back(bands[0][10]); v.push_back(bands[0][11]);
  v.push_back(bands[4][10]);
  v.push_back(bands[5][10]);
  v.push_back(bands[1][9]); v.push_back(bands[1][10]); v.push_back(bands[1][11]);

/* Bottom - band(5): 8, 7, 6 | band(2): 4 | band(3): 4 | band(4): 8, 7, 6 */
  v.push_back(bands[5][8]); v.push_back(bands[5][7]); v.push_back(bands[5][6]);
  v.push_back(bands[2][4]);
  v.push_back(bands[3][4]);
  v.push_back(bands[4][8]); v.push_back(bands[4][7]); v.push_back(bands[4][6]);

    int index;
    string str = "";
    for (auto it = begin(v); it!=end(v); ++it) {
      index = *it;
      str += pips[index]->data;
    }
    cout << str << endl;
    v.erase (v.begin(),v.begin()+48);
}

void Cube::print_bands() {
  for (int i = 0; i < 6; i++) {
    for (int k = 0; k < 12; k++) {
      cout << bands[i][k] << "\t";
    }
    cout << endl;
  }
}
