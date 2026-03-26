#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>

template<typename Record>
std::vector<Record> CsvToHostelStayMapper<Record>::read(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error("cannot open csv file");
    }

    std::vector<Record> result;
    std::string line;

    std::getline(file, line);
    int rowIndex = 0;
    while (std::getline(file, line))
    {
        ++rowIndex;
        if (line.empty())
        {
            continue;
        }

        const auto fields = splitLine(line);

        if (!isValidStayRow(fields))
        {
            continue;
        }

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
            std::cout << "row " << rowIndex << " parse error: " << ex.what() << '\n';
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
        else
        {
            current += ch;
        }
    }

    fields.push_back(current);
    return fields;
}

template<typename Record>
bool CsvToHostelStayMapper<Record>::isValidStayRow(const std::vector<std::string>& fields)
{
    if (fields.size() < 23)
    {
        return false;
    }

    const std::string room = trim(fields[1]);
    const std::string checkin = trim(fields[4]);
    const std::string checkout = trim(fields[8]);

    if (room == "инкасация")
    {
        return false;
    }

    if (checkin.empty() || checkout.empty())
    {
        return false;
    }

    return true;
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

    return r;
}

template<typename Record>
std::string CsvToHostelStayMapper<Record>::trim(const std::string& value)
{
    const auto begin = value.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos)
    {
        return "";
    }

    const auto end = value.find_last_not_of(" \t\r\n");
    return value.substr(begin, end - begin + 1);
}

template<typename Record>
std::string CsvToHostelStayMapper<Record>::normalizeDate(const std::string& value)
{
    const std::string v = trim(value);

    const std::string d = v.substr(0, 2);
    const std::string m = v.substr(3, 2);
    const std::string y = v.substr(6, 4);

    return y + "-" + m + "-" + d;
}

template<typename Record>
double CsvToHostelStayMapper<Record>::normalizePrice(const std::string& value)
{
    std::string clean;

    for (unsigned char ch : value)
    {
        if (ch == ',')
        {
            clean += '.';
        }
        else if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == 0xA0)
        {
        }
        else
        {
            clean += static_cast<char>(ch);
        }
    }

    clean = trim(clean);

    if (clean.empty())
    {
        throw std::invalid_argument("price is empty");
    }

    return std::stod(clean);
}

template<typename Record>
int CsvToHostelStayMapper<Record>::calculateStayDays(
    const std::string& checkin,
    const std::string& checkout
)
{
    const int y1 = std::stoi(checkin.substr(0, 4));
    const int m1 = std::stoi(checkin.substr(5, 2));
    const int d1 = std::stoi(checkin.substr(8, 2));

    const int y2 = std::stoi(checkout.substr(0, 4));
    const int m2 = std::stoi(checkout.substr(5, 2));
    const int d2 = std::stoi(checkout.substr(8, 2));

    auto toDays = [](int y, int m, int d)
    {
        y -= m <= 2;
        const int era = (y >= 0 ? y : y - 399) / 400;
        const unsigned yoe = static_cast<unsigned>(y - era * 400);
        const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
        return era * 146097 + static_cast<int>(doe);
    };

    return toDays(y2, m2, d2) - toDays(y1, m1, d1);
}