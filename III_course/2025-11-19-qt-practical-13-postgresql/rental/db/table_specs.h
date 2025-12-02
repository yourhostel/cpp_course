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

enum class SortFieldType {
    Integer,
    Real,
    Boolean,
    Date,
    Text
};

struct SortColumn {
    QString name;         // текст у таблиці
    SortFieldType type;   // тип для сорту
};

struct SortingSpec {
    QVector<SortColumn> columns;
};

static const SortingSpec TapeSorting = {
    {
        {"Код",         SortFieldType::Integer},
        {"Назва",       SortFieldType::Text},
        {"Тип",         SortFieldType::Text},
        {"Ціна/день",   SortFieldType::Real},
        {"Опис",        SortFieldType::Text}
    }
};

static const SortingSpec RentalSorting = {
    {
        {"Код",          SortFieldType::Integer},
        {"Касета",       SortFieldType::Integer},
        {"Дата видачі",  SortFieldType::Date},
        {"Дата прийому", SortFieldType::Date},
        {"Клієнт",       SortFieldType::Integer},
        {"К-сть копій",  SortFieldType::Integer},
        {"Термін",       SortFieldType::Date},
        {"Повернено",    SortFieldType::Boolean}
    }
};

#endif //CPP_COURSE_TABLE_SPECS_H
