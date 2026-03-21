# Випадкові величини і процеси

Закон розподілу неперервної випадкової величини

ТІМС-ЛПР-08+


# Завдання 8

$8.1-8.30$ Випадкова величина $X$ має функцію розподілу $F(x)$. Знайти:

а) ймовірність того, що $X$ набуде значення з інтервалу $\alpha;\beta $

б) щільність розподілу; 

в) математичне сподівання, дисперсію та середнє квадратичне відхилення. 

Побудувати графіки функції розподілу та щільності розподілу.


Варіант 8.2

$$F(x)=\begin{cases}
0, & x \le 1 \\
\dfrac{x^2 - x}{2}, & 1 < x \le 2 \\
1, & x > 2
\end{cases}$$

$\alpha = -1;\beta = 1.5$

a) Ймовірність того, що випадкова величина набуде значення з інтервалу $[\alpha, \beta]$ обчислюється через функцію розподілу:

$P(\alpha \leq X \leq \beta) = F(\beta) - F(\alpha)$

Для цього використовується функція:

```cpp
double probability(const distribution_case& c);
```

`distribution_case` тримає параметри конкретної задачі:

```cpp
struct distribution_case {
    std::string label;
    double a;
    double b;
    double alpha;
    double beta;
    std::function<double(double)> distribution_function;
    std::function<double(double)> density_function;
};
```

`a, b` інтервал, де визначена випадкова величина

`alpha, beta` інтервал, для якого рахується ймовірність

`distribution_function` функція розподілу

`density_function` щільність розподілу, тобто похідна функції розподілу $f(x)=F'(x)$

Репозиторій `DistributionRepository` тримає всі завдання 8.1 - 8.2, і має два методи для відображення графіків

Для функції розподілу

```cp
void plot_distribution_function(std::size_t variant_number) const;
```

Для щільності розподілу

```cp
void plot_density_function(std::size_t variant_number) const;
```

Інші значення вираховуються методами класу `Statistics`

# Клас Statistics

Формула чисельного інтегрування за методом Сімпсона.

```cpp
double Statistics::integrate(Function f, double a, double b);
```

Інтервал $[a,b]$ розбивається на $n$ рівних частин.
На кожній парі відрізків функція апроксимується квадратичною параболою.
Значення функції у вузлах беруться з різними вагами:
коефіцієнт 4 для непарних точок, 2 для парних, 1 для крайніх.
Має високу точність, тому що враховує кривизну функції а не площу прямокутників.

$$\int_a^b f(x)\,dx \approx \frac{h}{3}\left[f(x_0)+4\sum_{\substack{k=1 \\ k\ \mathrm{odd}}}^{n-1} f(x_k)+2\sum_{\substack{k=2 \\ k\ \mathrm{even}}}^{n-2} f(x_k)+f(x_n)\right]$$

$$h=\frac{b-a}{n}, \quad x_k=a+kh$$

## Математичне сподівання

```cpp
double Statistics::expectation(Function f, double a, double b);
```

Cереднє значення випадкової величини. Воно показує, навколо якого значення зосереджена випадкова величина при великій кількості спостережень.

$$\mathbb{E}[X]=\int_a^b x f(x)\,dx$$

## Математичне сподівання квадрата

```cpp
double Statistics::second_moment(Function f, double a, double b);
```

Допоміжна величина, яка характеризує розподіл значень з урахуванням їх квадрата. Вона використовується для обчислення дисперсії.

$$\mathbb{E}[X^2]=\int_a^b x^2 f(x)\,dx$$

## Дисперсія

```cpp
double Statistics::variance(Function f, double a, double b);
```

Міра розкиду значень випадкової величини відносно її середнього. Якщо дисперсія мала, значення зосереджені близько до математичного сподівання.

$$\mathrm{Var}(X)=\mathbb{E}[X^2]-(\mathbb{E}[X])^2$$

## Середнє квадратичне відхилення

```cpp
double Statistics::standard_deviation(Function f, double a, double b);
```

Це корінь із дисперсії. Показує типове відхилення значень від середнього.

$$\sigma=\sqrt{\mathrm{Var}(X)}$$

Результат виконання:

![Завдання 8.2](screenshots/img_0.png)

![Розподіл F(x)](screenshots/img_1.png)

![Щільність розподілу f(x)](screenshots/img_2.png)

---

# Додаток

