#include <fstream>

using namespace std;

int main()
{
  fstream fs ("prime_list.txt", fstream::out);
	for (unsigned int i = 2; i < 65535; i++) {
    bool prime = true;
	  for (unsigned int j = 2; j <= i/2; j++) {
	    if (i != j) {
        if (i % j == 0) {
          prime = false;
        }
      }
	  }
    if (prime == true) {
      fs << i << endl;
    }
	}
  fs.close();
	return 0;
}
