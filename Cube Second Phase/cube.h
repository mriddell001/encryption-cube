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
  Cube(string cube_order);
  void initializeCube(fstream&);                      // streams in data
  void deconstructCube(ostream&);                     // streams out data
  int getSize(){return pips.size();}
  string transformationDispatch(string a);
  void print(ostream& stream);                        // prints out data
  void print(ostream& stream, string cube_order);
  void screenprint();
  string cube_order();
  void print_bands(ostream& stream);
private:
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
