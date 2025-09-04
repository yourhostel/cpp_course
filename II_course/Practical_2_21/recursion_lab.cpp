// recursion_lab.cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;

// Приклад 1: Вивід цифр числа
void cnum(int n) {
    if (n == 0) return;
    cnum(n / 10);
    cout << n % 10 << " ";
}

// Приклад 2: Піднесення до степеня
double power(double x, int st) {
    if (st <= 0) return 1;
    return x * power(x, st - 1);
}

// Приклад 3: Індекс мінімального елемента масиву
int minimum(int *mas, int n, int k) {
    if (k == n - 1) return k;
    int a = minimum(mas, n, k + 1);
    return (mas[a] < mas[k]) ? a : k;
}

// Приклад 4: Сума квадратних коренів від 1 до n
double sumkor(int a) {
    if (a == 1) return 1;
    return sqrt(a) + sumkor(a - 1);
}

// Приклад 5: Обернення масиву
void invertItem(int *a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
    if (++i < --j) invertItem(a, i, j);
}

// Приклад 6: Перевірка на паліндром
int pal(char *s) {
    if (strlen(s) <= 1) return 1;
    int len = (s[0] == s[strlen(s) - 1]);
    char *s1 = new char[strlen(s) - 1];
    strncpy(s1, s + 1, strlen(s) - 2);
    s1[strlen(s) - 2] = '\0';
    int result = len && pal(s1);
    delete[] s1;
    return result;
}

// Приклад 7: НСД (алгоритм Евкліда)
int nod(int a, int b) {
    if (b > a) return nod(b, a);
    if (b == 0) return a;
    return nod(b, a % b);
}

// Приклад 8: Швидке сортування
void QuickSort(int a[], int L, int R) {
    int i = L, j = R;
    int x = a[(L + R) / 2];
    do {
        while (a[i] < x) i++;
        while (x < a[j]) j--;
        if (i <= j) {
            int y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    } while (i <= j);
    if (L < j) QuickSort(a, L, j);
    if (i < R) QuickSort(a, i, R);
}

int main() {
    int choice;
    cout << "Практичне заняття 11 — Рекурсивні алгоритми\n";
    cout << "1. Вивід цифр числа\n";
    cout << "2. Піднесення до степеня\n";
    cout << "3. Мінімальний елемент масиву\n";
    cout << "4. Сума коренів від 1 до n\n";
    cout << "5. Обернення масиву\n";
    cout << "6. Перевірка на паліндром\n";
    cout << "7. НСД (алгоритм Евкліда)\n";
    cout << "8. Швидке сортування\n";
    cout << "0. Вихід\n";

    do {
        cout << "\nВиберіть приклад (0-8): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "Введіть число: ";
                cin >> n;
                cnum(n);
                cout << endl;
                break;
            }
            case 2: {
                double x; int st;
                cout << "Введіть число x = "; cin >> x;
                cout << "Введіть степінь st = "; cin >> st;
                cout << "Результат: " << power(x, st) << endl;
                break;
            }
            case 3: {
                int n;
                cout << "Розмір масиву: ";
                cin >> n;
                int *mas = new int[n];
                for (int i = 0; i < n; i++) {
                    mas[i] = rand() % 100;
                    cout << mas[i] << " ";
                }
                cout << endl;
                int min = minimum(mas, n, 0);
                cout << "Мінімальний елемент: mas[" << min << "] = " << mas[min] << endl;
                delete[] mas;
                break;
            }
            case 4: {
                int n;
                cout << "Введіть n: ";
                cin >> n;
                cout << "Сума коренів: " << sumkor(n) << endl;
                break;
            }
            case 5: {
                int a[10];
                cout << "Введіть 10 чисел:\n";
                for (int i = 0; i < 10; i++) cin >> a[i];
                invertItem(a, 0, 9);
                cout << "Обернений масив:\n";
                for (int i = 0; i < 10; i++) cout << a[i] << " ";
                cout << endl;
                break;
            }
            case 6: {
                cin.ignore();
                char ss[100];
                cout << "Введіть рядок: ";
                cin.getline(ss, 100);
                char *s = new char[strlen(ss) + 1];
                strcpy(s, ss);
                if (pal(s)) cout << "Це паліндром\n";
                else cout << "Ні, не паліндром\n";
                delete[] s;
                break;
            }
            case 7: {
                int a, b;
                cout << "Введіть два числа: ";
                cin >> a >> b;
                cout << "НСД = " << nod(a, b) << endl;
                break;
            }
            case 8: {
                int a[12];
                cout << "Введіть 12 чисел:\n";
                for (int i = 0; i < 12; i++) cin >> a[i];
                QuickSort(a, 0, 11);
                cout << "Відсортований масив:\n";
                for (int i = 0; i < 12; i++) cout << a[i] << " ";
                cout << endl;
                break;
            }
            case 0:
                cout << "Завершення програми.\n";
                break;
            default:
                cout << "Неправильний вибір, спробуйте ще раз.\n";
        }

    } while (choice != 0);

    return 0;
}
