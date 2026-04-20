//
// Created by tysser on 20.04.26.
//

#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <functional>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/math/constants/constants.hpp>
#include <boost/math/distributions/bernoulli.hpp>
#include <boost/math/distributions/binomial.hpp>
#include <boost/math/distributions/geometric.hpp>
#include <boost/math/distributions/hypergeometric.hpp>
#include <boost/math/distributions/negative_binomial.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/poisson.hpp>

namespace stats
{
    template <typename T>
    concept floating_point_like = std::floating_point<T>;

    namespace detail
    {
        /**
         * Перевірка, що значення є скінченним.
         * @param value число для перевірки
         * @param name назва параметра для тексту винятку
         * @throws std::domain_error якщо значення не є скінченним
         */
        template <floating_point_like Real>
        inline void require_finite(const Real value, const std::string_view name);

        /**
         * Перевірка, що значення строго додатне.
         * @param value число для перевірки
         * @param name назва параметра для тексту винятку
         * @throws std::domain_error якщо value <= 0 або не є скінченним
         */
        template <floating_point_like Real>
        inline void require_positive(const Real value, const std::string_view name);

        /**
         * Перевірка, що значення не відємне.
         * @param value число для перевірки
         * @param name назва параметра для тексту винятку
         * @throws std::domain_error якщо value < 0 або не є скінченним
         */
        template <floating_point_like Real>
        inline void require_non_negative(const Real value, const std::string_view name);

        /**
         * Перевірка, що probability належить відрізку [0, 1].
         * @param value імовірність
         * @param name назва параметра для тексту винятку
         * @throws std::domain_error якщо value не належить [0, 1]
         */
        template <floating_point_like Real>
        inline void require_probability_closed(const Real value, const std::string_view name);

        /**
         * Перевірка, що probability належить інтервалу (0, 1).
         * @param value імовірність
         * @param name назва параметра для тексту винятку
         * @throws std::domain_error якщо value не належить (0, 1)
         */
        template <floating_point_like Real>
        inline void require_probability_open(const Real value, const std::string_view name);

        /**
         * Перевірка кількості випробувань у біноміальному законі.
         * @param n кількість випробувань
         * @throws std::domain_error якщо n < 0
         */
        inline void require_non_negative_int(const int n, const std::string_view name);

        /**
         * Перевірка меж цілочисельного інтервалу.
         * @param lo нижня межа
         * @param hi верхня межа
         * @throws std::domain_error якщо lo > hi
         */
        inline void require_ordered_int_interval(int lo, int hi, const std::string_view lo_name, const std::string_view hi_name);

        /**
         * Перевірка коректності числа успіхів для біноміального закону.
         * @param m число успіхів
         * @param n число випробувань
         * @throws std::domain_error якщо m < 0 або m > n
         */
        inline void require_binomial_k(const int m, const int n, const std::string_view name);

        /**
         * Число 1 / sqrt(2 pi).
         * @return константа для нормальної щільності
         */
        template <floating_point_like Real>
        [[nodiscard]] inline constexpr Real inv_sqrt_2pi() noexcept;
    }

