# Print

[print.hpp](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/lib/print.hpp)
[print.tpp](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/lib/print.tpp)

`Print` це допоміжна `header only` бібліотека для виведення результатів у консоль та побудови простих діаграм.

## Призначення

Бібліотека використовується у навчальних задачах зі статистики для двох типів виведення результатів.

1. Друк табличних результатів у консоль.
2. Побудова гістограм через Qt Charts.

## Простори імен

```cpp
namespace print::tables
```

Містить функції для форматованого виведення таблиць у консоль.

```cpp
namespace print::charts
```

Містить функції для побудови графіків і діаграм.


## create_histogram_chart_view

**Побудова гістограми**

Функція `create_histogram_chart_view` створює готовий об’єкт `QChartView` з гістограмою.

Гістограма будується як категоріальна стовпчикова діаграма.
Кожен елемент вхідного набору даних перетворюється на один стовпчик.

Функція підходить для візуалізації:

1. абсолютних частот;
2. відносних частот;
3. щільностей частот;
4. інших числових значень, які потрібно подати у вигляді стовпчиків.

## Структура одного стовпчика

```cpp
namespace print::charts
{
    struct histogram_bar
    {
        std::string category;
        double value;
    };
}
```

Поле `category` містить підпис стовпчика.

Поле `value` містить числове значення стовпчика.

Приклад:

```cpp
const std::vector<print::charts::histogram_bar> data
{
    {"2-6",   0.10},
    {"6-10",  0.16},
    {"10-14", 0.32},
    {"14-18", 0.24},
    {"18-22", 0.12},
    {"22-26", 0.06}
};
```

## Структура налаштувань гістограми

```cpp
namespace print::charts
{
    struct histogram_options
    {
        std::string set_name;
        std::string chart_title;
        std::string y_axis_title;
        std::string x_axis_title;

        double y_min = 0.0;
        double y_max = 1.0;

        int width = 800;
        int height = 600;
    };
}
```

Поле `set_name` задає назву набору стовпчиків.

Поле `chart_title` задає заголовок діаграми.

Поле `y_axis_title` задає підпис осі Y.

Поле `x_axis_title` задає підпис осі X.

Поля `y_min` і `y_max` задають межі шкали по осі Y.

Поля `width` і `height` задають розмір вікна з діаграмою.

## Сигнатура функції

```cpp
namespace print::charts
{
    inline std::unique_ptr<QChartView> create_histogram_chart_view(
        const std::vector<histogram_bar>& data,
        const histogram_options& options
    );
}
```

Функція приймає:

1. `data` - вектор стовпчиків гістограми;
2. `options` - параметри оформлення діаграми.

Функція повертає `std::unique_ptr<QChartView>`.

Це означає, що кореневий віджет керується через RAII, тому користувачу не потрібно вручну викликати `delete`.

## Залежності стандартної бібліотеки C++

| Заголовок     | Призначення                                |
|---------------|--------------------------------------------|
| `<string>`    | Зберігання назв категорій, графіка та осей |
| `<vector>`    | Зберігання набору стовпчиків               |
| `<memory>`    | Використання `std::unique_ptr`             |
| `<algorithm>` | Використання стандартних алгоритмів        |
| `<ranges>`    | Використання `std::ranges::for_each`       |

## Використані компоненти Qt

| Назва              | Опис                               | Особливості                                            |
|--------------------|------------------------------------|--------------------------------------------------------|
| `QChartView`       | Віджет для відображення графіка    | Саме цей об’єкт показується через `show()`             |
| `QChart`           | Об’єкт діаграми                    | Містить серії, осі та заголовок                        |
| `QBarSeries`       | Серія стовпчиків                   | Об’єднує набір значень для діаграми                    |
| `QBarSet`          | Набір значень                      | Містить висоти стовпчиків                              |
| `QBarCategoryAxis` | Категоріальна вісь X               | Використовується для підписів інтервалів               |
| `QValueAxis`       | Числова вісь Y                     | Використовується для шкали значень                     |
| `QApplication`     | Об’єкт застосунку Qt               | Потрібен у `main.cpp`, але не у самій функції          |
| `QPainter`         | Інструмент налаштування рендерингу | Використовується для згладжування через `Antialiasing` |

## Include

Для реалізації функції потрібні такі заголовки:

```cpp
#include <algorithm>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPainter>
```

У `main.cpp` додатково потрібен:

```cpp
#include <QApplication>
```

## Приклад використання

```cpp
#include <QApplication>
#include "print.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    const std::vector<print::charts::histogram_bar> data
    {
        {"2-6",   0.10},
        {"6-10",  0.16},
        {"10-14", 0.32},
        {"14-18", 0.24},
        {"18-22", 0.12},
        {"22-26", 0.06}
    };

    const print::charts::histogram_options options
    {
        .set_name = "Відносна частота",
        .chart_title = "Гістограма відносних частот",
        .y_axis_title = "Частка",
        .x_axis_title = "Інтервали",
        .y_min = 0.0,
        .y_max = 0.4,
        .width = 800,
        .height = 600
    };

    auto chart_view = print::charts::create_histogram_chart_view(data, options);

    chart_view->show();

    return app.exec();
}
```

## Приклад внутрішнього обходу даних

```cpp
QStringList categories;

std::ranges::for_each(data,
    [&](const auto& item)
    {
        categories << QString::fromStdString(item.category);
        *set << item.value;
    }
);
```

Тут `data` є діапазоном, по якому виконується ітерація.

Параметр `item` є посиланням на поточний елемент вектора.

Значення `item.category` додається до списку категорій осі X.

Значення `item.value` додається до набору стовпчиків `QBarSet`.

## CMake

Для використання Qt Charts потрібно підключити компоненти `Widgets` і `Charts`.

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

target_link_libraries(your_target_name
    PRIVATE
        Qt6::Widgets
        Qt6::Charts
)
```

Якщо `Print` підключається як `INTERFACE` бібліотека, залежності можна передати через неї.

```cmake
target_link_libraries(print
    INTERFACE
        Qt6::Widgets
        Qt6::Charts
)
```

## Керування пам’яттю

Функція повертає `std::unique_ptr<QChartView>`, тому кореневий віджет знищується автоматично.

Внутрішні об’єкти Qt Charts створюються через `new`, тому що Qt використовує власну модель володіння об’єктами.

Після додавання серій та осей у `QChart` ці об’єкти переходять під керування Qt.

Користувач функції не повинен вручну знищувати `QChart`, `QBarSeries`, `QBarSet` або осі.

## Обмеження

Функція будує категоріальну стовпчикову діаграму.

Для навчальної задачі з рівними інтервалами така діаграма коректно відображає гістограму частот або відносних частот.

Якщо інтервали мають різну ширину, для строгої статистичної гістограми потрібно будувати щільності частот, а не просто частоти.