Якщо є конкретна вибірка значень $x_1, ... , x_n$, формули описані нижче застосовуються напряму без інтегрування.
Це класичний підхід математичної статистики. Інтегрування використовується тоді, коли є лише аналітична щільність розподілу $f(x)$ або теоретична модель випадкової величини.
Тоді характеристики визначаються через інтеграли, наприклад $E[X]= \int xf(x)dx$.
Якщо ж дані емпіричні, інтегрування є зайвим і навіть гіршим за точністю підходом, оскільки додає чисельну похибку.

## Вибіркове середнє

Обчислює вибіркове середнє для емпіричної вибірки як оцінку математичного сподівання випадкової величини.
Перевантажує метод математичного сподівання з інтегруванням
Повертає значення вибіркового середнього.

```cpp
static double expectation(const Container& data);
```

$$\bar{x}=\frac{1}{n}\sum_{i=1}^{n}x_i$$

## Математичне сподівання квадрата:

Обчислює середнє значення квадратів елементів емпіричної вибірки.
Перевантажує метод другого початкового моменту неперервної випадкової величини.
Повертає значення середнього квадрата.

```cpp
static double second_moment(const Container& data);
```

$$\overline{x^2}=\frac{1}{n}\sum_{i=1}^{n}x_i^2$$

## Дисперсія:

Обчислює емпіричну дисперсію вибірки. Перевантажує дисперсію неперервної випадкової величини.

```cpp
static double variance(const Container& data);
```

$$s^2=\overline{x^2}-\bar{x}^2$$

Або еквівалентно:
Обчислює емпіричну дисперсію вибірки за стабільною формулою. Ця реалізація є більш чисельно стабільною при великих значеннях.

```cpp
static double variance_stable(const Container& data);
```

$$s^2=\frac{1}{n}\sum_{i=1}^{n}(x_i-\bar{x})^2$$

## Виправлена дисперсія (Незміщена оцінка дисперсії.): 



Обчислює виправлену дисперсію емпіричної вибірки.

```cpp
static double variance_unbiased(const Container& data);
```

$$s^2=\frac{1}{n-1}\sum_{i=1}^{n}(x_i-\bar{x})^2$$

## Середнє квадратичне відхилення:

Обчислює емпіричне середнє квадратичне відхилення.

```cpp
static double standard_deviation(const Container& data);
```

$$s=\sqrt{s^2}$$

## Виправлене середнє квадратичне відхилення:

```cpp
static double standard_deviation_unbiased(const Container& data);
```

$$s=\sqrt{\frac{1}{n-1}\sum_{i=1}^{n}(x_i-\bar{x})^2}$$

де 

$$\bar{x}=\frac{1}{n}\sum_{i=1}^{n}x_i$$

# Виправлення:

| Дата       | Причина                                            | що виправлено                                                                                                                             |
|------------|----------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| 2026-03-21 | Оновлення класу `DistributionStatistics`           | Додано методи для емперичних даних: Математичне сподівання для вибірки, Математичне сподівання квадрата, Дисперсія, Виправлена дисперсія, |
| 2026-03-21 | Задача на оновлення класу `DistributionStatistics` | Додати окремими класами `ParameterEstimation` для методу максимальної правдоподібності та `StatisticalTests` для критерію Фішера.         |


> `ParameterEstimation`
> ```cpp
> template<typename Container>
> static double mle_mean(const Container& data);
> 
> template<typename Container>
> static double mle_variance(const Container& data);
> 
> template<typename Container>
> static double mle_stddev(const Container& data);
> ```

> `StatisticalTests`
> ```cpp
> template<typename Container1, typename Container2>
> static double fisher_statistic(const Container1& data1, const Container2& data2);
> ```

 -V geometry:landscape \
```bash
pandoc README.md -s \
--pdf-engine=xelatex \
-V mainfont="DejaVu Serif" \
-V monofont="DejaVu Sans Mono" \
-V fontsize=12pt \
-V linestretch=1.15 \
-V geometry:a4paper \
-V geometry:margin=20mm \
--toc-depth=3 \
--number-sections \
--metadata title="Теорія ймовірностей та математична статистика" \
--metadata subtitle="Закон розподілу неперервної випадкової величини. ТІМС-ЛПР-08+" \
--metadata author="Тищенко Сергій, alk-43" \
--metadata date="2026-03-19" \
-H ../../../header.tex \
-o README.pdf
```