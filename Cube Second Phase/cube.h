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
  ~Cube();
  Cube(string cube_order);
  void initializeCube(fstream&);                      // streams in data
  void deconstructCube(ostream&);                     // streams out data
  int getSize(){return pips.size();}
  string transformationDispatch(string a);
  void overwriteOrder(string a);
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
  string c48 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv";
  int x[48] = {0,0,0,2,3,1,1,1,0,0,0,5,4,1,1,1,4,4,4,2,3,5,5,5,0,0,0,3,2,1,1,1,
               0,0,0,4,5,1,1,1,5,5,5,2,3,4,4,4};
  int y[48] = {0,1,2,1,1,0,1,2,3,4,5,4,4,3,4,5,0,1,2,10,10,0,1,2,6,7,8,7,7,6,7,
               8,9,10,11,10,10,9,10,11,8,7,6,4,4,8,7,6};
};

#endif // CUBE_H
