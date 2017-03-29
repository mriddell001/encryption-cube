#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
  fstream ostream ("text.txt", fstream::out);
  string file;
  for (int i = 0; i < 6; i++) {
    file = "";
    file = "transformation";
    file += to_string(i);
    file += ".txt";
    cout << file << endl;
    fstream tstream (file, fstream::out);
    tstream << i << "0";
    tstream.close();
    ostream << "0 basic.txt\n";
    ostream << "1 transformation" << i << ".txt\n";
    ostream << "2 output" << i << ".txt\n";
  }
  return 0;
}
