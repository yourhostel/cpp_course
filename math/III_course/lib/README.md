# StatKit

StatKit це header only бібліотека для роботи зі статистичними розподілами, 
яка побудована як строго типізована надбудова над Boost.Math. 
Вона використовує його як обчислювальне ядро, додаючи контроль інваріантів, 
перевірку параметрів і уніфікований інтерфейс доступу до розподілів.

---

[![Boost](https://img.shields.io/badge/Boost-Математичний_toolkit-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/libs/math/)

[![Boost](https://img.shields.io/badge/Boost-Розподіли_та_функції-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/dist.html)

[![Boost](https://img.shields.io/badge/Boost-Нормальний_розподіл-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/math_toolkit/dist_ref/dists/normal_dist.html)

[![Boost](https://img.shields.io/badge/Boost-Біноміальний_розподіл-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/math_toolkit/dist_ref/dists/binomial_dist.html)

[![Boost](https://img.shields.io/badge/Boost-Розподіл_Пуассона-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/math_toolkit/dist_ref/dists/poisson_dist.html)

[![Boost](https://img.shields.io/badge/Boost-Розподіл_Бернулі-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/math_toolkit/dist_ref/dists/bernoulli_dist.html)

[![Boost](https://img.shields.io/badge/Boost-Інтерфейс_розподілів-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/math_toolkit/dist_ref.html)

[![Boost](https://img.shields.io/badge/Boost-Константи_Boost.Math-orange?style=for-the-badge&labelColor=ff6600&color=lightgrey)](https://www.boost.org/doc/libs/latest/libs/math/doc/html/math_toolkit/constants.html)

---

## Основні функції розподілів

Базові аналітичні функції стандартного нормального розподілу та похідні від нього величини. 
Вони використовуються для статистичних критеріїв, апроксимацій і переходів до табличних значень.

| назва                       | сигнатура                                                | опис                                              |
|-----------------------------|----------------------------------------------------------|---------------------------------------------------|
| `phi`                       | `template <Real> Real phi(Real x)`                       | Щільність стандартного нормального розподілу      |
| `normal_cdf`                | `template <Real> Real normal_cdf(Real x)`                | Функція розподілу стандартного нормального закону |
| `laplace_phi`               | `template <Real> Real laplace_phi(Real x)`               | Таблична функція Лапласа F(x) - 0.5               |
| `inverse_laplace_phi`       | `template <Real> Real inverse_laplace_phi(Real y)`       | Обернена функція Лапласа                          |
| `z_critical`                | `template <Real> Real z_critical(Real alpha)`            | Квантиль стандартного нормального розподілу       |
| `normal_two_tailed_p_value` | `template <Real> Real normal_two_tailed_p_value(Real z)` | Двостороннє p value                               |

---

## Біноміальний розподіл і наближення

Формули для біноміального закону і асимптотичні наближення через теореми Лапласа. 
Ці функції дозволяють працювати як з малими вибірками, так і з великими $n$ через нормальне наближення.

| назва                 | сигнатура                                                                 | опис                                        |
|-----------------------|---------------------------------------------------------------------------|---------------------------------------------|
| `bernoulli_exact`     | `template <Real> Real bernoulli_exact(int n, int m, Real p)`              | Точна формула Бернуллі                      |
| `binomial_cdf`        | `template <Real> Real binomial_cdf(int n, int m, Real p)`                 | Кумулятивна функція біноміального розподілу |
| `laplace_local`       | `template <Real> Real laplace_local(int n, int m, Real p)`                | Локальна теорема Лапласа                    |
| `laplace_integral`    | `template <Real> Real laplace_integral(int n, int m1, int m2, Real p)`    | Інтегральна теорема Лапласа                 |
| `laplace_integral_cc` | `template <Real> Real laplace_integral_cc(int n, int m1, int m2, Real p)` | Теорема Лапласа з поправкою                 |

---

## Розподіл Пуассона

Функції реалізують точну масову функцію і кумулятивний розподіл для рідкісних подій. 
Використовуються як окремо, так і як граничний випадок біноміального розподілу.

| назва         | сигнатура                                              | опис                         |
|---------------|--------------------------------------------------------|------------------------------|
| `poisson_pmf` | `template <Real> Real poisson_pmf(int m, Real lambda)` | Ймовірність рівно m подій    |
| `poisson_cdf` | `template <Real> Real poisson_cdf(int m, Real lambda)` | Кумулятивна функція Пуассона |

---

## Моменти розподілів

Функції для обчислення математичного сподівання і дисперсії базових розподілів.
Забезпечує доступ до аналітичних характеристик без потреби створення об’єкта розподілу.

| назва               | сигнатура                                               | опис                                            |
|---------------------|---------------------------------------------------------|-------------------------------------------------|
| `binomial_mean`     | `template <Real> Real binomial_mean(int n, Real p)`     | Математичне сподівання біноміального            |
| `binomial_variance` | `template <Real> Real binomial_variance(int n, Real p)` | Дисперсія біноміального                         |
| `poisson_mean`      | `template <Real> Real poisson_mean(Real lambda)`        | Математичне сподівання Пуассона                 |
| `poisson_variance`  | `template <Real> Real poisson_variance(Real lambda)`    | Дисперсія Пуассона                              |
| `normal_mean`       | `template <Real> Real normal_mean()`                    | Математичне сподівання стандартного нормального |
| `normal_variance`   | `template <Real> Real normal_variance()`                | Дисперсія стандартного нормального              |

---

## Універсальна обгортка

Надає єдиний інтерфейс для роботи з різними розподілами через уніфіковані операції:
- `pdf` **probability density function** функція щільності ймовірності
- `cdf` **cumulative distribution function** кумулятивна функція розподілу
- `quantile` **quantile function** квантильна функція обернена до cdf
- `mean` **expected value** математичне сподівання
- `variance` **variance** дисперсія
Абстрагує конкретну реалізацію `Boost` і дозволяє працювати з розподілами однаково

| назва                  | сигнатура                                          | опис                              |
|------------------------|----------------------------------------------------|-----------------------------------|
| `distribution_wrapper` | `template <typename D> class distribution_wrapper` | Узагальнений інтерфейс розподілів |
| `pdf`                  | `template <Real> Real pdf(Real x)`                 | Щільність або маса                |
| `cdf`                  | `template <Real> Real cdf(Real x)`                 | Кумулятивна функція               |
| `quantile`             | `template <Real> Real quantile(Real p)`            | Квантиль                          |
| `mean`                 | `template <Real> Real mean()`                      | Математичне сподівання            |
| `variance`             | `template <Real> Real variance()`                  | Дисперсія                         |

---

## Фабричні функції

Ці функції створюють типізовані обгортки розподілів з перевіркою параметрів. 
Забезпечують зручний і безпечний спосіб ініціалізації розподілів без прямої залежності від `Boost API`.

| назва                  | сигнатура                                                 | опис                            |
|------------------------|-----------------------------------------------------------|---------------------------------|
| `make_standard_normal` | `template <Real> auto make_standard_normal()`             | Стандартний нормальний розподіл |
| `make_normal`          | `template <Real> auto make_normal(Real mean, Real sigma)` | Нормальний розподіл             |
| `make_binomial`        | `template <Real> auto make_binomial(int n, Real p)`       | Біноміальний розподіл           |
| `make_poisson`         | `template <Real> auto make_poisson(Real lambda)`          | Розподіл Пуассона               |

---

## Внутрішні перевірки

Допоміжний рівень, який гарантує дотримання математичних інваріантів і коректність вхідних даних. 
Вони централізують валідацію параметрів і забезпечують передбачувану поведінку всієї бібліотеки.

| назва                          | сигнатура                                                                       | опис                            |
|--------------------------------|---------------------------------------------------------------------------------|---------------------------------|
| `require_finite`               | `template <Real> void require_finite(Real value, string_view name)`             | Перевірка на скінченність       |
| `require_positive`             | `template <Real> void require_positive(Real value, string_view name)`           | `value > 0`                     |
| `require_non_negative`         | `template <Real> void require_non_negative(Real value, string_view name)`       | `value >= 0`                    |
| `require_probability_closed`   | `template <Real> void require_probability_closed(Real value, string_view name)` | `[0, 1]`                        |
| `require_probability_open`     | `template <Real> void require_probability_open(Real value, string_view name)`   | `(0, 1)`                        |
| `require_non_negative_int`     | `void require_non_negative_int(int n, string_view name)`                        | `n >= 0`                        |
| `require_ordered_int_interval` | `void require_ordered_int_interval(int lo, int hi, ...)`                        | `lo <= hi`                      |
| `require_binomial_k`           | `void require_binomial_k(int m, int n, string_view name)`                       | `0 <= m <= n`                   |
| `inv_sqrt_2pi`                 | `template <Real> Real inv_sqrt_2pi()`                                           | Константа нормального розподілу |

## Дискретні розподіли і табличні закони

Компоненти для роботи з дискретними випадковими величинами.
Дозволяють як явно задавати закон розподілу через таблицю, так і створювати стандартні дискретні розподіли 
через Boost з єдиним інтерфейсом.

| назва                     | сигнатура                                                                | опис                             |
|---------------------------|--------------------------------------------------------------------------|----------------------------------|
| `table_distribution`      | `template <Real> class table_distribution`                               | Табличний дискретний розподіл    |
| `make_table_distribution` | `template <Real> table_distribution<Real>(vector, vector)`               | Створення розподілу за таблицею  |
| `make_bernoulli`          | `template <Real> auto make_bernoulli(Real p)`                            | Розподіл Бернуллі                |
| `make_geometric`          | `template <Real> auto make_geometric(Real p)`                            | Геометричний розподіл            |
| `make_hypergeometric`     | `template <Real> auto make_hypergeometric(unsigned, unsigned, unsigned)` | Гіпергеометричний розподіл       |
| `make_negative_binomial`  | `template <Real> auto make_negative_binomial(unsigned, Real p)`          | Негативний біноміальний розподіл |

