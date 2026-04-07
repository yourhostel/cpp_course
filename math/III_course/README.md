# Math III_course

[Home](https://github.com/yourhostel/cpp_course) - [Math](https://github.com/yourhostel/cpp_course/tree/main/math) - Math III_course

Теорія ймовірностей та математична статистика з реалізаціями на C++.

---

## [Практичне заняття 2. Ймовірність подій](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-07-shots)

- Шаблонні функції та concepts
- Відносна частота подій

---

## [Практичне заняття 4. Комбінаторна ймовірність](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-08-probability-combination)

- Додавання та множення ймовірностей
- Умовна ймовірність
- Залежні та незалежні події

---

## [Формула Бернуллі](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-13-bernoulli)

Біноміальний розподіл.

---

## [Формули Лапласа та Пуассона](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-13-laplace-poisson)

- Локальна теорема Лапласа
- Інтегральна теорема Лапласа
- Розподіл Пуассона

---

## [Практичне заняття 7. Числові характеристики](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-15-expected-variance)

- Математичне сподівання
- Дисперсія
- Середнє квадратичне відхилення

---

## [Дискретні випадкові величини](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-18-random-variables)

Задача на закон розподілу для послідовної перевірки ламп.

---

## [Неперервні випадкові величини](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-19-continuous-random-variable)

- Функція розподілу
- Щільність
- Математичне сподівання та дисперсія
- Побудова графіків

---

## [Нормальний розподіл](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-21-density)

---

## [Емпірична функція розподілу](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/empirical-distribution-function)

---

## [ANOVA та F критерій Фішера](https://github.com/yourhostel/cpp_course/tree/main/math/III_course/2026-03-26-anova)

Аналіз гіпотез та нормалізація даних.

```bash
pandoc \
2026-03-07-shots/README.md \
2026-03-08-probability-combination/README.md \
2026-03-13-bernoulli/README.md \
2026-03-13-laplace-poisson/README.md \
2026-03-15-expected-variance/README.md \
2026-03-18-random-variables/README.md \
2026-03-19-continuous-random-variable/README.md \
2026-03-21-density/README.md \
2026-03-21-empirical-distribution-function/README.md \
2026-03-26-anova/README.md \
2026-03-29-confidence_interval/README.md \
-s \
--pdf-engine=xelatex \
--resource-path=.:2026-03-07-shots:2026-03-08-probability-combination:2026-03-13-bernoulli:2026-03-13-laplace-poisson:2026-03-15-expected-variance:2026-03-18-random-variables:2026-03-19-continuous-random-variable:2026-03-21-density:2026-03-21-empirical-distribution-function:2026-03-26-anova \
-V mainfont="DejaVu Serif" \
-V monofont="DejaVu Sans Mono" \
-V fontsize=12pt \
-V linestretch=1.15 \
-V geometry:a4paper \
-V geometry:margin=20mm \
-V geometry:landscape \
--toc \
--toc-depth=3 \
--number-sections \
--metadata title="Теорія ймовірностей та математична статистика" \
-H ../../header.tex \
-o math_III.pdf
```



