#ifndef LOCALITY_H
#define LOCALITY_H

#include <string>
#include <vector>

using namespace std;

class Locality {
public:
  string randGen(vector<string>* v);
  int locCheck(string data);
};

#endif // LOCALITY_H
