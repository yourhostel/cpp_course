// HostelStayRepository.tpp
#pragma once

#include <libpq-fe.h>
#include <stdexcept>
#include <string>

template<typename Connection>
HostelStayRepository<Connection>::HostelStayRepository(const std::string& connectionString)
    : connection_(connectionString)
{
}

template<typename Connection>
void HostelStayRepository<Connection>::saveAll(const std::vector<HostelStay>& stays)
{
    PGconn* conn = reinterpret_cast<PGconn*>(connection_.get());

    PGresult* res = PQexec(conn, "begin");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("begin failed");
    }
    PQclear(res);

    res = PQprepare(
        conn,
        "insert_hostel_stay",
        R"sql(
            insert into hostel_stays
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
            values
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
        throw std::runtime_error("prepare failed");
    }
    PQclear(res);

    for (const HostelStay& s : stays)
    {
        const std::string prise = std::to_string(s.prise);
        const std::string tariff = std::to_string(s.tariffTerm);
        const std::string days = std::to_string(s.stayDays);
        const std::string total = std::to_string(s.totalPrice);
        const std::string revenue = std::to_string(s.revenuePerDay);

        const char* params[13] =
        {
            s.hostel.c_str(),
            s.room.c_str(),
            s.lastName.c_str(),
            s.fullName.c_str(),
            s.sourceFileDate.c_str(),
            s.checkinDate.c_str(),
            s.checkoutDate.c_str(),
            prise.c_str(),
            tariff.c_str(),
            days.c_str(),
            total.c_str(),
            revenue.c_str(),
            s.source.c_str()
        };

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
            PQexec(conn, "rollback");
            throw std::runtime_error("insert failed");
        }

        PQclear(res);
    }

    res = PQexec(conn, "commit");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        throw std::runtime_error("commit failed");
    }
    PQclear(res);
}
