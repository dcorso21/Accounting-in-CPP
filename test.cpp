// Live Demo
#include <iostream>
#include <ctime>

using namespace std;

// function to generate and retrun random numbers.
int * getArray() {
    static int r[4] = {1,2,3,4};
    return r;
}




// main function to call above defined function.
int main () {
   int *p;
   p = getArray();
   for ( int i = 0; i < 4; i++ ) {
      cout << *(p + i) << endl;
   }
   return 0;
