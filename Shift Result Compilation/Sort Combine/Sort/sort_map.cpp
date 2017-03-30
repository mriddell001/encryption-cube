#include <fstream>
#include <string>
#include <map>
#include <iostream>

using namespace std;


int fComp (string i,string j) {
  int ta=0, tb=0;
  for (int k = 0; k < i.length()/2; k++) {
    string w, x, y, z;
    w = i[k];
    x = i[k+1];
    y = j[k];
    z = j[k+1];
    int a, b, c, d;
    std::string::size_type sz;
    a = stoi(w);
    b = stoi(y);
    c = stoi(x);
    d = stoi(z);
    switch (a) {
      case 0: {if (c == 0) {ta += 1;}else {ta -= 1;}break;}
      case 1: {if (c == 0) {ta += 10;}else {ta -= 10;}break;}
      case 2: {if (c == 0) {ta += 100;}else {ta -= 100;}break;}
      case 3: {if (c == 0) {ta += 1000;}else {ta -= 1000;}break;}
      case 4: {if (c == 0) {ta += 10000;}else {ta -= 10000;}break;}
      case 5: {if (c == 0) {ta += 100000;}else {ta -= 100000;}break;}
    }
    switch (b) {
      case 0: {if (d == 0) {tb += 1;}else {tb -= 1;}break;}
      case 1: {if (d == 0) {tb += 10;}else {tb -= 10;}break;}
      case 2: {if (d == 0) {tb += 100;}else {tb -= 100;}break;}
      case 3: {if (d == 0) {tb += 1000;}else {tb -= 1000;}break;}
      case 4: {if (d == 0) {tb += 10000;}else {tb -= 10000;}break;}
      case 5: {if (d == 0) {tb += 100000;}else {tb -= 100000;}break;}
    }
    k++;
  }
  if (ta == tb) {
    return 0;
  }
  else if (abs(ta) < abs(tb)) {
    return -1;
  }
  else {
    return 1;
  }
}

int main() {
  string output = "t_sorted.txt";
  string input = "total_output.txt";
  map<string,string> s_map;
  map<string,string>::iterator it;
  fstream ostream (output, fstream::out);
  fstream istream (input, fstream::in);
  string tmp = "", a, b;
  while (getline(istream,tmp)) {
    a = tmp.substr(0, tmp.find("\t"));
    tmp.erase(0, tmp.find("\t")+1);
    b = tmp;

    it = s_map.find(a);
    if (s_map.empty()) {
        s_map.insert(pair<string,string>(a,b));
    }
    else if (it != s_map.end()){
      string it_value = it->second;
      if (it_value.length() > b.length()) {
        s_map[a] = b;
      }
      else if (it_value.length() == b.length()) {
        int x = fComp(it_value, b);
        if (x == 1) {
          s_map[a] = b;
        }
        else if (it_value.compare(b) < 0) {
          s_map[a] = b;
        }
      }
    }
    else {
      s_map.insert(pair<string,string>(a,b));
    }
  }
  istream.close();
  for (map<string,string>::iterator it=s_map.begin(); it!=s_map.end(); ++it)
    ostream << it->first << "\t" << it->second << '\n';
  ostream.close();
  s_map.clear();
  return 0;
}