    /**
     * Щільність стандартного нормального розподілу.
     * f(x) = 1 / sqrt(2 pi) * exp( -x^2 / 2 )
     *
     * @param x аргумент
     * @return значення щільності
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real phi(Real x) noexcept;

    /**
     * Функція розподілу стандартного нормального закону.
     * Використовується Boost.Math
     *
     * @param x аргумент
     * @return P(Z <= x), де Z ~ N(0, 1)
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real normal_cdf(Real x);

    /**
     * Таблична функція Лапласа.
     * Phi(x) = F(x) - 0.5, де F це CDF стандартного нормального закону.
     *
     * @param x аргумент
     * @return значення табличної функції Лапласа
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real laplace_phi(Real x);

    /**
     * Обернена таблична функція Лапласа.
     * Для заданого y з інтервалу (-0.5, 0.5) повертає x таке, що
     * laplace_phi(x) = y.
     *
     * @param y значення табличної функції Лапласа
     * @return аргумент x
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real inverse_laplace_phi(Real y);

    /**
     * Квантиль стандартного нормального розподілу.
     * Використовується Boost.Math
     *
     * alpha = 0.05 означає правохвостову критичну точку рівня 5%
     *
     * @param alpha рівень значущості з інтервалу (0, 1)
     * @return z таке, що P(Z <= z) = 1 - alpha
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real z_critical(Real alpha);

    /**
     * Двостороннє p value для нормального критерію.
     * Обчислює 2 * min(F(z), 1 - F(z)).
     *
     * @param z статистика критерію
     * @return двостороннє p value
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real normal_two_tailed_p_value(Real z);

    /**
     * Точна формула Бернуллі.
     * P(X = m), де X ~ Bin(n, p)
     *
     * @param n кількість випробувань
     * @param m кількість успіхів
     * @param p імовірність успіху
     * @return точна ймовірність
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real bernoulli_exact(int n, int m, Real p);

    /**
     * Біноміальна функція розподілу.
     * P(X <= m), де X ~ Bin(n, p)
     *
     * @param n кількість випробувань
     * @param m верхня межа числа успіхів
     * @param p імовірність успіху
     * @return кумулятивна ймовірність
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real binomial_cdf(int n, int m, Real p);

    /**
     * Локальна теорема Лапласа для біноміального розподілу.
     * Наближення для P(X = m), де X ~ Bin(n, p)
     *
     * @param n кількість випробувань
     * @param m кількість успіхів
     * @param p імовірність успіху
     * @return асимптотичне наближення
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real laplace_local(int n, int m, Real p);

    /**
     * Інтегральна теорема Лапласа без поправки на неперервність.
     * Наближення для P(m1 <= X <= m2), де X ~ Bin(n, p)
     *
     * @param n кількість випробувань
     * @param m1 нижня межа
     * @param m2 верхня межа
     * @param p імовірність успіху
     * @return асимптотичне наближення
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real laplace_integral(int n, int m1, int m2, Real p);

    /**
     * Інтегральна теорема Лапласа з поправкою на неперервність.
     * Наближення для P(m1 <= X <= m2), де X ~ Bin(n, p)
     *
     * @param n кількість випробувань
     * @param m1 нижня межа
     * @param m2 верхня межа
     * @param p імовірність успіху
     * @return асимптотичне наближення
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real laplace_integral_cc(int n, int m1, int m2, Real p);

    /**
     * Формула Пуассона для ймовірності рівно m подій.
     * P(X = m), де X ~ Pois(lambda)
     *
     * @param m кількість подій
     * @param lambda параметр закону
     * @return ймовірність
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real poisson_pmf(int m, Real lambda);

    /**
     * Кумулятивна функція розподілу Пуассона.
     * P(X <= m), де X ~ Pois(lambda)
     *
     * @param m верхня межа кількості подій
     * @param lambda параметр закону
     * @return кумулятивна ймовірність
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real poisson_cdf(int m, Real lambda);

    /**
     * Математичне сподівання біноміального розподілу.
     * Для X ~ Bin(n, p) маємо E[X] = n p
     *
     * @param n кількість випробувань
     * @param p імовірність успіху
     * @return математичне сподівання
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real binomial_mean(int n, Real p) noexcept;

    /**
     * Дисперсія біноміального розподілу.
     * Для X ~ Bin(n, p) маємо Var(X) = n p (1 - p)
     *
     * @param n кількість випробувань
     * @param p імовірність успіху
     * @return дисперсія
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real binomial_variance(int n, Real p) noexcept;

    /**
     * Математичне сподівання розподілу Пуассона.
     * Для X ~ Pois(lambda) маємо E[X] = lambda
     *
     * @param lambda параметр закону
     * @return математичне сподівання
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real poisson_mean(Real lambda) noexcept;

    /**
     * Дисперсія розподілу Пуассона.
     * Для X ~ Pois(lambda) маємо Var(X) = lambda
     *
     * @param lambda параметр закону
     * @return дисперсія
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline Real poisson_variance(Real lambda) noexcept;

    /**
     * Математичне сподівання стандартного нормального розподілу.
     * Для Z ~ N(0, 1) маємо E[Z] = 0
     *
     * @return математичне сподівання
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline constexpr Real normal_mean() noexcept;

    /**
     * Дисперсія стандартного нормального розподілу.
     * Для Z ~ N(0, 1) маємо Var(Z) = 1
     *
     * @return дисперсія
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline constexpr Real normal_variance() noexcept;

    /**
     * Єдина обгортка для параметризованих розподілів.
     * Забезпечує уніфікований доступ до pdf, cdf, quantile, mean і variance.
     */
    template <typename Distribution>
    class distribution_wrapper final
    {
    public:
        using distribution_type = Distribution;

        /**
         * Створення обгортки над конкретним розподілом.
         * @param distribution екземпляр розподілу Boost.Math
         */
        explicit constexpr distribution_wrapper(Distribution distribution) noexcept(std::is_nothrow_move_constructible_v<Distribution>);

        /**
         * Доступ до збереженого розподілу.
         * @return константне посилання на розподіл
         */
        [[nodiscard]] constexpr const Distribution& native() const noexcept;

        /**
         * Узагальнений pdf.
         * @param x аргумент
         * @return щільність або маса ймовірності
         */
        template <floating_point_like Real>
        [[nodiscard]] Real pdf(Real x) const;

        /**
         * Узагальнений cdf.
         * @param x аргумент
         * @return кумулятивна ймовірність
         */
        template <floating_point_like Real>
        [[nodiscard]] Real cdf(Real x) const;

        /**
         * Узагальнений quantile.
         * @param p імовірність з інтервалу [0, 1]
         * @return квантиль
         */
        template <floating_point_like Real>
        [[nodiscard]] Real quantile(Real p) const;

