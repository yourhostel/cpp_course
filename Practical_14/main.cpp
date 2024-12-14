#include <iostream>
#include <iostream>
#include <windows.h>
#include <random>
#include <span>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int* generateRandomArray(const int n, const int minValue, const int maxValue) {
    // Ініціалізація генератора випадкових чисел
    random_device rd;
    mt19937 gen(rd()); // Генератор Mersenne Twister
    uniform_int_distribution<> distrib(minValue, maxValue); // Діапазон випадкових чисел

    // Виділяємо пам'ять для динамічного масиву
    const auto arr = new int[n];

    // Заповнюємо масив випадковими числами за допомогою range-based for
    for (int& num : span(arr, n)) num = distrib(gen);

    return arr; // Повертаємо вказівник на динамічний масив
}

int main()
{
    // setlocale(LC_ALL, "uk_UA"); // for my Linux system.
    setUtf8Encoding(); // for my Windows system.

    cout << "Привіт, світ!" << std::endl;
    return 0;
}
