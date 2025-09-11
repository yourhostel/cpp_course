// III_course/2025-09-11-topic-3/vector_map_search.cpp

#include <iostream>
#include <random>

using namespace std;

struct Pair
{
    int key;
    double value;
};

class WVector
{
    Pair* data_;        // Вказівник на перший елемент масиву
    int size_;          // Скільки зараз зайнято
    int capacity_;      // Місткість

    public:
        WVector() : data_(nullptr), size_(0), capacity_(5)
        {
            data_ = new Pair[capacity_];           // По замовчуванню виділяємо під 5 Pair-об'єктів.
        }

        // Конструктор із визначенням місткісті
        explicit WVector(const int initial_capacity) : size_(0), capacity_(initial_capacity)
        {
            data_ = new Pair[capacity_];           // Виділяємо масив із N пар. Місткість N, зайнято 0
        }

        ~WVector() {
            delete[] data_;
        }

    // Додає елемент у кінець. Дуже дешево О(1)
    void set_back(const Pair& p)
    {
        if (size_ == capacity_)
        {
            resizeUp(); // збільшити масив
        }

        data_[size_] = p;
        ++size_;     // Збільшуємо лічильник кількості елементів
    }

    // Вставляє елемент у початок. Дорого О(n)
    void set_front(const Pair& p)
    {
        if (size_ == capacity_)
        {
            resizeUp();
        }

        // Зрушуємо всі елементи вправо
        for (int i = size_; i > 0; --i)
        {
            data_[i] = data_[i - 1];
        }

        data_[0] = p;
        ++size_;    // Збільшуємо лічильник кількості елементів
    }

    // Видаляє останній елемент (O(1))
    void pop_back()
    {
        if (size_ == 0)
        {
            cout << "Список порожній, видаляти нічого!\n";
            return;
        }

        // Зменшуємо лічильник елементів
        size_--;

        // Зменшити місткість, якщо масив надто роздутий
        if (size_ * 4 <= capacity_)
        {
            resizeDown();
        }
    }

    // Вивід усіх елементів вектора
    void print() const
    {
        cout << "{ "; // початкова фігурна дужка
        for (int i = 0; i < size_; i++)
        {
            cout << "[" << data_[i].key << " : " << data_[i].value << "]";
            if (i != size_ - 1)
            {
                cout << ", ";    // ставимо кому лише між елементами
            }
        }
        cout << " }"; // закриваємо дужку
        cout << "\n";
    }

    // Пошук за ключем (лінійний пошук, O(n))
    Pair* find_by_key(int key)
    {
        for (int i = 0; i < size_; ++i)
        {
            if (data_[i].key == key)
            {
                return &data_[i]; // повертаємо адресу елемента
            }
        }
        return nullptr; // не знайдено
    }

    int get_size() const
    {
        return size_;
    }

    // Повертає поточну місткість масиву
    int get_capacity() const
    {
        return capacity_;
    }

    private:
        // Службовий метод для збільшення місткості масиву
        void resizeUp()
        {
            const int newCap = (capacity_ == 0) ? 1 : capacity_ * 2;  // Захист від WVector vec(0) - додаємо хоча б один
            Pair* newData = new Pair[newCap];                         // Інакше подвоюємо поточну місткість
            for (int i = 0; i < size_; ++i) newData[i] = data_[i];    // Копіюємо всі існуючі елементи зі старого масиву
            delete[] data_;                                   // Звільняємо старий масив, щоб запобігти витоку пам'яті
            data_ = newData;                                  // Перенаправляємо вказівник data_ на новий масив
            capacity_ = newCap;                               // Оновлюємо значення місткості (тепер воно вдвічі більше)
        }

        // Службовий метод для зменшення місткості масиву
        void resizeDown()
        {
            const int newCap = max(size_, capacity_ / 2);         // Зменшуємо на половину від поточної
            if (newCap == capacity_) return;                          // нічого змінювати
            Pair* newData = new Pair[newCap];                         // Виділяємо менший динамічний масив
            for (int i = 0; i < size_; ++i) newData[i] = data_[i];    // Копіюємо всі існуючі елементи зі старого масиву
            delete[] data_;                                           // Далі так само як у  resizeUp
            data_ = newData;
            capacity_ = newCap;
        }
};

void test_resizeUp_resizeDown()
{
    WVector vec(2);  // стартова місткість 2

    cout << "[init] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    // Заповнюємо масив (2 елементи)
    vec.set_back({1, 1.11});
    vec.set_back({2, 2.22});
    cout << "[after 2x set_back] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    // Додаємо третій => має спрацювати resizeUp (2 -> 4)
    vec.set_back({3, 3.33});
    cout << "[after 3rd set_back | Очікуємо розширення масиву x2 resizeUp] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    // Додаємо 4-й => місткість ще 4, resizeUp не треба
    vec.set_back({4, 4.44});
    cout << "[after 4th set_back] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    // Додаємо 5-й => має спрацювати resizeUp (4 -> 8)
    vec.set_back({5, 5.55});
    cout << "[after 5th set_back | Очікуємо розширення масиву x2 resizeUp] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    // Тепер видаляємо: capacity = 8, size зменшується
    vec.pop_back(); // size=4
    cout << "[after 1st pop_back] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    vec.pop_back(); // size=3
    cout << "[after 2nd pop_back] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";

    vec.pop_back(); // size=2 → 8/2=4, newCap= max(2,4)=4, отже буде resizeDown
    cout << "[after 3rd pop_back | Очікуємо колапсу масиву /2 resizeDown] ";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n\n";
}

void test_find_by_key()
{
    WVector vec(5); // початкова місткість = 5

    // 1) Ініціалізуємо генератор випадкових чисел
    random_device rd;                                       // джерело ентропії
    mt19937 gen(rd());                                   // генератор (Mersenne Twister)
    uniform_real_distribution<double> dist(0.0, 100.0); // рівномірний розподіл [0;100)

    // 2) Додаємо 30 елементів у кінець (ключ = номер, значення = випадкове)
    for (int i = 1; i <= 30; ++i) {
        Pair p;
        p.key = i;               // ключ = порядковий номер
        p.value = dist(gen);  // випадкове число double
        vec.set_back(p);
    }

    // 3) Виводимо результат
    cout << "Вектор після вставки 30 елементів:\n";
    vec.print();
    cout << "size=" << vec.get_size()
         << " capacity=" << vec.get_capacity() << "\n";

    // 4) Нескінченний цикл пошуку
    while (true) {
        string input;
        cout << "Введіть ключ для пошуку (або 'exit' для виходу): ";
        cin >> input;

        if (input == "exit") {
            cout << "Вихід з програми...\n";
            break;
        }

        // Перетворюємо введений рядок у число
        int searchKey;
        try {
            searchKey = stoi(input);   // Пробуємо перетворити
        } catch (...) {                // Ловимо помилку якщо невдалося
            cout << "Помилка: введіть ціле число або 'exit'\n";
            continue;                  // Закінчюємо тут та йдемо на нову ітерацію
        }

        Pair* found = vec.find_by_key(searchKey);

        if (found != nullptr) {
            // cout.setf(ios::fixed);   // показувати число у фіксованій десятковій формі
            // cout.precision(4);       // точність 4 знаки після крапки
            cout << "Знайдено: [" << found->key         // Ми отримуємо напряму поля Pair found->key та  found->value
                 << " : " << found->value << "]\n";     // тому що структура по замовчуванню public на відміну від класу
        } else {
            cout << "Ключ " << searchKey << " не знайдено\n";
        }
    }
}

int main() {
    // test_resizeUp_resizeDown();
    test_find_by_key();
    return 0;
}
