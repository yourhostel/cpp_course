// DatabaseConnection.tpp
#pragma once

#include <libpq-fe.h>
#include <stdexcept>

template<typename NativeConnection>
DatabaseConnection<NativeConnection>::DatabaseConnection(const std::string& connectionString)
    : connection_(reinterpret_cast<NativeConnection*>(PQconnectdb(connectionString.c_str())))
{
    if (PQstatus(reinterpret_cast<PGconn*>(connection_)) != CONNECTION_OK)
    {
        throw std::runtime_error(PQerrorMessage(reinterpret_cast<PGconn*>(connection_)));
    }
}

template<typename NativeConnection>
DatabaseConnection<NativeConnection>::~DatabaseConnection()
{
    if (connection_ != nullptr)
    {
        PQfinish(reinterpret_cast<PGconn*>(connection_));
    }
}

template<typename NativeConnection>
NativeConnection* DatabaseConnection<NativeConnection>::get() const
{
    return connection_;
}