// HostelStayRepository.tpp
#pragma once

#include <libpq-fe.h>
#include <stdexcept>
#include <string>

template<typename Connection>
HostelStayRepository<Connection>::HostelStayRepository(const std::string& connectionString)
    : connection_(connectionString)
{
    prepare_insert_hostel_stay_statement();
    prepare_calculate_fisher_statement();
    prepare_stats_by_group_statement();
}

template<typename Connection>
void HostelStayRepository<Connection>::prepare_insert_hostel_stay_statement()
{
    auto* conn = reinterpret_cast<PGconn*>(connection_.get());

    PGresult* res = PQprepare(
        conn,
        "insert_hostel_stay",
        R"sql(
            INSERT INTO hostel_stays
            (
                hostel,
                room,
                last_name,
                full_name,
                source_file_date,
                checkin_date,
                checkout_date,
                prise,
                tariff_term,
                stay_days,
                total_price,
                revenue_per_day,
                source
            )
            VALUES
            (
                $1,$2,$3,$4,$5,$6,$7,
                $8,$9,$10,$11,$12,$13
            )
        )sql",
        13,
        nullptr
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("Не вдалося підготувати запит insert_hostel_stay");
    }

    PQclear(res);
}

template<typename Connection>
void HostelStayRepository<Connection>::prepare_calculate_fisher_statement()
{
    auto* conn = reinterpret_cast<PGconn*>(connection_.get());

    PGresult* res = PQprepare(
        conn,
        "calculate_fisher_stmt",
        R"sql(
            SELECT calculate_fisher($1, $2)
        )sql",
        2,
        nullptr
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("Не вдалося підготувати запит calculate_fisher");
    }

    PQclear(res);
}

template<typename Connection>
void HostelStayRepository<Connection>::prepare_stats_by_group_statement()
{
    auto* conn = reinterpret_cast<PGconn*>(connection_.get());

    PGresult* res = PQprepare(
        conn,
        "stats_by_group_stmt",
        R"sql(
            SELECT *
            FROM stats_by_group($1, $2)
        )sql",
        2,
        nullptr
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("Не вдалося підготувати запит stats_by_group");
    }

    PQclear(res);
}

template<typename Connection>
void HostelStayRepository<Connection>::saveAll(const std::vector<HostelStay>& stays)
{
    PGconn* conn = reinterpret_cast<PGconn*>(connection_.get());

    PGresult* res = PQexec(conn, "begin");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("Не вдалося почати транзакцію");
    }
    PQclear(res);

    for (const HostelStay& s : stays)
    {
        const std::string prise = std::to_string(s.prise);
        const std::string tariff = std::to_string(s.tariffTerm);
        const std::string days = std::to_string(s.stayDays);
        const std::string total = std::to_string(s.totalPrice);
        const std::string revenue = std::to_string(s.revenuePerDay);

        const char* params[13] = { s.hostel.c_str(), s.room.c_str(), s.lastName.c_str(), s.fullName.c_str(),
            s.sourceFileDate.c_str(), s.checkinDate.c_str(), s.checkoutDate.c_str(), prise.c_str(), tariff.c_str(),
            days.c_str(), total.c_str(), revenue.c_str(), s.source.c_str()};

        res = PQexecPrepared(
            conn,
            "insert_hostel_stay",
            13,
            params,
            nullptr,
            nullptr,
            0
        );

        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            PQclear(res);

            PGresult* rollback_res = PQexec(conn, "rollback");
            PQclear(rollback_res);

            throw std::runtime_error("Не вдалося додати запис у hostel_stays");
        }

        PQclear(res);
    }

    res = PQexec(conn, "commit");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("Не вдалося зафіксувати транзакцію");
    }
    PQclear(res);
}

template<typename Connection>
double HostelStayRepository<Connection>::calculate_fisher(
    const std::optional<std::string>& date_from,
    const std::optional<std::string>& date_to
)
{
    auto* conn = reinterpret_cast<PGconn*>(connection_.get());

    const char* params[2] =
    {
        date_from ? date_from->c_str() : nullptr,
        date_to ? date_to->c_str() : nullptr
    };

    PGresult* res = PQexecPrepared(
        conn,
        "calculate_fisher_stmt",
        2,
        params,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) != 1 || PQgetisnull(res, 0, 0))
    {
        PQclear(res);
        throw std::runtime_error("Функція calculate_fisher повернула неочікуваний результат");
    }

    const double result = std::stod(PQgetvalue(res, 0, 0));
    PQclear(res);

    return result;
}

template<typename Connection>
std::vector<GroupStats> HostelStayRepository<Connection>::get_group_stats(
    const std::optional<std::string>& date_from,
    const std::optional<std::string>& date_to
)
{
    auto* conn = reinterpret_cast<PGconn*>(connection_.get());

    const char* params[2] =
    {
        date_from ? date_from->c_str() : nullptr,
        date_to ? date_to->c_str() : nullptr
    };

    PGresult* res = PQexecPrepared(
        conn,
        "stats_by_group_stmt",
        2,
        params,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        throw std::runtime_error("Помилка виконання stats_by_group");
    }

    std::vector<GroupStats> result;

    for (int i = 0; i < PQntuples(res); ++i)
    {
        GroupStats row;

        row.group_id = std::stoi(PQgetvalue(res, i, 0));
        row.group_size = std::stoll(PQgetvalue(res, i, 1));
        row.group_mean = std::stod(PQgetvalue(res, i, 2));
        row.within_group_variance = std::stod(PQgetvalue(res, i, 3));
        row.min_value = std::stod(PQgetvalue(res, i, 4));
        row.max_value = std::stod(PQgetvalue(res, i, 5));
        row.median = std::stod(PQgetvalue(res, i, 6));
        row.p25 = std::stod(PQgetvalue(res, i, 7));
        row.p75 = std::stod(PQgetvalue(res, i, 8));

        result.push_back(row);
    }

    PQclear(res);
    return result;
}
