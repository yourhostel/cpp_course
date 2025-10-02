// # III_course/2025-10-02-pointers-and-links/main.cpp
#include <iomanip>
#include <iostream>
#include <bits/ranges_algo.h>

using namespace std;

void print_hex(const char *str);
unsigned __int128 fibonacci(int n);
string to_string_i128(const __int128 x);

int main(int argc, char *argv[]) {
    // const auto str = "\nabcdefghij";
    // print_hex(str);

    for (int i = 0; i < 186; i++)
    {
        cout << to_string_i128(fibonacci(i)) << "\n";
    }

}

// Функція конвертує __int128 у std::string, бо напряму в cout << його не можна вивести
string to_string_i128(const __int128 x) {
    if (x == 0) return "0";  // якщо число = 0 — відразу повертаємо рядок "0"

    const bool neg = x < 0;  // прапорець: чи число від'ємне
    // v — абсолютне значення числа (якщо x < 0, беремо -x)
    __int128 v = neg ? -static_cast<__int128>(x) : static_cast<__int128>(x);

    string s;           // тут збираємо цифри (у зворотному порядку)
    while (v > 0) {
        // додаємо останню цифру числа (v % 10) у кінець рядка
        s.push_back('0' + (v % 10));
        v /= 10;             // зсуваємо число на один розряд (відкидаємо останню цифру)
    }

    if (neg) s.push_back('-');  // якщо було від'ємне число — додаємо мінус

    ranges::reverse(s);         // перевертаємо рядок, бо цифри назбиралися справа наліво
    return s;                   // повертаємо готовий рядок
}


// Функція обчислює n-те число Фібоначчі, повертає у вигляді unsigned __int128
unsigned __int128 fibonacci(const int n) {
    if(n==0) return 0;   // базовий випадок: F(0) = 0
    if(n==1) return 1;   // базовий випадок: F(1) = 1

    // Змінні: f = поточний результат, a = F(k-2), b = F(k-1)
    unsigned __int128 f=0, a=0, b=1;

    // цикл обчислює від 2 до n
    for(int k=2; k<=n; k++) {
        f = a + b;   // формула Фібоначчі: F(k) = F(k-1) + F(k-2)
        a = b;       // зсуваємо: тепер "передостаннє" стає попереднім
        b = f;       // а нове значення стає останнім
    }

    return f;  // повертаємо F(n)
}

void print_hex(const char *str)
{
    cout << '"';
    for (auto p = reinterpret_cast<const unsigned char*>(str); *p; ++p) {
        switch (const unsigned char c = *p) {
        case '\n': cout << "\\n"; break;
        case '\r': cout << "\\r"; break;
        case '\t': cout << "\\t"; break;
        case '\\': cout << "\\\\"; break;
        case '"':  cout << "\\\""; break;
        default:
            if (isprint(c)) cout << static_cast<char>(c);
            else { cout << "\\x" << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(c) << dec; }
        }
    }
    cout << "\" :hex => ";

    for (int i = 0; ; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(static_cast<unsigned char>(str[i])) << " ";
        if (str[i] == '\0') break;
    }

}