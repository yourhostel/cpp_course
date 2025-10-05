#include <bits/stdc++.h>
#include <filesystem>
using namespace std;

struct Car { string name, brand, color; };

// Читає файл, фільтрує лише власників Audi сірого кольору
vector<Car> read_audi_grey(string_view path)
{
    ifstream in{string(path)};                  // відкриття файлу
    vector<Car> v;                                // контейнер для результату
    string l;                                     // буфер для рядка
    while (getline(in, l))                  // читаємо файл построково
    {
        if (l.empty() || l[0] == '#') continue;   // пропускаємо порожні та коментовані рядки
        stringstream ss(l);                       // парсимо рядок через ;
        Car c;
        getline(ss, c.name, ';');
        getline(ss, c.brand, ';');
        getline(ss, c.color, ';');
        // фільтрація за маркою та кольором
        if ((c.brand == "Audi" || c.brand == "audi") && (c.color == "Сірий" || c.color == "сірий"))
            v.push_back(move(c));               // додаємо запис до результату
    }
    return v;                                     // повертаємо вектор власників
}

// Форматований вивід таблиці власників
template <class Range> // будь-який контейнер або діапазон, але саме тут для vector
void print_rows(const Range& a)
{
    cout << left;                                                  // вирівнювання по лівому краю
    for (const auto& i : a)
    {
        int with_name = 15 - static_cast<int>(i.name.size()) / 2;  // динамічний відступ для центрування імені
        if (with_name < 0) with_name = 0;                          // не допускаємо від’ємного значення

        // друк у три колонки з роздільниками “|”
        cout << setw(with_name + static_cast<int>(i.name.size()))
             << i.name.c_str() << " | "
             << setw(8) << i.brand.c_str() << " | "
             << i.color.c_str() << '\n';
    }
}

// Основна логіка: знайти файл, прочитати, вивести
void process_file()
{
    namespace fs = filesystem;
    const fs::path path = fs::current_path() / "car.csv";                   // шлях до файлу в поточній директорії
    const auto rows = read_audi_grey(path.string());  // читаємо та фільтруємо дані
    if (rows.empty())                                                    // якщо нічого не знайдено
    {
        cout << "Немає власників із Audi сірого кольору.\n";
        return;
    }
    print_rows(rows);
}

int main()
{
    process_file();
    return 0;
}

