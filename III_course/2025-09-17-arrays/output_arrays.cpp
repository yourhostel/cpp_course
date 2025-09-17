#include <iostream>

using namespace std;

// Прототипи для розуміння змісту, та підняття main
void print_all(const int* a, size_t n);
void print_reverse(const int* a, size_t n);
void print_even(const int* a, size_t n);
void print_every_other(const int* a, size_t n);
void print_until_minus1(const int* a, size_t n);
void menu();

int main() {
    menu();
    return 0;
}

// 1) Усі елементи
void print_all(const int* a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        cout << a[i] << ' '; // виводимо елемент
    }
    cout << '\n';
}

// 2) У зворотному порядку
void print_reverse(const int* a, size_t n) {
    for (size_t i = n; i > 0; --i) {
        cout << a[i - 1] << ' '; // рухаємось з кінця
    }
    cout << '\n';
}

// 3) Лише парні
void print_even(const int* a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (a[i] % 2 == 0) cout << a[i] << ' '; // якщо парний — виводимо
    }
    cout << '\n';
}

// 4) Через один елемент (0,2,4,...)
void print_every_other(const int* a, size_t n) {
    for (size_t i = 0; i < n; i += 2) {
        cout << a[i] << ' '; // беремо кожен другий
    }
    cout << '\n';
}

// 5) До першого -1 (не включаючи його)
void print_until_minus1(const int* a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (a[i] == -1) break;   // зупиняємось, якщо зустріли -1
        cout << a[i] << ' ';     // виводимо поки не -1
    }
    cout << '\n';
}

// 6) Меню: do-while з вибором дії та введенням масиву
void menu() {
    const int MAXN = 10;
    int a[MAXN];
    int n = 0;
    int choice = 0;

    // читаємо один токен (слово/число); у разі EOF/помилки — "exit"
    auto read_token = []() -> string {
        string s;
        if (!(cin >> s)) return "exit";
        return s;
    };

    // парсимо ціле int з токена (без зайвих символів)
    auto parse = [](const string& s, int& out) -> bool {
        try {
            size_t pos = 0;
            int v = stoi(s, &pos, 10);
            if (pos != s.size()) return false; // є зайві символи
            out = v;
            return true;
        } catch (...) { return false; }
    };

    do {
        // показуємо опції користувачу
        cout << "\n=== Меню ===\n"
             << "1 - Вивести всі елементи\n"
             << "2 - Вивести у зворотному порядку\n"
             << "3 - Вивести парні елементи\n"
             << "4 - Вивести елементи через один\n"
             << "5 - Вивести до першого -1\n"
             << "(для виходу введи: exit)\n";

        // цикл валідації вибору 1..5 або exit
        while (true) {
            cout << "Обери номер (1-5 або exit): ";
            string tok = read_token();
            if (tok == "exit") return; // вихід у будь-який момент
            int v;
            if (parse(tok, v) && v >= 1 && v <= 5) {
                choice = v;             // зберігаємо вибір
                break;
            }
            cout << "Помилка вводу. Спробуй ще раз.\n"; // просимо повторити
        }

        // цикл валідації розміру 1..10 або exit
        while (true) {
            cout << "Введи розмір масиву (1.." << MAXN << " або exit): ";
            string tok = read_token();
            if (tok == "exit") return;
            int t;
            if (parse(tok, t) && t >= 1 && t <= MAXN) {
                n = t;                 // фіксуємо розмір
                break;
            }
            cout << "Невірний розмір. Спробуй ще раз.\n"; // просимо повторити
        }

        cout << "Введи " << n << " цілих через пробіл (або exit): ";
        // читаємо n елементів, перевіряємо кожен
        for (int i = 0; i < n; /* інкремент нижче */) {
            string tok = read_token();
            if (tok == "exit") return;            // вихід у будь-який момент
            int val;
            if (parse(tok, val)) {
                a[i] = val;                       // записуємо елемент
                ++i;                              // переходимо до наступного
            } else {
                cout << "\nНе ціле число. Повтори введення з позиції "
                     << (i + 1) << ": ";         // підказка на помилці
            }
        }

        // виконуємо обрану дію
        switch (choice) {
            case 1: print_all(a, n); break;
            case 2: print_reverse(a, n); break;
            case 3: print_even(a, n); break;
            case 4: print_every_other(a, n); break;
            case 5: print_until_minus1(a, n); break;
        }

    } while (true); // повторюємо, поки користувач не введе "exit"
}
