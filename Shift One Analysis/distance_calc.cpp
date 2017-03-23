#include <fstream>
#include <string>

using namespace std;

int main() {
  for (int i = 0; i < 6; i++) {
    string fileName = "output";
    string analysis = "calc";
    fileName += to_string(i);
    fileName += ".txt";
    analysis += to_string(i);
    analysis += ".txt";
    fstream istream (fileName, fstream::in);
    fstream ostream (analysis, fstream::out);
    string input = "";
    getline(istream, input);
    istream.close();
    for (int j = 0; j < input.length(); j++) {
      ostream << "Char: " << input[j] << "\tIndex: " << j << "\tDistance: ";
      if (input[j]-0 < 97) {
        ostream << j - (input[j]-65);
      }
      else {
        ostream << j - (input[j]-97);
      }
      ostream << endl;
    }
    ostream.close();
  }
  return 0;
}
