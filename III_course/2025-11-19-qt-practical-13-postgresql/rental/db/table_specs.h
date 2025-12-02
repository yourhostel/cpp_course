//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/db/table_specs.h
#ifndef CPP_COURSE_TABLE_SPECS_H
#define CPP_COURSE_TABLE_SPECS_H


// ===== Специфікації таблиць =====

static const TableSpec TapeSpec = {
    "tapes",
    "tape_id",
    {"title", "type", "price", "description"}
};

static const TableSpec CustomerSpec = {
    "customers",
    "customer_id",
    {"full_name", "info"}
};

static const TableSpec RentalSpec = {
    "rentals",
    "rental_id",
    {"tape_id", "issue_date", "return_date",
     "customer_id", "copies", "deadline", "returned"}
};

#endif //CPP_COURSE_TABLE_SPECS_H