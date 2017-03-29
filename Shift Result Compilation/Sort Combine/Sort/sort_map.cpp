#include <fstream>
#include <string>
#include <map>
#include <iostream>

using namespace std;


bool fComp (string i,string j) { return (i<j); }

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
      if (it_value.compare(b) > 0) {
        s_map[a] = b;
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
