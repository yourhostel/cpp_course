// insert_sort.cpp

#include <iostream>
#include "print.h"
using namespace std;

// Функція сортування вставками
void insertSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        const int current = arr[i];  // Поточний елемент для вставки
        int j = i - 1;

        // Зсуваємо елементи, що більші за current, вправо
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Вставляємо current на своє місце
        arr[j + 1] = current;
    }
}

int main() {
    int arr[] = {0, 11, 3, 40, 2, 7, 90, 7, 89, 1024, 16, 9, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Початковий масив: ";
    printArray(arr, n);

    insertSort(arr, n);

    cout << "Відсортований масив: ";
    printArray(arr, n);

    return 0;
}
