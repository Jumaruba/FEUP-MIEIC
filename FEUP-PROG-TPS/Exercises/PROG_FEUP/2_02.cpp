//exercise 2.2

#include <iostream>

using namespace std;

int main(){
    double a, b, c, biggest, medium, smallest;

    //let's find out which one is the biggest (letter a)
    if (cin >> a >> b >> c) {
        if (a > b && a > c) {
            biggest = a;
            if (b > c) {
                medium = b;
                smallest = c;
            }
            else{
                medium = c;
                smallest = b;
            }

        }
        if (b > c && b > a) {
            biggest = b;
            if (a > c) {
                medium = a;
                smallest = c;
            }
            else {
                medium = c;
                smallest = a;
            }
        }
        if (c > b && c > a) {
            biggest = c;
            if (a > b) {
                medium = a;
                smallest = b;
            }
            else{
                medium = b;
                smallest = a;
            }
        }
    }
    cout << biggest << " " << medium << " " << smallest << endl;   //letter b

    if (biggest <= medium + smallest)  //letter c
        cout << "it can be a triangle";
    else
        cout << "it cannot be a triangle";

    return 0;
}
