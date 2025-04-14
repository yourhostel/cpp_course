// bubble_sort.cpp

#include <iostream>
using namespace std;

// Функція сортування бульбашкою
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j - 1] > arr[j]) {
                // Обмін елементів
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

// Функція друку масиву
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Головна функція
int main() {
    int arr[] = {4, 9, 7, 6, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Початковий масив: ";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "Відсортований масив: ";
    printArray(arr, n);

    return 0;
}
