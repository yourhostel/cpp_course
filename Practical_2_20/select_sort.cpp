// select_sort.cpp

#include <iostream>
#include "print.h"
using namespace std;

// Функція сортування вибором
void selectSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Пошук найменшого елемента в правій частині
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Обмін місцями з поточним i
        if (minIndex != i) {
            const int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int main() {
    int arr[] = {4, 91, 7, 6, 2, 3, 11, 0, 34, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Початковий масив: ";
    printArray(arr, n);

    selectSort(arr, n);

    cout << "Відсортований масив: ";
    printArray(arr, n);

    return 0;
}
