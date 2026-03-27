#include <filesystem>
#include <iostream>

#include "classes/EnvAnova.h"
#include "classes/CsvToHostelStayMapper.h"
#include "classes/HostelStayRepository.h"

// Читання датасету з csv, нормалізація, мапинг на вектор, додавання до БД
void read_normalization_and_save_to_db()
{
    const std::filesystem::path filePath = EnvAnova::csvPath;
    const std::vector<HostelStay> stays =
        CsvToHostelStayMapper<>::read(filePath);

    std::cout << "stays.size() = " << stays.size() << '\n';
    HostelStayRepository<> repository(EnvAnova::connectionString);
    repository.saveAll(stays);
}

int main()
{
    read_normalization_and_save_to_db();

    return 0;
}