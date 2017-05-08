#ifndef B64_H
#define B64_H

#include <string>

using namespace std;

class B64 {
public:
  string to_base64(string data);
  string from_base64(string data);
private:
  string b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
};

#endif // CUBE_H
