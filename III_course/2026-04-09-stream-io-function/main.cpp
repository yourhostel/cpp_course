//
// Created by tysser on 09.04.26.
//

#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <ostream>

#include "Function.h"

template <typename T>
std::map<std::string, std::function<T(T)>> make_function_registry()
{
    return {
            {"sin",   [](T x){ return std::sin(x); }},
            {"cos",   [](T x){ return std::cos(x); }},
            {"exp",   [](T x){ return std::exp(x); }},
            {"log",   [](T x){ return std::log(x); }},
            {"square",[](T x){ return x * x; }},
            {"cube",  [](T x){ return x * x * x; }},
            {"linear",[](T x){ return x; }},
            {"sqrt",  [](T x){ return std::sqrt(x); }},
            {"inv", [](T x){ return T(1) / (x + T(1)); }},
            // Діодоподібна характеристика
            {"diode", [](T x){
                if (x < T(0.6)) return T(0);
                return std::exp(T(10) * (x - T(0.6)));
            }},
            // гіперболічний тангенс
            {"tanh", [](T x){
                return std::tanh(x);
            }},
            // Сигмоїда
            {"sigmoid", [](T x){
                return T(1) / (T(1) + std::exp(-x));
            }},
            // Абсолютне значення
            {"abs", [](T x){
            return std::abs(x);
            }},
            // Пилкоподібна
            {"saw", [](T x){
            return x - std::floor(x);
            }},
            // Гаус
            {"gauss", [](T x){
            return std::exp(-x * x);
            }}

    };
}

template <typename T>
void generate_from_registry(
    const std::map<std::string, std::function<T(T)>>& registry,
    const std::string& f1_name,
    const std::string& f2_name,
    T x_min, T x_max, T step
)
{
    auto it1 = registry.find(f1_name);
    auto it2 = registry.find(f2_name);

    if (it1 == registry.end() || it2 == registry.end()) return;

    const std::string file_name = f1_name + "_" + f2_name + ".txt";

    // std::cout << std::filesystem::current_path() << std::endl;
    std::ofstream out("../../../III_course/2026-04-09-stream-io-function/" + file_name);
    if (!out) return;

    out << std::fixed << std::setprecision(3);

    auto print_row = [&](T x)
    {
        out << std::setw(6) << x << "  "
            << std::setw(8) << it1->second(x) << "  "
            << std::setw(8) << it2->second(x) << '\n';
    };

    for (T x = x_min; x <= x_max; x += step) print_row(x);
}

void gen()
{
    const auto registry = make_function_registry<double>();

    // generate_from_registry(registry, "sin", "cos", 0.0, 6.0, 0.2);
    generate_from_registry(registry, "log", "exp", 0.2, 3.0, 0.2);
    generate_from_registry(registry, "square", "cube", -2.0, 2.0, 0.2);
    generate_from_registry(registry, "linear", "square", -2.0, 2.0, 0.2);
    // generate_from_registry(registry, "linear", "cube", -2.0, 2.0, 0.2);
    // generate_from_registry(registry, "sin", "square", -3.0, 3.0, 0.2);
    // generate_from_registry(registry, "cos", "linear", -3.0, 3.0, 0.2);
    // generate_from_registry(registry, "sqrt", "linear", 0.0, 4.0, 0.2);
    // generate_from_registry(registry, "sqrt", "square", 0.0, 4.0, 0.2);
    generate_from_registry(registry, "inv", "linear", -0.9, 3.0, 0.2);
    // generate_from_registry(registry, "inv", "square", -0.9, 3.0, 0.2);
    // generate_from_registry(registry, "exp", "linear", 0.0, 3.0, 0.2);
    // generate_from_registry(registry, "sin", "cube", -2.0, 2.0, 0.2);
    // generate_from_registry(registry, "cos", "square", -2.0, 2.0, 0.2);
    // generate_from_registry(registry, "diode", "sigmoid", 0.0, 1.0, 0.05);
    // generate_from_registry(registry, "tanh", "gauss", -3.0, 3.0, 0.1);
    // generate_from_registry(registry, "abs", "saw", -2.0, 2.0, 0.1);
}

void test()
{
    std::ifstream in("log_exp.txt");
    // std::ifstream in("sin_cos.txt");
    // std::ifstream in("square_cube.txt");
    // std::ifstream in("inv_linear.txt");

    // std::ifstream in("abs_saw.txt");
     // std::ifstream in("diode_sigmoid.txt");
    // std::ifstream in("tanh_gauss.txt");

    if (!in) std::cerr << "file not opened\n";

    Function<double> f1(100, 1);
    Function<double> f2(100, 2);

    in >> f1;
    in.clear();
    in.seekg(0);

    in >> f2;

    std::cout << "Function 1:\n";
    std::cout << f1 << '\n';

    std::cout << "Function 2:\n";
    std::cout << f2 << '\n';

    print_min_max(f1, std::cout);
    print_min_max(f2, std::cout);
}

void test_2()
{
    const std::string base_path = "../../../III_course/2026-04-09-stream-io-function/";

    const std::string input_file  = base_path + "square_cube.txt";
    const std::string output_file = base_path + "square_cube_formatted.txt";

    Function<double>::convert_file_format(input_file, output_file);

    std::ifstream in(output_file);
    if (!in)
    {
        std::cerr << "formatted file not opened\n";
        return;
    }

    std::string line;
    while (std::getline(in, line))
    {
        std::cout << line << '\n';
    }
}

int main()
{
       test();
    // gen();
    // test_2();
   return 0;
}
