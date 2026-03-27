// HostelStayRepository.h
#pragma once

#include "DatabaseConnection.h"
#include "HostelStay.h"
#include "GroupStats.h"
#include <vector>

/**
 *
 * @tparam Connection
 */
template<typename Connection = PGconn>
class HostelStayRepository
{
public:
    /**
     *
     * @param connectionString
     */
    explicit HostelStayRepository(const std::string& connectionString);

    /**
     *
     * @param stays
     */
    void saveAll(const std::vector<HostelStay>& stays);

    /**
     *
     * @param date_from
     * @param date_to
     * @return
     */
    double calculate_fisher(
    const std::optional<std::string>& date_from,
    const std::optional<std::string>& date_to
    );

    /**
     *
     * @param date_from
     * @param date_to
     * @return
     */
    std::vector<GroupStats> get_group_stats(
        const std::optional<std::string>& date_from,
        const std::optional<std::string>& date_to
    );

private:
    /**
     *
     */
    void prepare_insert_hostel_stay_statement();

    /**
     *
     */
    void prepare_calculate_fisher_statement();

    /**
     *
     */
    void prepare_stats_by_group_statement();

private:
    /**
     *
     */
    DatabaseConnection<Connection> connection_;
};

#include "HostelStayRepository.tpp"
