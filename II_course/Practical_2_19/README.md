# Функції в C++

## 1. Базові функції (C-style)

```cpp
int add(int a, int b) {
    return a + b;
}
```

### Особливості:
- Обов’язкове визначення типів параметрів і повертаємого значення.
- Передача аргументів за значенням, за посиланням (`&`) або по вказівнику (`*`).
- `void` — тип, який означає "нічого не повертає".
- Функції можуть бути оголошені і визначені окремо (headers + source files).

---

## 2. Нові можливості C++ (починаючи з C++11)

### Inline функції

```cpp
inline int square(int x) { return x * x; }
```

---

### Lambda-функції (анонімні функції)

```cpp
auto f = [](int a, int b) { return a + b; };
```

```cpp
int x = 5;
auto g = [x](int y) { return x + y; };  // захоплення значення
```

---

### std::function

```cpp
#include <functional>
std::function<int(int)> twice = [](int x) { return 2 * x; };
```

---

### Шаблонні функції (templates)

```cpp
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}
```

---

### Константні функції (`const`)

```cpp
class MyClass {
    int x;
public:
    int getX() const { return x; }
};
```

---

### Функції-члени класу

- `static`
- `virtual`
- `override`
- `final`

---

### Move-семантика

```cpp
std::string create() {
    std::string s = "hello";
    return s;
}
```

---

### constexpr функції

```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}
```

---

## 3. Що є в C++, але нема в інших

| Фіча | C++ | JS | Java | C |
|------|-----|----|------|----|
| Лямбди із захопленням | ✅ | ✅ | ✅ | ❌ |
| `constexpr` | ✅ | ❌ | ❌ | ❌ |
| `std::function` | ✅ | ✅ | частково | ❌ |
| Шаблони | ✅ | ❌ | Обмежено | ❌ |
| Move-семантика | ✅ | ❌ | ❌ | ❌ |
| Перевантаження функцій | ✅ | ✅ | ✅ | ❌ |
| `inline` | ✅ | ❌ | ❌ | ✅ |
| RAII | ✅ | ❌ | частково | ❌ |



---

## 4. Системні особливості

- Вказівники на функції
- `extern "C"`
- `va_args`
- `constexpr` + шаблони = compile-time магія
- Контроль памʼяті — вручну або через smart pointers

---

## 5. Інші сучасні штуки

- `mutable` лямбди
- `constexpr`, `noexcept`, `-> return_type` в лямбдах
- `decltype(auto)` + `auto`
- `requires Callable<T>` (C++20 Concepts)

---

## Висновок

C++ — найгнучкіша мова в контексті функцій:

- Низько- і високорівневі інструменти
- Шаблони, поліморфізм, RAII, move, constexpr
- Оптимізація на рівні компіляції
- Жорстка типізація

---