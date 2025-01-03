# Завдання No 9 з Дискретної математики
## Тема:  Елементи теорії чисел та криптографії.

## Задача 1.

Знайти кількість натуральних чисел $x$, які менші від числа $n = 1176$ і мають з ним найбільший спільний дільник $d = 42$.

### Формули:
1. Числа $x$ мають задовольняти умову<sup>1</sup>: $\text{НСД}(x, n) = d$
2. Для зручності обчислень, задача зводиться до наступного:
    - Знайти $n' = \frac{n}{d}$.
    - Обчислити функцію Ейлера $\phi(n')$, яка дає кількість чисел, взаємно простих із $n'$.
3. Використовується формула для функції Ейлера:

$$
\phi(n') = n' \cdot \left( 1 - \frac{1}{p_1} \right) \cdot \left( 1 - \frac{1}{p_2} \right) \cdots
$$

   де $p_1, p_2, \ldots$ — прості числа, що входять у розклад $n'$.

---

<sup>1</sup> *НСД — найбільший спільний дільник.*

## Опис функцій

1. **`int gcd(int a, int b)`**
    - Знаходить найбільший спільний дільник (НСД) двох чисел за допомогою алгоритму Евкліда $НСД(a,b)=НСД(b,a \mod b)$.

$$
\text{НСД}(a, b) =
\begin{cases}
b, & \text{якщо } a \bmod b = 0, \\
\text{НСД}(b, a \bmod b), & \text{в іншому випадку}.
\end{cases}
$$

Використовується для перевірки умови $\text{НСД}(x, n) = d$.

2. **`vector<int> primeFactors(int n)`**
    - Розкладає число $n$ на прості множники.
    - Використовується для обчислення функції Ейлера.

3. **`int phi(int n)`**
    - Обчислює функцію Ейлера $\phi(n)$, яка рахує кількість чисел, менших за $n$ і взаємно простих із ним.
    - Використовує прості множники числа $n$.

4. **`vector<int> findNumbers(int n, int d)`**
    - Знаходить усі числа $x$, які задовольняють умову $\text{НСД}(x, n) = d$.
    - Перевіряє кожне число $x < n$ за допомогою функції `gcd`.

5. **`void solveTask()`**
    - Основна функція, яка:
        1. Розраховує $n' = \frac{n}{d}$.
        2. Обчислює функцію Ейлера $\phi(n')$.
        3. Знаходить усі числа $x$, які задовольняють умову задачі.
        4. Виводить кількість чисел та самі числа.

- **Алгоритм Евкліда для обчислення НСД**: складність $O(\log(\min(a, b)))$
- **Функція Ейлера $\phi(n')$**: складність $O(\sqrt{n'})$ для розкладання на прості множники, після чого $O(\log n')$ для обчислення функції. Загальна складність визначається домінуючим фактором і дорівнює $O(\sqrt{n'})$.


## Приклад роботи
Вхідні дані:
- $n = 1176$
- $d = 42$

## Результат:

![2024-12-20_213444.jpg](screenshots%2F2024-12-20_213444.jpg)

# Задача 2

### Умова
Розшифрувати повідомлення, закодоване класичним шифром Цезаря, використовуючи два підходи:
1. Введення ключа $k$ для розшифрування.
2. Перебір усіх можливих значень $k$ від $0$ до заданого максимального $k$, з виведенням розшифрованого тексту для кожного зсуву.

---

### Теоретична частина
**Шифр Цезаря** — це метод шифрування, в якому кожна літера замінюється іншою, що знаходиться на фіксованій кількості позицій далі в алфавіті.  
При розшифруванні використовується зсув назад за формулою:

$$
f^{-1}(p) = (p - k) \mod 26,
$$

де:
- $p$ — числове значення літери,
- $k$ — величина зсуву,
- $26$ — кількість літер в алфавіті.

Якщо $p - k$ менше $0$, використовується операція $+ 26$, щоб закільцювати літери алфавіту.

---

### Функції, використані для розв'язання

#### `decryptLetter`
Функція для розшифрування окремої літери за формулою:

$$
\text{letter} = \text{base} + ((\text{letter} - \text{base} - k + 26) \mod 26),
$$

де:
- $\text{base}$ визначається як `'A'` для великих літер або `'a'` для малих.

**Приклад використання**:
Розшифрувати літеру `D` зі зсувом $k = 3$:
- $\text{letter} = 'D'$,
- $\text{base} = 'A'$,
- Результат: $'A'$.

---

#### `decryptMessage`
Функція для розшифрування всього повідомлення. Використовує `decryptLetter` для кожної літери в повідомленні.

**Параметри**:
- `message` — зашифроване повідомлення (строка).
- $k$ — ключ шифрування (зсув).

**Результат**:
Повертає розшифроване повідомлення у вигляді строки.

**Приклад**:

![2024-12-20_233020.jpg](screenshots%2F2024-12-20_233020.jpg)

---

#### `processDecryption`
Функція, яка:
1. Запитує зашифроване повідомлення.
2. Запитує ключ $k$.
3. Розшифровує повідомлення за допомогою `decryptMessage`.
4. Виводить результат.

**Алгоритм роботи**:
1. Зчитати строку повідомлення.
2. Зчитати значення $k$.
3. Викликати функцію `decryptMessage` з отриманими даними.
4. Вивести розшифроване повідомлення.

---

#### `processDecryptionWithCycle`
Функція, яка:
1. Запитує зашифроване повідомлення.
2. Запитує початок та кінець діапазону $k$ для перебору.
3. Для кожного значення $k$ у вказаному діапазоні викликає `decryptMessage`.
4. Виводить результати для всіх можливих значень $k$ у заданому діапазоні.

**Алгоритм роботи**:
1. Зчитати строку повідомлення.
2. Зчитати початок діапазону `rangeStart`.
3. Зчитати кінець діапазону `rangeEnd`.
4. Перевірити, чи `rangeStart` не більший за `rangeEnd`.
5. Запустити цикл від $k = rangeStart$ до $rangeEnd$:
   - Викликати `decryptMessage` для кожного $k$.
   - Вивести результат у форматі `k = значення: розшифроване повідомлення`.

**Приклад**:

![2024-12-23_160449.jpg](screenshots%2F2024-12-23_160449.jpg)

