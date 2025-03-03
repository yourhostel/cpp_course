// main.cpp
#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

// Функція для генерації випадкового числа у заданому діапазоні
int randInRange(int min, int max) {
    static random_device rd;
    // Використовуємо std::mt19937 замість rand() для більш рівномірного розподілу
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Функція для перевиділення пам'яті під масив із перевіркою
int* resizeArray(int* a, int newSize) {
    if (const auto temp = static_cast<int*>(realloc(a, newSize * sizeof(int))); temp != nullptr) {
        return temp; // Якщо виділення пам’яті успішне, повертаємо новий вказівник
    } else {
        cout << "Помилка перевиділення пам'яті!" << endl;
        free(a); // Очищаємо старий масив, якщо realloc() провалився
        return nullptr; // Повертаємо nullptr, щоб функція виклику могла обробити помилку
    }
}

// Приклад 1. Видалення нульових елементів з масиву
void removeZerosFromArray() {
    int i, j, n, k = 0;

    cout << "n = ";
    cin >> n;

    auto a = new int[n]; // Динамічне оголошення масиву
    cout << "Old array:";

    for (i = 0; i < n; i++) {
        a[i] = randInRange(-2, 3); // Використання кастомної функції генерації
        cout << a[i] << " ";
        if (a[i] == 0) k++; // Підрахунок кількості нульових елементів
    }

    for (i = 0; i < n; i++) {
        if (a[i] == 0) { // Якщо зустріли нульовий елемент
            for (j = i; j < n - 1; j++) {
                a[j] = a[j + 1]; // Зсуваємо елементи вліво
            }
            i--; // Робимо крок назад для обробки випадків із кількома 0 підряд
        }
    }

    // Перевиділяємо пам'ять із перевіркою через `resizeArray()`
    a = resizeArray(a, n + k);
    if (!a) return; // Якщо realloc() провалився, функція завершується

    cout << endl << "New array:";
    for (i = 0; i < n - k; i++) cout << a[i] << " ";

    free(a); // Звільнення пам'яті
}

// Приклад 2. Додавання заданої кількості нулів у початок масиву
void prependZerosToArray() {
    int i, n, k;

    cout << "n = ";
    cin >> n;

    int* a = new int[n]; // Динамічне оголошення масиву
    cout << "Old array:";

    for (i = 0; i < n; i++) {
        a[i] = randInRange(1, 9); // Генеруємо числа від 1 до 9 (без нулів)
        cout << a[i] << " ";
    }

    cout << endl << "How many elements to add? = ";
    cin >> k; // Користувач задає кількість нулів для додавання

    // Перевиділяємо пам'ять із перевіркою через `resizeArray()`
    a = resizeArray(a, n + k);
    if (!a) return; // Якщо realloc() провалився, функція завершується

    // Зсуваємо елементи масиву вправо на k позицій
    for (i = n - 1; i >= 0; i--) {
        a[i + k] = a[i];
    }

    // Заповнюємо перші k елементів нулями
    for (i = 0; i < k; i++) {
        a[i] = 0;
    }

    // Вивід нового масиву
    cout << "New array: ";
    for (i = 0; i < n + k; i++) {
        cout << a[i] << " ";
    }

    free(a); // Звільнення пам'яті
}

// Приклад 3. Вставка нового рядка у матрицю

// Функція для перевиділення пам'яті під матрицю
int** resizeMatrix(int** a, int newRows, int cols) {
    int** temp = new int*[newRows]; // Створюємо новий масив вказівників

    // Копіюємо старі рядки у новий масив
    for (int i = 0; i < newRows - 1; i++) {
        temp[i] = a[i];
    }

    // Виділяємо пам'ять для нового рядка
    temp[newRows - 1] = new int[cols];

    delete[] a; // Видаляємо старий масив вказівників
    return temp; // Повертаємо нову матрицю
}
// Вставка нового рядка у матрицю
void insertRowToMatrix() {
    int i, j, n, m, k;

    // Визначаємо розміри матриці
    cout << "rows n = ";
    cin >> n;
    cout << "columns m = ";
    cin >> m;

    // Оголошуємо матрицю динамічно
    int** a = new int*[n];
    for (i = 0; i < n; i++) {
        a[i] = new int[m];
    }

    // Заповнюємо і виводимо початкову матрицю
    cout << "Old matrix:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = randInRange(-10, 10);
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // Додаємо один рядок у матрицю
    a = resizeMatrix(a, n + 1, m);

    // Дізнаємося індекс нового рядка
    cout << endl << "Enter the row index you want to add = ";
    cin >> k;

    if (k < 0 || k > n) {
        cout << "Помилка: індекс поза межами!" << endl;
        return;
    }

    // Зсуваємо рядки вниз
    for (i = n - 1; i >= k; i--) {
        for (j = 0; j < m; j++) {
            a[i + 1][j] = a[i][j];
        }
    }

    // Заповнюємо новий рядок нулями
    for (j = 0; j < m; j++) {
        a[k][j] = 0;
    }

    // Виводимо оновлену матрицю
    cout << "New matrix:" << endl;
    for (i = 0; i < n + 1; i++) {
        for (j = 0; j < m; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // Видаляємо матрицю
    for (i = 0; i < n + 1; i++) {
        delete[] a[i];
    }
    delete[] a;
}

// Приклад 4. Вставка нового стовпця у матрицю

// Функція для перевиділення пам'яті під додавання стовпця у кожному рядку матриці
void resizeMatrixColumns(int** a, const int rows, const int newCols) {
    for (int i = 0; i < rows; i++) {
        const auto temp = new int[newCols]; // Виділяємо новий рядок потрібного розміру

        // Копіюємо старі значення
        for (int j = 0; j < newCols - 1; j++) {
            temp[j] = a[i][j];
        }

        delete[] a[i]; // Видаляємо старий рядок
        a[i] = temp;   // Оновлюємо вказівник на новий рядок
    }
}
// Вставка нового стовпця у матрицю
void insertColumnToMatrix() {
    int i, j, n, m, k;

    // Визначаємо розміри матриці
    cout << "rows n = ";
    cin >> n;
    cout << "columns m = ";
    cin >> m;

    // Оголошуємо матрицю динамічно
    const auto a = new int*[n];
    for (i = 0; i < n; i++) {
        a[i] = new int[m];
    }

    // Заповнюємо і виводимо початкову матрицю
    cout << "Old matrix:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = randInRange(-10, 10);
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // Дізнаємося індекс нового стовпця
    cout << endl << "Enter the column index you want to add = ";
    cin >> k;

    if (k < 0 || k > m) {
        cout << "Помилка: індекс поза межами!" << endl;
        return;
    }

    // Перевиділяємо пам'ять для кожного рядка матриці, збільшуючи кількість стовпців
    resizeMatrixColumns(a, n, m + 1);

    // Зсуваємо елементи у кожному рядку вправо
    for (i = 0; i < n; i++) {
        for (j = m - 1; j >= k; j--) {
            a[i][j + 1] = a[i][j];
        }
    }

    // Заповнюємо новий стовпець нулями
    for (i = 0; i < n; i++) {
        a[i][k] = 0;
    }

    // Виводимо оновлену матрицю
    cout << "New matrix:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m + 1; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // Видаляємо матрицю
    for (i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int main() {
    // removeZerosFromArray(); // Виклик основної функції
    // prependZerosToArray(); // Виклик функції для додавання нулів у початок масиву
    // insertRowToMatrix(); // Виклик функції вставки рядка у матрицю
    insertColumnToMatrix(); // Виклик функції вставки стовпця у матрицю
    return 0;
}
