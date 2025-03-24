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
    int i, n, k = 0;

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
            for (int j = i; j < n - 1; j++) {
                a[j] = a[j + 1]; // Зсуваємо елементи вліво
            }
            i--; // Робимо крок назад для обробки випадків із кількома 0 підряд
        }
    }

    // Перевиділяємо пам'ять із перевіркою через `resizeArray()`
    a = resizeArray(a, n - k);
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
int** resizeMatrixRows(int** a, const int newRows, const int cols) {
    // Виконуємо перевиділення пам'яті для масиву покажчиків
    const auto temp = static_cast<int**>(realloc(a, newRows * sizeof(int*)));

    // Якщо realloc() провалився, очищуємо старий масив і повертаємо nullptr
    if (!temp) {
        cout << "Помилка перевиділення пам'яті!" << endl;
        free(a); // Звільняємо пам’ять від старого масиву покажчиків
        return nullptr;
    }

    // Оновлюємо основний вказівник
    a = temp;

    // Виділяємо пам’ять для нового рядка
    a[newRows - 1] = static_cast<int*>(malloc(cols * sizeof(int)));

    // Якщо виділення нового рядка не вдалося, очищаємо масив і повертаємо nullptr
    if (!a[newRows - 1]) {
        cout << "Помилка виділення пам'яті для нового рядка!" << endl;

        // Звільняємо всі рядки масиву перед виходом
        for (int i = 0; i < newRows - 1; i++) {
            free(a[i]);
        }
        free(a);

        return nullptr;
    }

    return a;
}

// Вставка нового рядка у матрицю
void insertRowToMatrix() {
    int i, j, n, m, k;

    // Визначаємо розміри матриці
    cout << "rows n = ";
    cin >> n;
    cout << "columns m = ";
    cin >> m;

    // Оголошуємо матрицю через malloc()
    auto a = static_cast<int**>(malloc(n * sizeof(int*)));
    for (i = 0; i < n; i++) {
        a[i] = static_cast<int*>(malloc(m * sizeof(int)));
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
    a = resizeMatrixRows(a, n + 1, m);

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
        free(a[i]);
    }
    free(a);
}

// Приклад 4. Вставка нового стовпця у матрицю

// Функція для перевиділення пам'яті під додавання стовпця у кожному рядку матриці
bool resizeMatrixColumns(int*** a, const int rows, const int newCols) {
    // Перевіряємо, чи `a` не є nullptr перед початком роботи
    if (!(*a)) {
        cout << "Помилка: передано nullptr замість матриці!" << endl;
        return false;
    }

    for (int i = 0; i < rows; i++) {
        // Зберігаємо поточний вказівник
        const auto temp = static_cast<int*>(realloc((*a)[i], newCols * sizeof(int)));

        // Перевіряємо, чи вдалося перевиділити пам’ять
        if (!temp) {
            cout << "Помилка перевиділення пам'яті у рядку " << i << "!" << endl;

            // Звільняємо усю пам'ять, якщо сталася помилка
            for (int j = 0; j < rows; j++) {
                if ((*a)[j]) free((*a)[j]);  // Перевіряємо, чи не nullptr
            }
            free(*a);
            *a = nullptr; // Обнуляємо покажчик, щоб уникнути висячих вказівників
            return false;
        }

        (*a)[i] = temp; // Оновлюємо покажчик на новий рядок
    }
    return true;  // Успішне перевиділення пам’яті
}
// Функція для вставки нового стовпця у матрицю
void insertColumnToMatrix() {
    int i, j, n, m, k;

    // Визначаємо розміри матриці
    cout << "rows n = ";
    cin >> n;
    cout << "columns m = ";
    cin >> m;

    // Оголошуємо матрицю через malloc()
    auto a = static_cast<int**>(malloc(n * sizeof(int*)));
    for (i = 0; i < n; i++) {
        a[i] = static_cast<int*>(malloc(m * sizeof(int)));
    }

    // Заповнюємо та виводимо початкову матрицю
    cout << "Old matrix:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = randInRange(-10, 10);
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // Визначаємо індекс нового стовпця
    cout << endl << "Enter the column index you want to add = ";
    cin >> k;

    if (k < 0 || k > m) {
        cout << "Помилка: індекс поза межами!" << endl;
        return;
    }

    // Перевиділяємо пам'ять для кожного рядка матриці, збільшуючи кількість стовпців
    if (!resizeMatrixColumns(&a, n, m + 1)) {
        cout << "Помилка: не вдалося перевиділити пам'ять для стовпців!" << endl;
        return;  // Вихід з функції, якщо пам'ять не вдалося виділити
    }

    // Якщо `a` стало nullptr після перевиділення, виходимо
    if (!a) {
        cout << "Помилка: покажчик `a` став nullptr після перевиділення пам'яті!" << endl;
        return;
    }

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
        free(a[i]);
    }
    free(a);
}

int main() {
    // removeZerosFromArray(); // Виклик основної функції
    // prependZerosToArray(); // Виклик функції для додавання нулів у початок масиву
    // insertRowToMatrix(); // Виклик функції вставки рядка у матрицю
     insertColumnToMatrix(); // Виклик функції вставки стовпця у матрицю
    return 0;
}
