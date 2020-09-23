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
   const char separator    = ' ';
    const int nameWidth     = 6;
    const int numWidth      = 8;

    cout << left << setw(nameWidth) << setfill(separator) << "Bob";
    cout << left << setw(nameWidth) << setfill(separator) << "Doe";
    cout << left << setw(numWidth) << setfill(separator) << 10.96;
    cout << left << setw(numWidth) << setfill(separator) << 7.61;
    cout << left << setw(numWidth) << setfill(separator) << 14.39;
    cout << left << setw(numWidth) << setfill(separator) << 2.11;
    cout << left << setw(numWidth) << setfill(separator) << 47.30;
    cout << left << setw(numWidth) << setfill(separator) << 14.21;
    cout << left << setw(numWidth) << setfill(separator) << 44.58;
    cout << left << setw(numWidth) << setfill(separator) << 5.00;
    cout << left << setw(numWidth) << setfill(separator) << 60.23;
    cout << endl;

    cin.get();
}