#ifndef PRINT_H
#define PRINT_H

#include <iostream>
using namespace std;

// Функція, яка визначена прямо в заголовочному файлі
inline void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

#endif