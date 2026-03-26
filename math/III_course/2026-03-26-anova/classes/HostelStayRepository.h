// HostelStayRepository.h
#pragma once

#include "DatabaseConnection.h"
#include "HostelStay.h"
#include <vector>

template<typename Connection = PGconn>
class HostelStayRepository
{
public:
    explicit HostelStayRepository(const std::string& connectionString);

    void saveAll(const std::vector<HostelStay>& stays);

private:
    DatabaseConnection<Connection> connection_;
};

#include "../HostelStayRepository.tpp"
