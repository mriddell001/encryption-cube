#include "locality.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

string Locality::randGen(vector<string>* v) {
  srand (time(NULL));
  string c48 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv";
  string sorder = "", tmp = c48;
  for (int i = 47; i > -1; i--) {
    int t;
    if (i > 0) {t = rand() % i;}
    else {t = 0;}
    sorder += tmp[t];
    if (tmp.length()>1) {
      tmp.erase(t,1);
    }
  }
  int rvalue = locCheck(sorder);
  if (rvalue) {
    return sorder;
  }
  else {return randGen(v);}
}

int Locality::locCheck(string data) {
  string c48 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv";
  string input = data;
  int corner_arrays[4][3] = {{0,21,34},{2,8,23},{5,39,40},{7,13,42}};
  int side_arrays[8][2] = {{1,22},{3,36},{4,11},{6,41},{25,17},{27,12},{28,35},{30,46}};

  int similar = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      string tmp = "", pmt = "";
      tmp += c48[corner_arrays[i][j]];
      pmt += input[corner_arrays[i][j]];
      if (tmp == pmt) {
        similar++;
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      string tmp = "", pmt = "";
      tmp += c48[side_arrays[i][j]];
      pmt += input[side_arrays[i][j]];
      if (tmp == pmt) {
        similar++;
      }
    }
  }
  if (similar == 48) {
    return 0;
  }
  else {
    return 1;
  }
}
