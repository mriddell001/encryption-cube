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
  void stringCube();
  void reset();
  string transformationDispatch(string a);
  string print();                        // prints out data
private:
  string cube_order();
  void propagate_connections();
  void clockwise(int a);
  void counterclockwise(int a);
  void threeBack(int a);
  void threeFront(int a);
  class Pip {                                         // Represents on square on the cube
    public:
      string data;
      Pip(){};
      ~Pip();
    };
  vector<Pip*> pips;                                   // data storage
  int bands[6][12];
};

#endif // CUBE_H
