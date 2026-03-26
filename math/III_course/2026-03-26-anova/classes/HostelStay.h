// HostelStay.h
#pragma once

#include <string>

struct HostelStay
{
    std::string hostel;
    std::string room;
    std::string lastName;
    std::string fullName;
    std::string sourceFileDate;
    std::string checkinDate;
    std::string checkoutDate;
    int prise {};
    int tariffTerm {};
    int stayDays {};
    double totalPrice {};
    double revenuePerDay {};
    std::string source;
};