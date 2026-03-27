// CsvToHostelStayMapper.h
#pragma once

#include "HostelStay.h"
#include <string>
#include <vector>

/**
 *
 * Клас для читання CSV і перетворення рядків у структури проживання
 *
 * @tparam Record тип результату
 */
template<typename Record = HostelStay>
class CsvToHostelStayMapper
{
public:
    /**
     *
     * Читає файл і повертає готові структури
     *
     * @param filePath шлях до файлу
     * @return всі валідні записи
     */
    static std::vector<Record> read(const std::string& filePath);

private:
    /**
     *
     * Розбиває рядок по роздільнику
     *
     * @param line рядок CSV
     * @return поля рядка
     */
    static std::vector<std::string> splitLine(const std::string& line);

    /**
     *
     * Перевіряє, чи схожий рядок на дату у форматі dd.mm.yyyy
     *
     * @param value дата
     * @return чи є рядок схожим на дату
     */
    static bool isDateLike(const std::string& value);

    /**
     *
     * Відсіює сміття і службові записи
     *
     * @param fields поля CSV
     * @return чи валідний рядок
     */
    static bool isValidStayRow(const std::vector<std::string>& fields);

    /**
     *
     * Перетворює рядок у доменну модель
     *
     * @param fields поля CSV
     * @return структура Record
     */
    static Record mapRow(const std::vector<std::string>& fields);

    /**
     *
     * Прибирає пробіли
     *
     * @param value рядок
     * @return очищений рядок
     */
    static std::string trim(const std::string& value);

    /**
     *
     * Перетворює формат дати
     *
     * @param value дата
     * @return нормалізована дата
     */
    static std::string normalizeDate(const std::string& value);

    /**
     *
     * Чистить і парсить значення
     *
     * @param value ціна
     * @return число
     */
    static double normalizePrice(const std::string& value);

    /**
     *
     * Рахує тривалість проживання
     *
     * @param checkinDate дата заїзду
     * @param checkoutDate дата виїзду
     * @return кількість днів
     */
    static int calculateStayDays(const std::string& checkinDate, const std::string& checkoutDate);
};

#include "CsvToHostelStayMapper.tpp"
