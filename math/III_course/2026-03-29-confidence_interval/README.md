# Тема 6. Інтервальні оцінки параметрів

## Мета
Освоєння побудови довірчих інтервалів для математичного сподівання нормального розподілу 
при відомому середньому квадратичному відхиленні, аналіз впливу обсягу вибірки та дисперсії на ширину інтервалу.

## Завдання

Для кожного варіанта, заданого вибірковим середнім $\bar{x}$, обсягом вибірки $n$ 
та відомим стандартним відхиленням $\sigma$, побудувати надійний (довірчий) 
інтервал для оцінювання математичного сподівання нормального розподілу з надійністю (рівнем довіри) $\gamma = 0.95$.

- середнє `x_bar`
- обсяг вибірки `n`
- стандартне відхилення `sigma`

```cpp
struct task
{
    std::string id;
    double x_bar;
    int n;
    double sigma;
};

std::vector<task> tasks =
{
    {"1", 75.17, 36, 6},
    {"2", 75.16, 49, 7},
    {"3", 75.15, 64, 8},
    {"4", 75.14, 81, 9},
    {"5", 75.13, 100, 10},
    {"6", 75.12, 121, 11},
    {"7", 75.11, 144, 12},
    {"8", 75.10, 169, 13},
    {"9", 75.09, 196, 14},
    {"10", 75.08, 225, 15}
};
```

## Розв'язання для Задачі №1:

$$
к
$$

З рівняння:

$$
2\Phi(t) = 0.95 \Rightarrow \Phi(t) = 0.475
$$

Де $\Phi(z)$ - функція Лапласа (табульована), що визначає ймовірність на інтервалі від $0$ до $z$.

Нам потрібен інтервал

$$
P(\bar{x} - \varepsilon < a < \bar{x} + \varepsilon) = 2\Phi(t) = 0.475 + 0.475 \approx 0.95
$$

ймовірність поза інтервалом $1 - 0.95 = 0.05$

Оскільки інтервал симетричний $0.05/2$

- зліва $0.025$
- справа $0.025$

З таблиці функції Лапласа знаходимо таке значення $t$, для якого
$$
\Phi(t) = 0.475
$$

За таблицею функції Лапласа:
$$
t \approx 1.96
$$

Еквівалентно, це означає, що $t$ є квантилем стандартного нормального розподілу рівня $0.975$:

$$
t_{0.975} \approx 1.96
$$

Похибка:

$$
\varepsilon = \frac{t\sigma}{\sqrt{n}} = \frac{1.96 \cdot 6}{\sqrt{36}} = \frac{1.96 \cdot 6}{6} = 1.96
$$

Довірчий інтервал:

$$
h_1 = \bar{x} - \varepsilon = 75.17 - 1.96 = 73.21
$$

$$
h_2 = \bar{x} + \varepsilon = 75.17 + 1.96 = 77.13
$$

# Реалізація обчислення

1. Перехід від $\gamma$ до центральної ймовірності

```cpp
double central_probability(double gamma)
{
    return (1.0 + gamma) / 2.0;
}
```

2. Квантиль стандартного нормального розподілу

```cpp
#include <boost/math/distributions/normal.hpp>

double normal_quantile(double p)
{
    boost::math::normal_distribution<> dist(0.0, 1.0);
    return boost::math::quantile(dist, p);
}
```

3. Похибка $\varepsilon$

```cpp
double margin_of_error(double t, double sigma, int n)
{
    return t * sigma / std::sqrt(n);
}
```

4. Головна функція інтервалу

```cpp
std::pair<double, double> confidence_interval(
    double x_bar,
    int n,
    double sigma,
    double gamma
)
{
    const double p = central_probability(gamma);
    const double t = normal_quantile(p);
    const double eps = margin_of_error(t, sigma, n);

    return {x_bar - eps, x_bar + eps};
}
```

5. Функція що застосовує `confidence_interval` до кожного завдання `task` і повертає вектор результатів:

```cpp
struct result
{
    std::string id;
    double h_1;
    double h_2;
};

std::vector<result> compute_intervals(
    const std::vector<task>& tasks,
    double gamma
)
{
    std::vector<result> results;
    results.reserve(tasks.size());

    std::for_each(tasks.begin(), tasks.end(), [&](const task& t)
    {
        const auto interval = confidence_interval(t.x_bar, t.n, t.sigma, gamma);

        results.push_back(result{
            t.id,
            interval.first,
            interval.second
        });
    });

    return results;
}
```

## Аналіз

```text
Task 1
x_bar =  75.17   n =  36   sigma = 6.00   gamma = 0.95
Interval   h_1 =  73.21   h_2 =  77.13

Task 2
x_bar =  75.16   n =  49   sigma = 7.00   gamma = 0.95
Interval   h_1 =  73.20   h_2 =  77.12

Task 3
x_bar =  75.15   n =  64   sigma = 8.00   gamma = 0.95
Interval   h_1 =  73.19   h_2 =  77.11

Task 4
x_bar =  75.14   n =  81   sigma = 9.00   gamma = 0.95
Interval   h_1 =  73.18   h_2 =  77.10

Task 5
x_bar =  75.13   n = 100   sigma = 10.00   gamma = 0.95
Interval   h_1 =  73.17   h_2 =  77.09

Task 6
x_bar =  75.12   n = 121   sigma = 11.00   gamma = 0.95
Interval   h_1 =  73.16   h_2 =  77.08

Task 7
x_bar =  75.11   n = 144   sigma = 12.00   gamma = 0.95
Interval   h_1 =  73.15   h_2 =  77.07

Task 8
x_bar =  75.10   n = 169   sigma = 13.00   gamma = 0.95
Interval   h_1 =  73.14   h_2 =  77.06

Task 9
x_bar =  75.09   n = 196   sigma = 14.00   gamma = 0.95
Interval   h_1 =  73.13   h_2 =  77.05

Task 10
x_bar =  75.08   n = 225   sigma = 15.00   gamma = 0.95
Interval   h_1 =  73.12   h_2 =  77.04
```

- дисперсія $\sigma^2 = D(X)$
- похибка $\varepsilon = \frac{t\sqrt{D(X)}}{\sqrt{n}} = \frac{t\sigma}{\sqrt{n}}$

Якщо зростає дисперсія, то зростає $\sigma$, а отже і похибка $\varepsilon$, тому інтервал розширюється.

Ширина інтервалу:
$$
L = 2\varepsilon = 2\frac{t\sigma}{\sqrt{n}}
$$

Отже, $L$ прямо пропорційна до $\sigma$ і обернено пропорційна до $\sqrt{n}$.

### Закономірності по завданнях

- $n = 36, 49, 64, \ldots, 225 = k^2$
- $\sqrt{n} = 6, 7, 8, \ldots, 15$
- $\sigma = 6, 7, 8, \ldots, 15$

Тому:
$$
\frac{\sigma}{\sqrt{n}} = 1
$$

$$
\varepsilon = t \cdot \frac{\sigma}{\sqrt{n}} = t = 1.96
$$

$$
L = 2\varepsilon = 3.92
$$

## Висновок

Зі зростанням $\sigma$ інтервал має розширюватися, а зі зростанням $n$ звужуватися. 
Сукупність усіх завдань не показова, бо ефекти компенсуються, оскільки $\sigma$ і $\sqrt{n}$ зростають однаково. 
Тому ширина довірчого інтервалу не змінюється.

---
