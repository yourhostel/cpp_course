//
// Created by tysser on 22.03.26.
//

#pragma once
#include <string>

enum class factorial_type
{
    iterative,
    recursive,
    stl,
    gamma
};

class Chislo
{
private:
    long value_;

    /**
     * Валідація позитивного значення для поля класу.
     * @param value
     */
    static void validate_positive_value(long value);

    /**
     * Валідація не від'ємного значення для параметра
     * функцій обчислення факторіала.
     * @param n
     */
    static void validate_non_negative(long n);

    /**
    * Реалізовано декілька способів обчислення
    * факторіала.
    */
    static long factorial_iterative(long n);
    static long factorial_recursive(long n);
    static long factorial_stl(long n);
    static long factorial_gamma(long n);

public:
    /**
     * explicit забороняє неявне перетворення типів у Chislo
     *
     * @param value
     */
    explicit Chislo(long value);

    /**
     * Віртуальний деструктор потрібен, коли об'єкт
     * можуть знищувати через вказівник або посилання
     * на базовий клас. По завданню є вказівники на
     * базовий клас. Наявність хоча б одного віртуального
     * методу є сигналом, що деструктор теж має бути
     * віртуальним.
     */
    virtual ~Chislo();

    [[nodiscard]] long get_value() const;
    void set_value(long value);

    /**
     * Функція для вибору методу обчислення факторіала.
     * @param n Параметр для обчислення факторіала.
     * @param type Функція обчислення факторіала.
     * @return
     */
    [[nodiscard]] virtual long factorial(long n, factorial_type type) const;

    /**
     * Обгортка для дефолтного методу обчислення факторіала.
     * По дефолту використовується ітеративний метод.
     *
     * @param n
     * @return
     */
    [[nodiscard]] virtual long factorial(long n) const;

};
