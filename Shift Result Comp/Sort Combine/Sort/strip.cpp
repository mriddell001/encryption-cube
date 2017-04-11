#include <fstream>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main() {
  string output = "correct_inputs.txt";
  string input = "t_sorted.txt";
  map<string,int> s_map;
  map<string,int>::iterator it;
  fstream ostream (output, fstream::out);
  fstream istream (input, fstream::in);
  string tmp = "";
  while (getline(istream,tmp)) {
    tmp.erase(0, tmp.find("\t")+1);

    if (s_map.empty()) {
        s_map.insert(pair<string,int>(tmp,0));
    }
    else {
      it = s_map.find(tmp);
      if (it == s_map.end()) {
        s_map.insert(pair<string,int>(tmp,0));
      }
    }
    //Implied else: Value has been found, shorter instruction length exist.
  }
  istream.close();
  for (map<string,int>::iterator it=s_map.begin(); it!=s_map.end(); ++it) {
    ostream << it->first;
    if (it->first != "5131513151") {
      ostream << endl;
    }
  }

  ostream.close();
  s_map.clear();
  return 0;
}
