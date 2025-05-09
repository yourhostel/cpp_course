# Практичне заняття 6. Створення програм обробки масивів символів

## 1. Функція `printCharCodesFromInput()`

Функція `printCharCodesFromInput()` призначена для зчитування рядка символів від користувача та виведення ASCII-кодів кожного символу. Вона обмежує довжину рядка 20 символами, використовує `cin.getline()` для введення та `strlen()` для визначення кількості символів у рядку.

### Чому деякі символи виводяться як від’ємні числа?

Функція працює з символами у форматі `char`, який у більшості компіляторів на Linux є знаковим (`signed char`). Це означає, що байти з кодами вище 127 (`0x7F`) будуть інтерпретовані як від’ємні числа.

Оскільки більшість сучасних систем використовують UTF-8 як стандартне кодування, кожен кириличний символ займає два байти. Наприклад:

- `'о'` → `[208, 190]` → (`0xD0 0xBE`) → (`-48 -66`)
- `'П'` → `[208, 159]` → (`0xD0 0x9F`) → (`-48 -97`)
- `'А'` → `[208, 144]` → (`0xD0 0x90`) → (`-48 -112`)


![Screenshot from 2025-03-12 23-01-33.png](screenshots/Screenshot%20from%202025-03-12%2023-01-33.png)

- Тому, якщо у рядку є 3 кириличних символи, у виводі буде 6 від’ємних чисел, оскільки кожен символ у UTF-8 займає 2 байти.

## 2. Функція `replaceDotsAndCount()`

Функція читає повний рядок, визначає **реальну кількість символів у UTF-8,  
обрізає рівно до 15 символів та замінює всі крапки (`.`) на підкреслення (`_`).

### **Як працює код?**
- `getline(cin, input);` → читає **весь рядок без обмеження байтами.
- Спочатку підраховуємо символи** та визначаємо, скільки пам’яті потрібно.
- Виділяємо рівно потрібну кількість байтів, щоб зберегти 15 символів.
- Копіюємо рядок у новий масив, замінюючи `.` на `_`.

![Screenshot from 2025-03-12 23-58-39.png](screenshots/Screenshot%20from%202025-03-12%2023-58-39.png)
![Screenshot from 2025-03-12 23-59-27.png](screenshots/Screenshot%20from%202025-03-12%2023-59-27.png)
![Screenshot from 2025-03-12 23-59-54.png](screenshots/Screenshot%20from%202025-03-12%2023-59-54.png)
![Screenshot from 2025-03-13 00-00-31.png](screenshots/Screenshot%20from%202025-03-13%2000-00-31.png)

- Тип `char` у C++ – це просто 1 байт даних (`sizeof(char) == 1`).
- Він може зберігати лише один байт, тобто значення від 0 до 255 (unsigned) або від -128 до 127 (signed).
- Якщо текст зберігається в кодуванні `ASCII`, то кожен char містить 1 символ, бо `ASCII` – це однобайтове кодування.

# **Типи `char` в C++**

| **Тип**           | **Розмір (байти)** | **Діапазон значень**                                       |
|-------------------|--------------------|------------------------------------------------------------|
| `char`            | 1 байт             | `-128` до `127` (або `0` до `255`, залежно від реалізації) |
| `signed char`     | 1 байт             | `-128` до `127`                                            |
| `unsigned char`   | 1 байт             | `0` до `255`                                               |

# **Розмір символів у UTF-8**

| Символ             | Код у UTF-8           | Кількість байтів     |
|--------------------|-----------------------|----------------------|
| Латиниця (`A`)     | `0x41`                | **1 байт**           |
| Кирилиця (`Я`)     | `0xD0 0xAF`           | **2 байти**          |
| Ієрогліф (`漢`)     | `0xE6 0xBC 0xA2`      | **3 байти**          |
| Емодзі (`😊`)      | `0xF0 0x9F 0x98 0x8A` | **4 байти**          |
