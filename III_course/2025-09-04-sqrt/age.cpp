// age.cpp

#include <iostream>
using namespace std;

int main() {
    int years;
    cout << "Enter your age in years: ";
    cin >> years;

    int days = years * 365;  // без урахування високосних
    cout << "Your age: " << years << " years or " << days << " days." << endl;

    return 0;
}
