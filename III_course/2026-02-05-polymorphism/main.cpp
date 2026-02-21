#include <iostream>
#include <list>
#include <memory>
#include <ranges>
#include <algorithm>

// =====================================================================================================================
// Структура для вхідних даних
// n задано умовою; з точки зору алгоритму достатньо самого списку, можливе читання до кінця вводу
// =====================================================================================================================
struct InputData {
    std::size_t n{};
    std::list<double> a{};
};

// =====================================================================================================================
// Зчитування n та послідовності
// =====================================================================================================================
InputData read_input()
{
    InputData in;
    std::cin >> in.n;
    for (std::size_t i = 0; i < in.n; ++i)
    {
        double x;
        std::cin >> x;
        in.a.push_back(x);
    }
    return in;
}

// =====================================================================================================================
// Виведення у зворотному порядку
// =====================================================================================================================
void print_reverse(const std::list<double>& a)
{
    for (const double it : std::ranges::reverse_view(a)) std::cout << it << ' ';
}

// =====================================================================================================================
// 1) Простий обхід
// =====================================================================================================================
std::list<double> solve_plain(const InputData& in)
{
    std::list<double> out = in.a;

    bool has_lt_m3 = false;
    for (const double x : out)
    {
        if (x < -3.0)
        {
            has_lt_m3 = true;
            break;
        }
    }

    if (has_lt_m3)
    {
        for (double& x : out)
        {
            if (x < 0.0)
                x = x * x;
        }
    }
    else
    {
        for (double& x : out)
            x *= 0.1;
    }

    return out;
}

// =====================================================================================================================
// 2) Ad hoc поліморфізм: перевантаження функцій
// =====================================================================================================================
bool has_less_than(const std::list<double>& a, const double bound) {
    // any_of повертає true, якщо існує елемент, що задовольняє предикат
    return std::ranges::any_of(a, [bound](const double x) { return x < bound; });
}

bool has_less_than(const std::list<float>& a, const float bound) {
    // аналогічно для float
    return std::ranges::any_of(a, [bound](const float x) { return x < bound; });
}

std::list<double> solve_ad_hoc_overload(const InputData& in)
{
    std::list<double> out = in.a;

    if (has_less_than(out, -3.0))
    {
        for (double& x : out)
        {
            if (x < 0.0)
                x = x * x;
        }
    }
    else
    {
        for (double& x : out)
            x *= 0.1;
    }

    return out;
}

// =====================================================================================================================
// 3) Параметричний поліморфізм: шаблони C++
// =====================================================================================================================
template<class T>
bool has_less_than_t(const std::list<T>& a, const T& bound) {
    return std::ranges::any_of(
        a,
        [&bound](const T& x) { return x < bound; }
    );
}

template<class T>
void scale_all_t(std::list<T>& a, const T& k)
{
    for (T& x : a) x *= k;
}

template<class T>
void square_negative_t(std::list<T>& a)
{
    for (T& x : a)
    {
        if (x < T{0})
            x = x * x;
    }
}

template<class T>
std::list<T> solve_parametric_template_impl(const std::list<T>& src, const T& bound, const T& k)
{
    std::list<T> out = src;

    if (has_less_than_t(out, bound))
    {
        square_negative_t(out);
    }
    else
    {
        scale_all_t(out, k);
    }

    return out;
}

std::list<double> solve_parametric_templates(const InputData& in)
{
    return solve_parametric_template_impl<double>(in.a, -3.0, 0.1);
}

// =====================================================================================================================
// 4) Підтиповий поліморфізм: virtual інтерфейс (runtime dispatch)
// =====================================================================================================================
struct IListProcessor {
    virtual ~IListProcessor() = default;
    [[nodiscard]] virtual std::list<double> run(const InputData& in) const = 0;
};

// реалізацію інтерфейсу, як класу поведінки
struct ProcessorRule : IListProcessor {
    [[nodiscard]] std::list<double> run(const InputData& in) const override
    {
        std::list<double> out = in.a;

        const bool has_lt_m3 =
            std::ranges::any_of(out, [](const double x) { return x < -3.0; });

        if (has_lt_m3)
        {
            for (double& x : out)
            {
                if (x < 0.0)
                    x = x * x;
            }
        }
        else
        {
            for (double& x : out)
                x *= 0.1;
        }

        return out;
    }
};

std::list<double> solve_subtype_virtual(const InputData& in) {
    const std::unique_ptr<IListProcessor> p = std::make_unique<ProcessorRule>();
    return p->run(in);
}

int main()
{
    const InputData in = read_input();

    // const std::list<double> result = solve_plain(in);
    // const std::list<double> result = solve_ad_hoc_overload(in);
     const std::list<double> result = solve_parametric_templates(in);
    // const std::list<double> result = solve_subtype_virtual(in);

    print_reverse(result);
    return 0;
}
