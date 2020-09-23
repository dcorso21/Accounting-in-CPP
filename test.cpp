// Live Demo
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

// function to generate and retrun random numbers.
int * getArray() {
    static int r[4] = {1,2,3,4};
    return r;
}




// main function to call above defined function.
int main () {
    if (2){
        cout << "true";
    }
    return 0;
}