#include <iostream>
#include <random>
#include <algorithm> // для sort і greater

using namespace std;

// Блок А
void task_array15();

// Блок Б
constexpr int ROWS = 6;
constexpr int COLS = 7;
void print_double_array(const int arr[ROWS][COLS]);
void transform_double_array(const int arr[ROWS][COLS]);
void create_and_show_double_array();

int main() {
    cout << "Блок А" << endl;
    task_array15();
    cout << '\n';

    cout << "Блок Б" << endl;
    create_and_show_double_array();
    return 0;
}

// Блок А
void task_array15() {
    constexpr int N = 15;
    int a[N];

    random_device rd;                        // джерело ентропії
    mt19937 gen(rd());                    // генератор (Mersenne Twister)
    uniform_int_distribution dist(0, 9); // рівномірний розподіл, цілі числа

    int even_count = 0;

    cout << "Масив: ";
    for (int & i : a) {
        i = dist(gen);                    // генеруємо випадкове число int
        cout << i << ' ';
        if (i % 2 == 0) ++even_count;        // залишок від ділення на 2 = 0, збільшуємо лічильник парних
    }

    cout << "\nКількість парних: " << even_count << "\n";
}

// Блок Б

// Функція для виводу 2D масиву
void print_double_array(const int arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

// Функція для виводу 2D масиву з сортуванням рядків за спаданням
void transform_double_array(const int arr[ROWS][COLS]) {
    cout << "\nПеретворений масив (рядки за спаданням):\n";
    for (int i = 0; i < ROWS; ++i) {
        int row[COLS];
        for (int j = 0; j < COLS; ++j)
            row[j] = arr[i][j];

        // сортуємо рядок за спаданням
        sort(row, row + COLS, greater<>());

        for (const int j : row)
            cout << j << " ";
        cout << "\n";
    }
}

// Функція створення й демонстрації
void create_and_show_double_array() {
    int arr[ROWS][COLS];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dist(0, 9);

    // Заповнення
    for (auto & i : arr)
        for (int & j : i)
            j = dist(gen);

    cout << "Початковий масив:\n";

    print_double_array(arr);

    transform_double_array(arr);
}