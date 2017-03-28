#include <fstream>
#include <string>
#include <math.h>

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
        int d_right = j - (input[j]-65);
        int d_left = (input[j]-65) -j;
        int a_right, a_left;
        a_right = abs(d_right);
        a_left = abs(d_left);
        if (a_right < a_left) {
          ostream << a_right;
        }
        else {
          ostream << d_left;
        }
      }
      else {
        int d_right = j - (input[j]-97);
        int d_left = (input[j]-97) -j;
        int a_right, a_left;
        a_right = abs(d_right);
        a_left = abs(d_left);
        if (a_right < a_left) {
          ostream << a_right;
        }
        else {
          ostream << d_left;
        }
      }
      ostream << endl;
    }
    ostream.close();
  }
  return 0;
}
