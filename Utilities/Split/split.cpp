#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  string input = argv[1], in="";
  fstream istream (input, fstream::in);
  input = input.substr(0, input.size()-4);

  int index = 0, fsize=0;
  string output = input + "_p" + to_string(index) + ".txt";
  fstream ostream (output, fstream::out);
  while (getline(istream,in)) {
    if (fsize + in.size() + 1 < 52428800) {
      fsize += in.size() + 1;
    }
    else {
      index++;
      ostream.close();
      output = input + "_p" + to_string(index) + ".txt";
      ostream.open(output, fstream::out);
      fsize = in.size() + 1;
    }
    ostream << in << endl;
  }
  ostream.close();
  istream.close();
  return 0;
}
