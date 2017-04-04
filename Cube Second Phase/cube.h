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
  void deconstructCube(fstream&);                     // streams out data
  int getSize(){return pips.size();}
  void transformationStream(fstream&);                // streams in movement data
  void transformationString(string stream);
  void transformationDispatch(string a, string b);
  void print(fstream& stream);                        // prints out data
  void print();
  void clockwise(int a);
  void counterclockwise(int a);
  void threeBack(int a);
  void threeFront(int a);
  void print_bands();
private:
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
