#pragma once

#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

template<typename Record>
std::vector<Record> CsvToHostelStayMapper<Record>::read(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити CSV файл");

    std::vector<Record> result;
    std::string line;

    if (!std::getline(file, line)) throw std::runtime_error("CSV файл порожній");

    int rowIndex = 0;
    while (std::getline(file, line))
    {
        ++rowIndex;

        if (trim(line).empty()) continue;

        const auto fields = splitLine(line);

        if (!isValidStayRow(fields)) continue;

        try
        {
            Record record = mapRow(fields);

            if (record.stayDays == 1 || record.stayDays == 7 || record.stayDays == 28)
            {
                result.push_back(record);
            }
        }
        catch (const std::exception& ex)
        {
            std::cout << "Рядок " << rowIndex << " пропущено. Причина: " << ex.what() << '\n';
        }
    }

    return result;
}

template<typename Record>
std::vector<std::string> CsvToHostelStayMapper<Record>::splitLine(const std::string& line)
{
    std::vector<std::string> fields;
    std::string current;

    for (char ch : line)
    {
        if (ch == ';')
        {
            fields.push_back(current);
            current.clear();
        }
        else current += ch;
    }

    fields.push_back(current);
    return fields;
}

// треба перевірити швидкість відпрацювання регулярки
// template<typename Record>
// bool CsvToHostelStayMapper<Record>::isDateLike(const std::string& value)
// {
//     static const std::regex pattern(R"(^\d{2}\.\d{2}\.\d{4}$)");
//
//     return std::regex_match(trim(value), pattern);
// }

template<typename Record>
bool CsvToHostelStayMapper<Record>::isDateLike(const std::string& value)
{
    const std::string v = trim(value);

    if (v.size() != 10 || v[2] != '.' || v[5] != '.') return false;

    for (int i = 0; i < 10; ++i)
    {
        if (i == 2 || i == 5) continue;

        if (!std::isdigit(static_cast<unsigned char>(v[i]))) return false;
    }

    return true;
}

template<typename Record>
bool CsvToHostelStayMapper<Record>::isValidStayRow(const std::vector<std::string>& fields)
{
    if (fields.size() < 23) return false;

    const std::string room = trim(fields[1]);
    const std::string checkin = trim(fields[4]);
    const std::string checkout = trim(fields[8]);
    const std::string prise = trim(fields[5]);
    const std::string stayTerm = trim(fields[6]);
    const std::string price = trim(fields[7]);
    const std::string hostel = trim(fields[22]);

    bool result = !room.empty() &&
                  room != "инкасация" && // Виключаємо рядки інкасації
                  room != "свободное" && // Виключаємо рядки без оплат
                  hostel != "тюрьма" &&  // Виключаємо рядки що належать хостелу тюрьма
                  isDateLike(checkin) &&
                  isDateLike(checkout) &&
                  !prise.empty() &&
                  !stayTerm.empty() &&
                  !price.empty();

    if (!result) return false;

    try
    {
        const int parsedPrise = std::stoi(prise);
        const int parsedStayTerm = std::stoi(stayTerm);
        const double parsedPrice = normalizePrice(price);

        return
            parsedPrise > 0 &&
            parsedStayTerm > 0 &&
            parsedPrice > 0.0;
    }
    catch (...)
    {
        return false;
    }
}

template<typename Record>
Record CsvToHostelStayMapper<Record>::mapRow(const std::vector<std::string>& fields)
{
    Record r;

    r.hostel = trim(fields[22]);
    r.room = trim(fields[1]);
    r.lastName = trim(fields[2]);
    r.fullName = trim(fields[3]);

    r.sourceFileDate = normalizeDate(fields[0]);
    r.checkinDate = normalizeDate(fields[4]);
    r.checkoutDate = normalizeDate(fields[8]);

    r.prise = std::stoi(trim(fields[5]));
    r.tariffTerm = std::stoi(trim(fields[6]));

    r.stayDays = calculateStayDays(r.checkinDate, r.checkoutDate);

    r.totalPrice = normalizePrice(fields[7]);
    r.revenuePerDay = r.totalPrice / static_cast<double>(r.stayDays);

    r.source = trim(fields[16]);

    const char* msg = (r.prise <= 0) ? "Поле PRISE має бути додатним числом" :
                      (r.tariffTerm <= 0) ? "Строк проживання має бути додатним числом" :
                      (r.stayDays <= 0) ? "Фактична тривалість проживання має бути більшою за нуль" : nullptr;

    msg ? throw std::invalid_argument(msg) : void();

    r.totalPrice = normalizePrice(fields[7]);

    const char* price_msg = (r.totalPrice <= 0.0) ? "Ціна проживання має бути більшою за нуль" : nullptr;

    price_msg ? throw std::invalid_argument(price_msg) : void();

    return r;
}

template<typename Record>
std::string CsvToHostelStayMapper<Record>::trim(const std::string& value)
{
    const auto begin = value.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) return "";

    const auto end = value.find_last_not_of(" \t\r\n");
    return value.substr(begin, end - begin + 1);
}

template<typename Record>
std::string CsvToHostelStayMapper<Record>::normalizeDate(const std::string& value)
{
    const std::string v = trim(value);

    if (!isDateLike(v)) throw std::invalid_argument("Невірний формат дати");

    const std::string day = v.substr(0, 2);
    const std::string month = v.substr(3, 2);
    const std::string year = v.substr(6, 4);

    return year + "-" + month + "-" + day;
}

template<typename Record>
double CsvToHostelStayMapper<Record>::normalizePrice(const std::string& value)
{
    std::string clean;

    for (unsigned char ch : value)
    {
        if ((ch >= '0' && ch <= '9') || ch == ',' || ch == '.')
            clean += (ch == ',') ? '.' : static_cast<char>(ch);
    }

    if (clean.empty()) throw std::invalid_argument("price is empty");

    return std::stod(clean);
}

template<typename Record>
int CsvToHostelStayMapper<Record>::calculateStayDays(
    const std::string& checkinDate,
    const std::string& checkoutDate
)
{
    if (checkinDate.size() != 10 || checkoutDate.size() != 10)
    {
        throw std::invalid_argument("Невірний формат нормалізованої дати");
    }
    const int y1 = std::stoi(checkinDate.substr(0, 4));
    const int m1 = std::stoi(checkinDate.substr(5, 2));
    const int d1 = std::stoi(checkinDate.substr(8, 2));

    const int y2 = std::stoi(checkoutDate.substr(0, 4));
    const int m2 = std::stoi(checkoutDate.substr(5, 2));
    const int d2 = std::stoi(checkoutDate.substr(8, 2));

    auto toDays = [](int y, int m, int d)
    {
        y -= m <= 2;
        const int era = (y >= 0 ? y : y - 399) / 400;
        const auto yoe = static_cast<unsigned>(y - era * 400);
        const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
        return era * 146097 + static_cast<int>(doe);
    };

    return toDays(y2, m2, d2) - toDays(y1, m1, d1);
}