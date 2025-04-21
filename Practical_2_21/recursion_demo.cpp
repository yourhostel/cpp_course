// recursion_demo.cpp
#include <iostream>
using namespace std;

// Рекурсивна функція для обчислення факторіала
long factorial(long n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// Рекурсивна функція для обчислення n-го числа Фібоначчі
long fibonacci(int n) {
    if (n == 0 || n == 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;

    cout << "Введіть n для факторіала: ";
    cin >> n;
    cout << n << "! = " << factorial(n) << endl;

    cout << "Введіть n для числа Фібоначчі: ";
    cin >> n;
    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;

    return 0;
}
