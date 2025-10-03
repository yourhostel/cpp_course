// # III_course/2025-10-04-loops/main.cpp
#include <iostream>
#include <algorithm>
#include <ranges>
#include<vector>
#include <map>
#include <numeric>

using namespace std;

// Тестуємо різні цикли
bool IsOdd(int i);                // предикат: true для непар
void check_replace_if();          // демонструє std::replace_if: замінює елементи, що задовольняють предикат
void check_clamp();               // демонструє std::clamp: обмежує значення в діапазоні [min, max]
void check_range_based_for();     // показує range-based for: читання/модифікація елементів, structured bindings
void check_for_each();            // демонструє std::for_each: обхід діапазону + модифікація через лямбду
void check_count_if();            // підраховує кількість елементів, що відповідають предикату (std::count_if)
void check_all_any_none();        // перевіряє: всі/хоч один/жоден елемент задовольняє предикат (all_of/any_of/none_of)
void check_find();                // пошук значення або першого елемента за умовою (find/find_if/find_if_not)
void check_ranges_for_each();     // C++20 ranges::for_each: обхід без begin/end, повертає result
void check_iota();                // C++20 views::iota: генерація послідовностей (у т.ч. “нескінченних” з take)
void check_filter();              // C++20 views::filter: лінива фільтрація діапазону предикатом
void check_partial_sum();         // C++98 partial_sum: інклюзивні префіксні суми/операції по діапазону
void check_inclusive_scan();      // C++17 inclusive_scan: інклюзивний скан; підтримує execution policies (паралелізація)
void check_adjacent_difference(); // різниця (або інша операція) між сусідніми елементами; перший копіюється як є
void check_goto();                // демонструє стрибок за міткою (ручний “цикл”/вихід з вкладеності)

int main()
{
    // check_replace_if();
    // check_clamp();
    // check_range_based_for();
    // check_for_each();
    // check_count_if();
    // check_all_any_none();
    // check_find();
    // check_ranges_for_each();
    // check_iota();
    // check_filter();
    // check_partial_sum();
    // check_inclusive_scan();
    // check_adjacent_difference();
    check_goto();

    return 0;
}

bool IsOdd(int i)
{
    return ((i % 2) == 1);
}

void check_replace_if()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]); // (C++98/03/11/14)
    int t = size(arr); // новіший підхід(з С++17) для визначення розмірності масиву
    cout << "n: " << n << "; t: " << t << endl;

    // друк початкового масиву
    cout << "Original Array:";
    for (int i = 0; i < n; i++)
        cout << ' ' << arr[i];
    cout << '\n';

    // значення для заміни
    int new_val = 0;

    // заміна всіх непарних чисел на new_val
    replace_if(arr, arr + n, IsOdd, new_val);

    // друк нового масиву
    cout << "New Array:";
    for (int i = 0; i < n; i++)
        cout << ' ' << arr[i];
    cout << '\n';
}

// Не є циклом, тільки для тесту додано!
void check_clamp()
{
    int high = 100, low = 10;

    int num1 = 120;   // вище за верхню межу
    int num2 = 5;     // нижче за нижню межу
    int num3 = 50;    // всередині діапазону

    num1 = clamp(num1, low, high);
    num2 = clamp(num2, low, high);
    num3 = clamp(num3, low, high);

    cout << num1 << " " << num2 << " " << num3;
}

void check_range_based_for() {
    int arr[] = {1,2,3,4,5};

    // 1) Читання
    cout << "arr:";
    for (int x : arr) cout << ' ' << x;
    cout << '\n';

    // 2) Зміна in-place
    for (int &x : arr) if (x % 2 == 0) x *= 10;

    cout << "arr mod:";
    for (int x : arr) cout << ' ' << x;
    cout << '\n';

    // 3) map + structured bindings
    map<string,int> m{{"a",1},{"b",2}};
    for (auto &[k,v] : m) cout << k << ":" << v << " ";
    cout << '\n';
}

void check_for_each() {
    vector<int> v = {1, 2, 3, 4, 5};

    cout << "Original:";
    for_each(v.begin(), v.end(), [](int x){ cout << ' ' << x; });
    cout << '\n';

    // збільшимо кожен елемент на 10
    for_each(v.begin(), v.end(), [](int &x){ x += 10; });

    cout << "Modified:";
    for_each(v.begin(), v.end(), [](int x){ cout << ' ' << x; });
    cout << '\n';
}

void check_count_if() {
    vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // std::vector<int, std::allocator<int>> v = {1,2,3,4,5,6,7,8,9,10};

    // підрахунок парних
    int even_count = count_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });

    // підрахунок елементів > 5
    int gt5_count = count_if(v.begin(), v.end(), [](int x){ return x > 5; });

    cout << "Even numbers: " << even_count << endl;
    cout << "Greater than 5: " << gt5_count << endl;
}

void check_all_any_none() {
    vector<int> v = {2, 4, 6, 8, 10};

    // all_of: поверне true, якщо ВСІ елементи задовольняють предикат
    bool all_even  = all_of(v.begin(), v.end(),
                            [](int x){ return x % 2 == 0; });
    // тут умова "x % 2 == 0" виконується для всіх, бо всі парні → true

    // any_of: поверне true, якщо ХОЧА Б ОДИН елемент задовольняє предикат
    bool any_gt5   = any_of(v.begin(), v.end(),
                            [](int x){ return x > 5; });
    // у векторі є числа >5 (наприклад 6, 8, 10) → true

    // none_of: поверне true, якщо ЖОДЕН елемент не задовольняє предикат
    bool none_zero = none_of(v.begin(), v.end(),
                             [](int x){ return x == 0; });
    // жодного нуля в масиві немає → true

    cout << "All even:  " << all_even  << '\n';   // 1 (true)
    cout << "Any > 5:  " << any_gt5   << '\n';   // 1 (true)
    cout << "None ==0: " << none_zero << '\n';   // 1 (true)
}

