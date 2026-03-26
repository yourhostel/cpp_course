// DatabaseConnection.h
#pragma once

#include <string>

struct PGconn;

template<typename NativeConnection = PGconn>
class DatabaseConnection
{
public:
    explicit DatabaseConnection(const std::string& connectionString);
    ~DatabaseConnection();

    NativeConnection* get() const;

private:
    NativeConnection* connection_;
};

#include "../DatabaseConnection.tpp"
