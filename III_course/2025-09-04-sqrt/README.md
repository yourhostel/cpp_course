# Тема 1

---

1. Завдання було виконано в IDE [CLion](CLion)
2. Створено файл `root.cpp`, підключений заголовний системний файл `cmath`, написана проста функція обгортка `root` для std::sqrt, і скомпельован.

- > ![Знімок екрана з 2025-09-04 18-09-41.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2018-09-41.png)

3. Створено `root.h` з заголовком функції root. Таким чином, інші файли (наприклад, `main.cpp`) зможуть підключати `root.h` і викликати функцію `root`.
4. Створено `main.cpp` приєднано `root.h` та системні  `iostream` і `cmath`, увімкнено директиву `using namespace std`
- ```cpp
   // main.cpp

  #include <iostream>
  #include <cmath>
  #include "root.h"
  
  using namespace std;
  
  int main() {
  double x = 9.0;
  
      cout << "std::sqrt(" << x << ") = " << sqrt(x) << '\n';
      cout << "root(" << x << ")      = " << root(x) << '\n';
  
      return 0;
  }
  ```
- Виконана компіляція. `CMakeLists.txt` - визначає автоматичний режим (5 пункт)
  ```CMakeLists.txt
  add_executable(sqrt_2025_09_04
        main.cpp
        root.cpp
  )
  ```
- Перевірено роботу через обгортку та безпосередньо
  > ![Знімок екрана з 2025-09-04 18-28-34.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2018-28-34.png)

6.  Модифікація для введення значення користувачем
- ```cpp
  #include <iostream>
  #include <cmath>
  #include "root.h"
  
  using namespace std;
  
  int main() {
  double x(2.0);   // початкове значення

    cout << "give your value for x: ";
    cin >> x;        // введення користувачем

    cout << "std::sqrt(" << x << ") = " << sqrt(x) << '\n';
    cout << "root(" << x << ")      = " << root(x) << '\n';

    return 0;
  }
  ```
  > ![Знімок екрана з 2025-09-04 18-46-00.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2018-46-00.png)
7. Користування налагоджувачем при виконані функції `main`
- > ![Знімок екрана з 2025-09-04 18-53-42.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2018-53-42.png)
    ![Знімок екрана з 2025-09-04 19-16-16.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2019-16-16.png)
8. ```CMakeLists.txt
   cmake_minimum_required(VERSION 3.29)
   project(sqrt_2025_09_04)
   
   set(CMAKE_CXX_STANDARD 23)
   
   # 1) Програма для sqrt (main + root)
   add_executable(sqrt_2025_09_04
           main.cpp
           root.cpp
   )
   
   # 2) Друкує ім'я
   add_executable(name_2025_09_04
           name.cpp
   )
   
   # 3) Рахує вік у днях
   add_executable(age_2025_09_04
           age.cpp
   )
   ```

9. [name.cpp](https://github.com/yourhostel/cpp_course/blob/main/III_course/2025-09-04-sqrt/name.cpp)
- > ![Знімок екрана з 2025-09-04 19-10-48.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2019-10-48.png)
10. [age.cpp](https://github.com/yourhostel/cpp_course/blob/main/III_course/2025-09-04-sqrt/age.cpp)
- > ![Знімок екрана з 2025-09-04 19-11-43.png](screenshots/%D0%97%D0%BD%D1%96%D0%BC%D0%BE%D0%BA%20%D0%B5%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%B7%202025-09-04%2019-11-43.png)