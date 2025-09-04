#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Приклад 1: Зсув масиву вліво на 3 елементи
void shiftLeft(int arr[], int n, int shift) {
    shift %= n;
    for (int i = 0; i < shift; i++) {
        int temp = arr[0];
        for (int j = 0; j < n - 1; j++) {
            arr[j] = arr[j + 1];
        }
        arr[n - 1] = temp;
    }
}

void shiftRight(int arr[], int n, int shift) {
    shift %= n;
    for (int i = 0; i < shift; i++) {
        int temp = arr[n - 1];
        for (int j = n - 1; j > 0; j--) {
            arr[j] = arr[j - 1];
        }
        arr[0] = temp;
    }
}

// Приклад 2: Видалення всіх мінімальних елементів
void removeMinElements(int arr[], int &n) {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == min) {
            k++;
            for (int j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            i--;
        }
    }
    n -= k;
}

// Приклад 3: Стиснення масиву (видалення кожного другого елемента)
void compressArray(int arr[], int &n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n - 1; j++) {
            arr[j] = arr[j + 1]; // Зсув елементів вліво
        }
    }
    n = (n % 2 == 0) ? n / 2 : n / 2 + 1; // Оновлення розміру масиву
}

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(NULL));
    const int size = 10;
    int arr[size];

    cout << "Initial array:" << endl;
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }
    cout << endl;

    // Приклад 1
    shiftLeft(arr, size, 3);
    cout << "Array after left shift by 3:" << endl;
    printArray(arr, size);

    // Приклад 2
    int n = size;
    removeMinElements(arr, n);
    cout << "Array after removing min elements:" << endl;
    printArray(arr, n);

    // Приклад 3
    compressArray(arr, n);
    cout << "Array after compression:" << endl;
    printArray(arr, n);

    return 0;
}