        /**
         * Узагальнене математичне сподівання.
         * @return математичне сподівання
         */
        template <floating_point_like Real = double>
        [[nodiscard]] Real mean() const;

        /**
         * Узагальнена дисперсія.
         * @return дисперсія
         */
        template <floating_point_like Real = double>
        [[nodiscard]] Real variance() const;

    private:
        Distribution distribution_;
    };

    /**
     * Фабрична функція для стандартного нормального розподілу.
     * @return уніфікована обгортка над N(0, 1)
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline auto make_standard_normal();

    /**
     * Фабрична функція для нормального розподілу N(mean, sigma).
     * @param mean математичне сподівання
     * @param sigma стандартне відхилення, sigma > 0
     * @return уніфікована обгортка
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline auto make_normal(Real mean, Real sigma);

    /**
     * Фабрична функція для біноміального розподілу Bin(n, p).
     * @param n кількість випробувань
     * @param p імовірність успіху
     * @return уніфікована обгортка
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline auto make_binomial(int n, Real p);

    /**
     * Фабрична функція для розподілу Пуассона Pois(lambda).
     * @param lambda параметр закону
     * @return уніфікована обгортка
     */
    template <floating_point_like Real = double>
    [[nodiscard]] inline auto make_poisson(Real lambda);
}

namespace stats
{
    namespace discrete
    {
        /**
         * Табличний дискретний розподіл.
         *
         * Задається скінченним набором значень випадкової величини та
         * відповідних їм імовірностей.
         *
         * Використовується для задач, де закон розподілу задано явно у вигляді
         * таблиці:
         * x1, x2, ..., xn
         * p1, p2, ..., pn
         *
         * Інваріанти:
         * - масив значень не порожній
         * - кількість значень дорівнює кількості ймовірностей
         * - кожна ймовірність належить [0, 1]
         * - сума ймовірностей дорівнює 1 з допустимою похибкою
         */
        template <floating_point_like Real = double>
        class table_distribution;

        /**
         * Фабрична функція для табличного дискретного розподілу.
         *
         * Створює розподіл за набором значень випадкової величини та
         * відповідних імовірностей.
         *
         * @param values можливі значення випадкової величини
         * @param probabilities імовірності відповідних значень
         * @return табличний дискретний розподіл
         *
         * @throws std::domain_error якщо:
         * - values порожній
         * - sizes values і probabilities не збігаються
         * - деяка ймовірність не належить [0, 1]
         * - сума ймовірностей не дорівнює 1
         */
        template <floating_point_like Real = double>
        [[nodiscard]] table_distribution<Real>
        make_table_distribution(std::vector<Real> values,
                                std::vector<Real> probabilities);

        /**
         * Фабрична функція для розподілу Бернуллі Bernoulli(p).
         *
         * Моделює одне випробування з двома результатами:
         * успіх з імовірністю p
         * неуспіх з імовірністю 1 - p
         *
         * @param p імовірність успіху
         * @return уніфікована обгортка над розподілом Бернуллі
         *
         * @throws std::domain_error якщо p не належить [0, 1]
         */
        template <floating_point_like Real = double>
        [[nodiscard]] auto make_bernoulli(Real p);

        /**
         * Фабрична функція для геометричного розподілу Geometric(p).
         *
         * Моделює кількість невдач до першого успіху
         * або еквівалентну дискретну схему, яку використовує Boost.Math.
         *
         * @param p імовірність успіху в одному випробуванні
         * @return уніфікована обгортка над геометричним розподілом
         *
         * @throws std::domain_error якщо p не належить (0, 1)
         */
        template <floating_point_like Real = double>
        [[nodiscard]] auto make_geometric(Real p);

        /**
         * Фабрична функція для гіпергеометричного розподілу.
         *
         * Моделює кількість успіхів у вибірці без повернення з кінцевої
         * генеральної сукупності.
         *
         * @param successes кількість успішних елементів у генеральній сукупності
         * @param draws кількість вибірок без повернення
         * @param population загальний обсяг генеральної сукупності
         * @return уніфікована обгортка над гіпергеометричним розподілом
         *
         * @throws std::domain_error якщо:
         * - population == 0
         * - successes > population
         * - draws > population
         */
        template <floating_point_like Real = double>
        [[nodiscard]] auto make_hypergeometric(unsigned successes,
                                               unsigned draws,
                                               unsigned population);

        /**
         * Фабрична функція для негативного біноміального розподілу.
         *
         * Моделює число невдач до досягнення заданої кількості успіхів
         * у незалежних випробуваннях.
         *
         * @param failures параметр розподілу, що задає число невдач
         * або відповідний параметр у термінах реалізації Boost.Math
         * @param p імовірність успіху в одному випробуванні
         * @return уніфікована обгортка над негативним біноміальним розподілом
         *
         * @throws std::domain_error якщо p не належить (0, 1)
         */
        template <floating_point_like Real = double>
        [[nodiscard]] auto make_negative_binomial(unsigned failures, Real p);
    }
}

#include "stats.tpp"
