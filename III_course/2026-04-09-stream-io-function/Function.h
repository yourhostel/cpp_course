//
// Created by tysser on 09.04.26.
//

#pragma once
#include <cstddef>
#include <iosfwd>
#include <string>

template <typename T>
/**
 * Шаблон класу для роботи з дискретною функцією,
 * заданою масивами точок (x, y).
 *
 * @tparam T тип значень координат
 */
class Function {
public:
    /**
     * Символ для відображення точки на ASCII графіку
     */
    static constexpr char GRAPH_SYMBOL = '*';
    /**
     * Кількість рядків по вертикалі для ASCII графіка
     */
    static constexpr std::size_t GRAPH_HEIGHT = 25;
    static constexpr std::size_t HORIZONTAL_SCALE = 5;
    /**
     * Ширина поля для підпису значень по осі Y
     */
    static constexpr std::size_t LABEL_WIDTH = 8;
    /**
     * Горизонтальний відступ до початку області графіка
     * LABEL_WIDTH символів під значення + пробіл і вертикальна риска
     */
    static constexpr std::size_t OFFSET = LABEL_WIDTH + 2;

// ======================================================
// Конструктори та деструктор
// ======================================================
    /**
     * Створює порожній обєкт без виділеної памʼяті
     */
    Function();

    /**
     * Ініціалізує обєкт і виділяє масиви
     * @param size кількість точок
     * @param y_column номер стовпчика y (1 або 2)
     */
    Function(std::size_t size, int y_column);

    /**
     * Звільняє динамічну памʼять масивів
     */
    ~Function();

// ======================================================
// Поля класу
// ======================================================
private:
    /**
     * Масив значень x
     */
    T* x_values_;

    /**
     * Масив значень y
     */
    T* y_values_;

    /**
     * Кількість точок
     */
    std::size_t size_;

    /**
     * Обраний стовпчик y у файлі
     */
    int y_column_;

public:
// ======================================================
// Гетери стану обєкта
// ======================================================
    /**
     * Повертає кількість точок
     * @return size_
     */
    std::size_t get_size() const;

    /**
     * Повертає номер стовпчика y
     * @return y_column_
     */
    int get_y_column() const;

// ======================================================
// Керування внутрішнім сховищем
// ======================================================
    /**
     * Перевиділяє памʼять під масиви
     * @param new_size новий розмір
     */
    void resize_storage(std::size_t new_size);

    /**
     * Очищає масиви і скидає стан
     */
    void free_memory();

    /**
     * Записує точку у масиви
     * @param index позиція
     * @param x значення x
     * @param y значення y
     */
    void set_point(std::size_t index, T x, T y);

// ======================================================
// Потокове введення і виведення
// ======================================================
    /**
     * Зчитує дані з потоку у масиви
     * @param in вхідний потік
     */
    void read_from_stream(std::istream& in);

    /**
     * Виводить функцію у потік
     * @param out вихідний потік
     */
    void write_to_stream(std::ostream& out) const;

// ======================================================
// Форматне перетворення файлу
// ======================================================
    /**
     * Читає файл і записує новий у форматованому вигляді
     * @param input_path шлях до вхідного файлу
     * @param output_path шлях до вихідного файлу
     */
    static void convert_file_format(
        const std::string& input_path,
        const std::string& output_path
    );

private:
    /**
     * Форматує дані при копіюванні між потоками
     * @param in вхідний потік
     * @param out вихідний потік
     */
    static void tab_separated_fixed(
        std::istream& in,
        std::ostream& out
    );

// ======================================================
// Дружні оператори і дружня функція
// ======================================================
    /**
     * Делегує читання у read_from_stream
     * @param in потік
     * @param function обєкт
     * @return той самий потік
     */
    friend std::istream& operator>>(std::istream& in, Function<T>& function)
    {
        function.read_from_stream(in);
        return in;
    }

    /**
     * Делегує виведення у write_to_stream
     * @param out потік
     * @param function обєкт
     * @return той самий потік
     */
    friend std::ostream& operator<<(std::ostream& out, const Function<T>& function)
    {
        function.write_to_stream(out);
        return out;
    }

    /**
     * Делегує обчислення min/max
     * @param function обєкт
     * @param out потік
     */
    friend void print_min_max(const Function<T>& function, std::ostream& out)
    {
        function.print_min_max(out);
    }

// ======================================================
// Методи відображення
// ======================================================
public:
    /**
     * Будує ASCII графік функції
     * @param out потік для виводу
     */
    void draw_ascii_graph(std::ostream& out) const;

    /**
     * Обчислює і виводить мінімум і максимум
     * @param out потік
     */
    void print_min_max(std::ostream& out) const;

private:
    /**
     *
     * @param row
     * @param y_min
     * @param y_max
     * @return
     */
    //std::string build_row(T level) const;
    std::string build_row(std::size_t row, T y_min, T y_max) const;
    /**
     * Малює вісь X
     * @param out потік
     * @param width ширина
     */
    void print_axis_line(std::ostream& out, std::size_t width) const;

    /**
     * Малює шкалу по Y
     * @param out потік
     * @param y_min мінімум
     * @param y_max максимум
     */
    void print_y_scale(std::ostream& out, T y_min, T y_max) const;
};

#include "Function.tpp"

