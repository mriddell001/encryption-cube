#include "b64.h"
#include <bitset>
#include <string>

using namespace std;

string B64::to_base64(string data) {
  string b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  string data64="",binary="", tmp, pmt = data;
  int count = data.length()/2, number;
  for (int i = 0; i < count; i++) {
    tmp = pmt.substr(i*2, 2);
    number = stoi(tmp);
    if (number < 26) {binary += std::bitset<8>(number+65).to_string();}
    else {binary += std::bitset<8>(number+71).to_string();}
    while (binary.length()>5) {
      tmp = binary.substr(0,6);
      binary = binary.substr(6,binary.length()-6);
      number = std::stoi(tmp, nullptr, 2);
      data64 += b64[number];
    }
  }
  return data64;
}

string B64::from_base64(string data) {
  string b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  string rdata="",binary="", tmp;
  int count = data.length(), number;

  for (int i = 0; i < count; i++) {
    size_t index = b64.find(data[i]);
    tmp = std::bitset<8>(index).to_string();
    tmp = tmp.substr(2,6);
    binary += tmp;
    while (binary.length()>7) {
      tmp = binary.substr(0,8);
      binary = binary.substr(8,binary.length()-8);
      number = std::stoi(tmp, nullptr,2);
      if (number > 96) {number-=71; rdata += to_string(number);}
      else {number-=65; if (number < 10) {rdata += "0";} rdata += to_string(number);}
    }
  }
  return rdata;
}
