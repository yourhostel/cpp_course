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

/// Функція повертає динамічний масив.
/// Після використання необхідно вручну звільнити пам'ять за допомогою delete[].
/// Приклад:
/// int* arr = generateRandomArray(10, 1, 100);
/// ... використання масиву ...
/// delete[] arr;
int* generateRandomArray(const int n, const int minValue, const int maxValue) {
    // Ініціалізація генератора випадкових чисел
    random_device rd;
    mt19937 gen(rd()); // Генератор Mersenne Twister
    uniform_int_distribution<> distrib(minValue, maxValue); // Діапазон випадкових чисел

    // Виділяємо пам'ять для динамічного масиву
    const auto arr = new int[n];

    // Заповнюємо масив випадковими числами
    // span - це обгортка над масивом або частиною масиву,
    // яка дозволяє безпечно працювати з даними без копіювання.
    // Це частина стандарту C++20.
    for (int& num : span(arr, n)) num = distrib(gen); //

    return arr; // Повертаємо вказівник на динамічний масив
}

/// Функція для запиту параметрів і генерації масиву
/// Повертає згенерований масив і встановлює значення n через параметр
int* initializeArray(int& n, int& minValue, int& maxValue) {
    cout << "Введіть довжину масиву:\n";
    cin >> n;

    cout << "Введіть мінімальне значення:\n";
    cin >> minValue;

    cout << "Введіть максимальне значення:\n";
    cin >> maxValue;

    // Генеруємо масив
    int* randomArray = generateRandomArray(n, minValue, maxValue);

    // Виводимо масив
    cout << "Масив: ";
    for (int x : span(randomArray, n)) cout << x << " ";
    cout << endl;

    return randomArray;
}

// Приклад 1. Сума елементів масиву, розташованих між максимальним і мінімальним значеннями включно.

int sumBetweenMinMax(const int* arr, int n) {
    int imin = 0, imax = 0, sum = 0;

    // Знаходимо індекси мінімального та максимального елементів
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[imin]) imin = i;
        if (arr[i] > arr[imax]) imax = i;
    }

    // Визначаємо порядок індексів
    const int start = min(imin, imax);
    const int end = max(imin, imax);

    // Обчислюємо суму елементів між start та end включно
    for (int i = start; i <= end; ++i) {
        sum += arr[i];
    }

    return sum;
}

/// Функція для обробки масиву
void processBetweenMinMax(int(* func)(const int* arr, int n)) {
    cout << "\nprocessBetweenMinMax:\n";

    int n, minValue, maxValue;

    // Ініціалізуємо масив
    int* randomArray = initializeArray(n, minValue, maxValue);

    // Обчислюємо суму між мінімальним та максимальним
    int result = func(randomArray, n);
    cout << "Сума елементів між мінімальним і максимальним значеннями:\n" << result << endl;

    // Звільняємо пам'ять
    delete[] randomArray;
}

// Приклад 2. Знаходження індексів парного та непарного максимумів.

void findEvenOddMax(const int* arr, int n, int& ipmax, int& inpmax) {
    ipmax = -1;
    inpmax = -1;

    for (int i = 0; i < n; ++i) {
        // Пошук парного максимуму
        if (arr[i] % 2 == 0 && (ipmax == -1 || arr[i] > arr[ipmax])) {
            ipmax = i;
        }
        // Пошук непарного максимуму
        if (arr[i] % 2 == 1 && (inpmax == -1 || arr[i] > arr[inpmax])) {
            inpmax = i;
        }
    }
}

/// Функція для перестановки парного та непарного максимумів
void swapEvenOddMax(int* arr, int ipmax, int inpmax) {
    if (ipmax != -1 && inpmax != -1) {
        swap(arr[ipmax], arr[inpmax]);
    }
}

void processArrayEvenOdd() {
    cout << "\nprocessArrayEvenOdd:\n";

    int n, minValue, maxValue;

    // Ініціалізуємо масив
    int* randomArray = initializeArray(n, minValue, maxValue);
    // Знаходимо парний та непарний максимуми
    int ipmax, inpmax;
    findEvenOddMax(randomArray, n, ipmax, inpmax);

    // Виводимо знайдені максимуми
    cout << "Парний максимум = " << randomArray[ipmax] << " його індекс = " << ipmax << endl;
    cout << "Непарний максимум = " << randomArray[inpmax] << " його індекс = " << inpmax << endl;

    // Переставляємо місцями парний та непарний максимуми
    swapEvenOddMax(randomArray, ipmax, inpmax);

    // Виводимо змінений масив
    cout << "Новий масив: ";
    for (int x : span(randomArray, n)) cout << x << " ";
    cout << endl;

    // Звільняємо пам'ять
    delete[] randomArray;
}

// Приклад 3. Знайти максимальну з сум елементів: першого і останнього, другого і передостаннього і т.д.

/// Функція для знаходження максимальної суми пар елементів
void findMaxPairSum(const int* arr, int n, int& maxSum, int& maxIndex) {
    int sum = 0;
    maxSum = arr[0] + arr[n - 1]; // Ініціалізація першої суми
    maxIndex = 0;

    for (int i = 0; i < n / 2; ++i) {
        sum = arr[i] + arr[n - i - 1];
        if (sum > maxSum) {
            maxSum = sum;
            maxIndex = i;
        }
    }
}

void processMaxPairSum() {
    cout << "\nprocessMaxPairSum:\n";

    int n, minValue, maxValue;

    // Ініціалізуємо масив
    int* randomArray = initializeArray(n, minValue, maxValue);

    int maxSum, maxIndex;
    findMaxPairSum(randomArray, n, maxSum, maxIndex);

    // Виводимо результат
    cout << "\nsmax = " << maxSum << " = "
         << randomArray[maxIndex] << " + " << randomArray[n - maxIndex - 1] << endl;

    // Звільняємо пам'ять
    delete[] randomArray;
}

int main()
{
    // setlocale(LC_ALL, "uk_UA"); // for my Linux system.
    setUtf8Encoding(); // for my Windows system.

    // processBetweenMinMax(sumBetweenMinMax);
    // processArrayEvenOdd();
    processMaxPairSum();
    return 0;
}
