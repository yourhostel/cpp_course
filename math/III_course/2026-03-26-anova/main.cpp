#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include "classes/EnvAnova.h"
#include "classes/CsvToHostelStayMapper.h"
#include "classes/HostelStayRepository.h"
#include <boost/math/distributions/fisher_f.hpp>

constexpr auto YELLOW  = "\033[33m";
constexpr auto CYAN    = "\033[36m";
constexpr auto RESET = "\033[0m";

/**
 * Обчислення критичного значення через квантиль F розподілу.
 * Використовується Boost.Math
 *
 * 0.05 - стандарт, 0.01 - строгіша перевірка, 0.001 - дуже строгий критерій
 * @param alpha = рівень значущості
 * @param d1 = k − 1 (df_between)
 * @param d2 = N − k (df_within)
 * @return
 */
double f_critical(const double alpha, const double d1, const double d2)
{
    const boost::math::fisher_f_distribution<> dist(d1, d2);
    return boost::math::quantile(dist, 1.0 - alpha);
}

void print_row(const std::vector<std::string>& row, int width)
{
    auto center = [width](const std::string& s)
    {
        if (static_cast<int>(s.size()) >= width) return s.substr(0, width);

        const int pad_left = (width - static_cast<int>(s.size())) / 2;
        const int pad_right = width - pad_left - static_cast<int>(s.size());

        return std::string(pad_left, ' ') + s + std::string(pad_right, ' ');
    };

    for (const auto& cell : row) std::cout << center(cell);

    std::cout << "\n";
}

std::string format_double(const double value)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;
    return out.str();
}

void rend_critical(const std::vector<GroupStats>& stats)
{
    std::size_t total_n = 0;

    for (const auto& s : stats) total_n += s.group_size;

    std::cout << YELLOW << "F critical: " << RESET
              << f_critical(0.05,
                  static_cast<double>(stats.size() - 1),
                  static_cast<double>(total_n - stats.size()))
              << "\n";
}

void print_group_stats(const std::vector<GroupStats>& stats)
{
    const int w = 12;

    const std::vector<std::string> headers =
    {
        "group", "n", "mean", "var", "min", "max", "median", "p25", "p75"
    };

    print_row(headers, w);

    for (std::size_t i = 0; i < headers.size(); ++i) std::cout << std::string(w, '=');

    std::cout << "\n";

    for (const auto& r : stats)
    {
        print_row(
            {
                std::to_string(r.group_id),
                std::to_string(r.group_size),
                format_double(r.group_mean),
                format_double(r.within_group_variance),
                format_double(r.min_value),
                format_double(r.max_value),
                format_double(r.median),
                format_double(r.p25),
                format_double(r.p75)
            },
            w
        );
    }

    std::cout << "\n";

    rend_critical(stats);
}

// Читання датасету з csv, нормалізація, мапинг на вектор, додавання до БД
void read_normalization_and_save_to_db(HostelStayRepository<>& repository)
{
    const std::filesystem::path filePath = EnvAnova::csvPath;
    const std::vector<HostelStay> stays =
        CsvToHostelStayMapper<>::read(filePath);

    std::cout << "stays.size() = " << stays.size() << '\n';

    repository.saveAll(stays);
}

void rend_stats(const std::pair<std::optional<std::string>, std::optional<std::string>>& pair,
                HostelStayRepository<>& repository)
{
    const auto& date_from = pair.first;
    const auto& date_to = pair.second;

    std::cout << CYAN << "\n=== PERIOD: "
        << (date_from ? *date_from : "NULL")
        << " - "
        << (date_to ? *date_to : "NULL")
        << " ===\n" << RESET;

    std::cout << YELLOW << "\nСтатистика:\n" << RESET;
    print_group_stats(repository.get_group_stats(date_from, date_to));

    std::cout << YELLOW << "ANOVA F: " << RESET
        << repository.calculate_fisher(date_from, date_to)
        << "\n";
}

void stats(HostelStayRepository<>& repository)
{
    std::ranges::for_each(std::vector<std::pair<std::optional<std::string>,
        std::optional<std::string> >>{
        {"2019-01-01", "2019-12-31"},
        {"2020-01-01", "2020-12-31"},
        {"2021-01-01", "2021-12-31"},
        {"2022-01-01", "2022-12-31"},
        {"2023-01-01", "2023-12-31"},
        {std::nullopt, std::nullopt}
    },[&](const auto& r){rend_stats(r, repository);});
}



int main()
{
    HostelStayRepository<> repository(EnvAnova::connectionString);

    // read_normalization_and_save_to_db(repository);

    stats(repository);

    return 0;
}