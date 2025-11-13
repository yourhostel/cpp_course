# Тема: Основні функції базової графіки

**Практичне заняття №12.**

## Мета роботи: 
- Детальне знайомство з можливостями графічних функцій в С++ на конкретному прикладі програми, яка буде керувати кольором і шаблонами заливки, відображати текстову інформацію, малювати за допомогою графічних примітивів елементи в середовищі програмування `Qt6`

## Завдання:
- Створити форму проекту. На формі додати шість сторінок. Кожна з цих сторінок буде відповідати окремому етапу проекту. На кожній сторінці встановити компонент `QWidget` с реалізацією класу годинника `AnalogClock` з секундною стрілкою, що рухається.

```text
mainLayout
 ├── tabWidget
 │     ├── tabAnimation
 │     ├── tabLineStyles
 │     ├── tabPenBrush
 │     ├── tabPixelPen
 │     ├── tabShapes
 │     └── tabSinusoids
 └── btnExit
```

| objectName        | type        | value / text / description   |
|-------------------|-------------|------------------------------|
| **mainLayout**    | QVBoxLayout | головний вертикальний лейаут |
| **tabWidget**     | QTabWidget  | вкладки всього застосунку    |
| **tabAnimation**  | QWidget     | вкладка «Анімація»           |
| **tabLineStyles** | QWidget     | вкладка «Стилі ліній»        |
| **tabPenBrush**   | QWidget     | вкладка «Перо/Пензель»       |
| **tabPixelPen**   | QWidget     | вкладка «Піксель/Перо»       |
| **tabShapes**     | QWidget     | вкладка «Фігури»             |
| **tabSinusoids**  | QWidget     | вкладка «Синусоїди»          |
| **btnExit**       | QPushButton | текст: `Вихід`               |


### Сторінка `Малювання пікселем та пером`

- Кнопка `Піксель` - намалювати астроїду сукупністю точок (внутрішня фігура).
- Кнопка `Перо` - намалювати астроїду ламанням, що виходить з центру (зовнішня фігура).
- Режим `Точки` - перетягування миші малює одиночні пікселі по Canvas.
- Режим `Відрізки` - послідовні клацання малюють з’єднані відрізки.
- Астроїда обчислюється параметрично (`computePixel()`).

```text
tabPixelPen
 ├── tabMainLayout
 │      ├── tabDrawingLeftLayout
 │      │        └── drawArea
 │      └── tabDrawingRightLayout
 │              ├── toolsLayout
 │              │      ├── btnPixel
 │              │      ├── btnPen
 │              │      └── groupMouseMode
 │              │             └── layoutMouseMode
 │              │                    ├── radioPoints
 │              │                    └── radioLines
 │              └── extraLayout
 │                     ├── pixelPenTimerWidget
 │                     └── btnClear
```

| objectName          | type         | description                           |
|---------------------|--------------|---------------------------------------|
| tabPixelPen         | QWidget      | вкладка “Малювання пікселем та пером” |
| drawArea            | Canvas       | полотно малювання                     |
| btnPixel            | QPushButton  | намалювати астроїду точками           |
| btnPen              | QPushButton  | намалювати астроїду лініями           |
| btnClear            | QPushButton  | очистити канвас                       |
| radioPoints         | QRadioButton | режим “точки”                         |
| radioLines          | QRadioButton | режим “відрізки”                      |
| pixelPenTimerWidget | QWidget      | контейнер для годинника               |

#### Реалізація:

![2025-11-13_12-03-27.png](screenshots/2025-11-13_12-03-27.png)

### Сторінка `Фігури`

- При натисканні кнопки Показати канвас відрисовує графічні примітиви, розташовані у сітці 2x4.
- Відображаються такі фігури:

- Перший ряд:
  1. `Arc`
  2. `Chord`
  3. `Ellipse`
  4. `Pie`

- Другий ряд:
  5. `Polygon`
  6. `Polyline`
  7. `Rectangle`
  8. `RoundRect`

```text
tabShapes
 ├── shapesMainLayout
 │      ├── drawAreaShapes
 │      └── shapesTimerLayout
 │             ├── shapesTimerWidget
 │             └── verticalSpacer
 └── btnShowShapes
```

| objectName            | type        | description                            |
|-----------------------|-------------|----------------------------------------|
| **tabShapes**         | QWidget     | вкладка “Фігури”                       |
| **shapesMainLayout**  | QHBoxLayout | головний горизонтальний лейаут вкладки |
| **drawAreaShapes**    | Canvas      | полотно для відображення примітивів    |
| **shapesTimerLayout** | QVBoxLayout | колонка праворуч під годинник          |
| **shapesTimerWidget** | QWidget     | контейнер для AnalogClock              |
| **btnShowShapes**     | QPushButton | кнопка “Показати”                      |

#### Реалізація:

![2025-11-13_12-03-34.png](screenshots/2025-11-13_12-03-34.png)