void check_find() {
    vector<int> v = {1, 3, 5, 7, 9, 10};

    // find: шукає конкретне значення (10)
    auto it1 = find(v.begin(), v.end(), 10);
    if (it1 != v.end())
        cout << "find: знайдено значення " << *it1 << '\n';
    else
        cout << "find: елемент не знайдено\n";

    // find_if: шукає перший елемент, що задовольняє умову
    auto it2 = find_if(v.begin(), v.end(),
                       [](int x){ return x % 2 == 0; }); // шукаємо перший парний
    if (it2 != v.end())
        cout << "find_if: знайдено перший парний " << *it2 << '\n';
    else
        cout << "find_if: парних не знайдено\n";

    // find_if_not: протилежний варіант (з C++11)
    auto it3 = find_if_not(v.begin(), v.end(),
                           [](int x){ return x % 2 != 0; }); // шукаємо перший НЕ непарний
    if (it3 != v.end())
        cout << "find_if_not: знайдено " << *it3 << '\n';
    else
        cout << "find_if_not: елементів не знайдено\n";
}

void check_ranges_for_each() {
    vector<int> v = {1, 2, 3, 4, 5};

    // ranges::for_each працює без begin()/end(), напряму з контейнером
    ranges::for_each(v, [](int x){ cout << x << ' '; });
    cout << '\n';

    // можна відразу модифікувати елементи (через посилання)
    ranges::for_each(v, [](int &x){ x *= 10; });

    // знову виведемо, щоб побачити зміни
    ranges::for_each(v, [](int x){ cout << x << ' '; });
    cout << '\n';

    // ranges::for_each повертає структуру result з ітератором
    auto res = ranges::for_each(v, [](int x){ /* нічого */ });
    cout << "Ітератор вказує на кінець? " << (res.in == v.end()) << '\n';
}

void check_iota() {
    int n = 10;

    // 1) простий цикл від 0 до n-1
    cout << "iota(0," << n << "): ";
    for (auto i : views::iota(0, n))   // генерує [0,1,2,...,n-1]
        cout << i << ' ';
    cout << '\n';

    // 2) інший діапазон, наприклад [5..10)
    cout << "iota(5,11): ";
    for (auto i : views::iota(5, 11))  // генерує [5,6,7,8,9,10]
        cout << i << ' ';
    cout << '\n';

    // 3) нескінченний генератор
    // приклад — беремо тільки перші 5 значень
    cout << "iota infinite take(5): ";
    for (auto i : views::iota(100) | views::take(5)) // [100,101,102,103,104]
        cout << i << ' ';
    cout << '\n';
}

void check_filter() {
    // Генеруємо числа від 1 до 20
    auto rng = views::iota(1, 21);

    // Фільтруємо тільки парні
    cout << "Even numbers (1..20): ";
    for (auto v : rng | views::filter([](int x){ return x % 2 == 0; }))
        cout << v << ' ';
    cout << '\n';

    // Інший приклад: залишаємо числа кратні 3
    cout << "Multiples of 3 (1..20): ";
    for (auto v : rng | views::filter([](int x){ return x % 3 == 0; }))
        cout << v << ' ';
    cout << '\n';
}

void check_partial_sum() {
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> out(v.size());

    // обчислюємо префіксні суми
    partial_sum(v.begin(), v.end(), out.begin());

    cout << "Original: ";
    for (int x : v) cout << x << ' ';
    cout << '\n';

    cout << "Partial sums: ";
    for (int x : out) cout << x << ' ';
    cout << '\n';

    // приклад з власною операцією (добуток замість суми)
    partial_sum(v.begin(), v.end(), out.begin(), multiplies<int>());

    cout << "Partial products: ";
    for (int x : out) cout << x << ' ';
    cout << '\n';
}

void check_inclusive_scan() {
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> out(v.size());

    // 1) стандартна операція додавання
    inclusive_scan(v.begin(), v.end(), out.begin());

    cout << "Original: ";
    for (int x : v) cout << x << ' ';
    cout << '\n';

    cout << "Inclusive scan (sum): ";
    for (int x : out) cout << x << ' ';
    cout << '\n';

    // 2) з іншою операцією — наприклад, множення
    inclusive_scan(v.begin(), v.end(), out.begin(), multiplies<int>());

    cout << "Inclusive scan (product): ";
    for (int x : out) cout << x << ' ';
    cout << '\n';
}

void check_adjacent_difference() {
    vector<int> v = {5, 7, 11, 20};
    vector<int> out(v.size());

    // різниця між сусідніми елементами
    adjacent_difference(v.begin(), v.end(), out.begin());

    cout << "Original: ";
    for (int x : v) cout << x << ' ';
    cout << '\n';

    cout << "Adjacent difference: ";
    for (int x : out) cout << x << ' ';
    cout << '\n';

    // можна передати іншу операцію, напр. множення
    adjacent_difference(v.begin(), v.end(), out.begin(), multiplies<int>());

    cout << "Adjacent products: ";
    for (int x : out) cout << x << ' ';
    cout << '\n';
}

void check_goto() {
    int i = 0;

    start:  // мітка
        cout << i << ' ';
    i++;

    if (i < 5) goto start;  // стрибок назад

    cout << "\nDone!\n";
}