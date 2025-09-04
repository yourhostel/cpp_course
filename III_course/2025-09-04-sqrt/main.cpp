// main.cpp

#include <iostream>
#include <cmath>
#include "root.h"

using namespace std;

int main() {
    double x(2.0);   // початкове значення

    cout << "give your value for x: ";
    cin >> x;        // введення користувачем

    cout << "std::sqrt(" << x << ") = " << sqrt(x) << '\n';
    cout << "root(" << x << ")      = " << root(x) << '\n';

    return 0;
}
