#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
  for (int iterations = 0; iterations < 4; iterations++) {
    string input = "output";
    input += to_string(iterations);
    input += ".txt";

    string output = "output";
    output += to_string(iterations + 1);
    output += ".txt";

    if (iterations == 0) {
      fstream ostream (input, fstream::out);
      for (int i = 0; i < 6; i++) {
        string pmt = "";
        pmt += to_string(i);
        string cw, ccw;
        cw = pmt + "0";
        ccw = pmt + "1";
        if (i < 5) {
          ostream << cw << "\n" << ccw << "\n";
        }
        else {
          ostream << cw << "\n" << ccw;
        }
      }
      ostream.close();
    }

    fstream istream (input, fstream::in);
    fstream ostream (output, fstream::out);
    string tmp = "";
    string last = "";
    for (int i = 0; i < iterations+1; i++) {
      last += "51";
    }
    while (getline(istream,tmp)) {
      for (int i = 0; i < 6; i++) {
        string pmt = "";
        pmt += to_string(i);
        string cw, ccw;
        cw = tmp + pmt + "0";
        ccw = tmp + pmt + "1";
        if (i < 5) {
          ostream << cw << "\n" << ccw << "\n";
        }
        else {
          ostream << cw << "\n" << ccw;
        }
      }
      if (tmp != last) {
        ostream << endl;
        cout << "tmp: " << tmp << "\tlast: " << last << endl;
      }
      else {
        cout << "last: " << last << endl;
      }
    }
    istream.close();
    ostream.close();
  }
  return 0;
}
