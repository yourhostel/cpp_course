# Тема: Доступ до бази даних.

## Мета: Навчитися створювати додатки в C++ Qt6 з допомогою Qt Desiner
- придбати практичні навички у програмній реалізації управління станом БД PostgreSQL.

---

### Завдання:
1. Викликати редактор полів і відобразити імена полів таблиць, раніше створених у попередній роботі.
2. Створити поля для перегляду всіх пов'язаних підлеглих полів таблиць.
3. Налаштувати поля і призначити властивості полів за допомогою редактора полів (подання дати, ширини поля, зміна заголовка поля, введення початкового значення при створенні нових рядків).
4. Використовуючи можливості редактора полів, створити додаток, що реалізує подання даних у вигляді форми.
5. Організувати програмне керування даними: вставку, редагування, видалення, збереження, скасування змін.
6. Виконати програмну реалізацію сортування різних типів полів.
7. Відфільтрувати записи різних типів полів за певними критеріями.
8. З допомогою різних методів знайти записи за певними критеріями.

---

1. Робота з візуальними компонентами

- Поля та кнопки:

| Елемент                | Тип         | Текст у інтерфейсі    |
|------------------------|-------------|-----------------------|
| vcTapeIdEdit           | QLineEdit   | Код касети            |
| vcTapeTitleEdit        | QLineEdit   | Найменування          |
| vcTapeTypeEdit         | QLineEdit   | Тип касети            |
| vcTapePriceEdit        | QLineEdit   | Ціна                  |
| vcTapeDescriptionEdit  | QTextEdit   | Інформація про касету |
| vcTapeAddButton        | QPushButton | Додати                |
| vcTapeEditButton       | QPushButton | Редагувати            |
| vcTapeDeleteButton     | QPushButton | Видалити              |
| vcTapeCancelButton     | QPushButton | Скасувати             |
| vcTapeSaveButton       | QPushButton | Зберегти              |
| vcTapeFirstButton      | QToolButton | Перший запис          |
| vcTapePrevButton       | QToolButton | Попередній запис      |
| vcTapeNextButton       | QToolButton | Наступний запис       |
| vcTapeLastButton       | QToolButton | Останній запис        |
| vcRentalIdEdit         | QLineEdit   | Код операції          |
| vcRentalTapeIdEdit     | QLineEdit   | Код касети            |
| vcRentalTapeCombo      | QComboBox   | Найменування          |
| vcRentalIssueDateEdit  | QLineEdit   | Дата видачі           |
| vcRentalReturnDateEdit | QLineEdit   | Дата прийому          |
| vcRentalCustomerIdEdit | QLineEdit   | Код клієнта           |
| vcRentalCustomerCombo  | QComboBox   | ПІБ клієнта           |
| vcRentalCopiesEdit     | QLineEdit   | Кількість копій       |
| vcRentalDeadlineEdit   | QLineEdit   | Термін повернення     |
| vcRentalReturnedCheck  | QCheckBox   | Повернено             |
| vcRentalAddButton      | QPushButton | Додати                |
| vcRentalEditButton     | QPushButton | Редагувати            |
| vcRentalDeleteButton   | QPushButton | Видалити              |
| vcRentalCancelButton   | QPushButton | Скасувати             |
| vcRentalSaveButton     | QPushButton | Зберегти              |
| vcRentalFirstButton    | QToolButton | Перший запис          |
| vcRentalPrevButton     | QToolButton | Попередній запис      |
| vcRentalNextButton     | QToolButton | Наступний запис       |
| vcRentalLastButton     | QToolButton | Останній запис        |

