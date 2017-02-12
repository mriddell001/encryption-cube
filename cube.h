//Cube.h
#ifndef CUBE_H
#define CUBE_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Cube {
public:
  Cube();
  void initializeCube(fstream&);       // reads in data
  int getSize(){return pips.size();}
  void print();                          // prints out data
private:
  class Pip {                            // Represents on square on the cube
  public:
    string data;
    int location;
    Pip(int i){location = i;};
    ~Pip();
  };
  vector<Pip*> pips;             // data storage
};

#endif // CUBE_H
