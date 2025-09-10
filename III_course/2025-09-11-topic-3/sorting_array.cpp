// III_course/2025-09-11-topic-3/sorting_array.cpp

#include <iostream>

using namespace std;

// Використовується класичний алгоритм "сортування бульбашкою".
// Алгоритм полягає в багаторазовому проході по масиву та послідовному обміні
// сусідніх елементів, якщо вони розташовані у невірному порядку.

// Функція для виводу масиву на екран
void printArray(const int* arr, const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}


// Функція сортування бульбашкою за зростанням
void sortAscending(int* arr, const int size)
{
    // Зовнішній цикл відповідає за кількість проходів по масиву
    for (int i = 0; i < size - 1; i++)
    {
        // Внутрішній цикл порівнює сусідні елементи та міняє їх місцями
        for (int j = 0; j < size - i - 1; j++)
        {
            // Якщо поточний елемент більший за наступний – міняємо їх місцями
            if (arr[j] > arr[j + 1])
            {
                const int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функція сортування бульбашкою за спаданням
void sortDescending(int* arr, const int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            // Якщо поточний елемент менший за наступний – міняємо їх місцями
            if (arr[j] < arr[j + 1])
            {
                const int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Введіть кількість елементів масиву: ";
    cin >> n;

    // Динамічно виділяємо пам’ять під масив розміру n
    const auto arr = new int[n];

    // Введення елементів масиву користувачем
    cout << "Введіть " << n << " елементів масиву: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "\nМасив до сортування: ";
    printArray(arr, n);

    // Виконуємо сортування за зростанням
    sortAscending(arr, n);
    cout << "Масив після сортування за зростанням: ";
    printArray(arr, n);

    // Виконуємо сортування за спаданням
    sortDescending(arr, n);
    cout << "Масив після сортування за спаданням: ";
    printArray(arr, n);

    // Звільняємо пам’ять
    delete[] arr;

    return 0;
}
