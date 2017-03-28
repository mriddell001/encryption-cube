#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


bool fComp (string i,string j) { return (i<j); }

int main() {
  string output = "full_list.txt";
  vector<string> s_vec;
  fstream ostream (output, fstream::out);
  for (int iterations = 0; iterations < 5; iterations++) {
    string input = "output";
    input += to_string(iterations);
    input += ".txt";

    fstream istream (input, fstream::in);
    string tmp = "";
    while (getline(istream,tmp)) {
      s_vec.push_back(tmp);
    }
    istream.close();
  }
  sort (s_vec.begin(), s_vec.end(), fComp);
  for (vector<string>::iterator it = s_vec.begin(); it != s_vec.end(); ++it) {
    ostream << *it << endl;
  }
  ostream.close();
  return 0;
}
