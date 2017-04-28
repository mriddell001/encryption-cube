#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  string input = argv[1], in="", base, output;
  input = input.substr(0, input.size()-4);
  int loc_num = input.find("_p");
  int index = stoi(input.substr(loc_num+2, input.size()-loc_num+2));
  base = input.substr(0,loc_num);
  output = base + ".txt";
  fstream ostream (output, fstream::out);
  for (int i = 0; i < index+1; i++) {
    string input = base + "_p" + to_string(i) + ".txt";
    fstream istream (input, fstream::in);
    while (getline(istream,in)) {
      ostream << in << endl;
    }
    istream.close();
  }
  ostream.close();
  return 0;
}
