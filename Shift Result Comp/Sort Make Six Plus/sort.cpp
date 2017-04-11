#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool sortFunction (string i,string j) {
  int a = i.length(), b = j.length();
  if (a==b) {return (i<j);}
  else {
    if (a<b) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int main() {
  string output = "six_length.txt";
  string input = "ci.txt";
  vector<string> s_vec;
  fstream ostream (output, fstream::out);
  fstream istream (input, fstream::in);
  string tmp = "";
  while (getline(istream,tmp)) {
    int count = tmp.length()/2;
    if (count == 5) {
      string converted = "";
      for (int i = 0; i < count; i++) {
        string pairing = "";
        pairing += tmp[i*2];
        pairing += tmp[i*2+1];
        int pmt = stoi(pairing);
        switch (pmt) {
          case 0:{converted+="A";break;}
          case 1:{converted+="B";break;}
          case 10:{converted+="C";break;}
          case 11:{converted+="D";break;}
          case 20:{converted+="E";break;}
          case 21:{converted+="F";break;}
          case 30:{converted+="G";break;}
          case 31:{converted+="H";break;}
          case 40:{converted+="I";break;}
          case 41:{converted+="J";break;}
          case 50:{converted+="K";break;}
          case 51:{converted+="L";break;}
        }
      }
      s_vec.push_back(converted);
      tmp = "";
    }
  }
  istream.close();
  sort (s_vec.begin(), s_vec.end(), sortFunction);
  for (vector<string>::iterator it=s_vec.begin(); it!=s_vec.end(); ++it)
    ostream << *it << '\n';
  ostream.close();
  s_vec.clear();
  return 0;
}
