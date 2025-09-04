#include <iostream>
// #include <windows.h>
#include <random>
#include <vector>

using namespace std;
// void setUtf8Encoding()
// {
//     SetConsoleCP(65001);
//     SetConsoleOutputCP(65001);
// }

// Приклад 1.

// Функція для обчислення суми від'ємних елементів масиву
void sumNegativeElements()
{
    constexpr int n = 10; // Розмір масиву
    int a[n];
    int suma = 0; // Змінна для зберігання суми

    cout << "Введіть масив А (10 елементів):\n";
    for (int & i : a) // Використання range-based for для введення
    {
        cin >> i; // Введення елементів масиву
        if (i < 0) // Перевірка на від'ємність
        {
            suma += i; // Додавання до суми
        }
    }

    cout << "Сума від'ємних елементів = " << suma << endl;
}

// Приклад 2.

// Функція для обчислення зваженого добутку елементів масиву
void calculateWeightedProduct()
{
    constexpr int n = 8; // Розмір масиву
    random_device rd; // Ініціалізація генератора випадкових чисел
    mt19937 gen(rd()); // Генератор на базі Mersenne Twister
    uniform_int_distribution<> distrib(1, 10); // Діапазон чисел [1; 10]

    vector<int> a(n); // Використання std::vector для зберігання масиву
    long long product = 1; // Початкове значення добутку

    cout << "Масив A: ";
    for (int i = 0; i < n; ++i)
    {
        a[i] = distrib(gen); // Генерація випадкового числа
        cout << a[i] << " ";
        product *= (i + 1) * a[i]; // Обчислення зваженого добутку
    }

    cout << "\nЗважений добуток елементів масиву = " << product << endl;
}

// Приклад 3.

// Функція для симетричної перестановки елементів масиву
void symmetricSwapWork(const int n)
{
    random_device rd; // Ініціалізація генератора випадкових чисел
    mt19937 gen(rd()); // Генератор на базі Mersenne Twister
    uniform_int_distribution<> distrib(-10, 10); // Діапазон чисел [-10, 10]


    vector<int> a(n); // Масив

    cout << "Старий масив: ";
    for (int i = 0; i < n; ++i)
    {
        a[i] = distrib(gen); // Генерація випадкового числа
        cout << a[i] << " ";
    }

    // Симетрична перестановка елементів
    for (int i = 0; i < n / 2; ++i)
    {
        swap(a[i], a[n - i - 1]); // Міняємо місцями елементи
    }

    cout << "\nНовий масив: ";
    for (const auto &element : a) // Використання range-based for для виведення
    {
        cout << element << " ";
    }
    cout << endl;
}

void symmetricSwap()
{
    cout << "Для розміру 10:\n";
    symmetricSwapWork(10);

    cout << "\nДля розміру 9:\n";
    symmetricSwapWork(9);
}

// Приклад 4

//Знаходження найдовшої послідовності однакових елементів масиву

// Функція для генерації випадкового масиву
vector<int> generateRandomArray(int n, int minValue, int maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minValue, maxValue);

    vector<int> arr(n);
    for (int& num : arr) {
        num = distrib(gen); // Генерація випадкових чисел
    }
    return arr;
}

// Функція реалізує всю логіку аналізу масиву та виводу результату.
void processLongestSequence() {
    int n;
    cout << "Введіть розмір масиву:\n";
    cin >> n;

    // Генерація масиву
    vector<int> arr = generateRandomArray(n, 1, 3);

    int maxLength = 1; // Максимальна довжина
    int currentLength = 1; // Поточна довжина

    cout << "Масив: ";
    for (const int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Аналіз масиву
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] == arr[i - 1]) {
            ++currentLength; // Продовжуємо послідовність
        } else {
            maxLength = max(maxLength, currentLength); // Оновлюємо максимальну довжину
            currentLength = 1; // Починаємо нову послідовність
        }
    }
    maxLength = max(maxLength, currentLength); // Перевірка після завершення циклу

    cout << "Найдовша послідовність однакових елементів:\n" << maxLength << endl;
}


int main()
{
     setlocale(LC_ALL, "uk_UA"); // for my Linux system.
    // setUtf8Encoding(); // for my Windows system.

    // sumNegativeElements();
    // calculateWeightedProduct();
    // symmetricSwap();
    // processLongestSequence();

    constexpr int arr[4] = {1, 2, 3, 4};
    cout << arr + 2;
    return 0;
}
