//
// Created by tysser on 03.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/db/sql_query_helper.cpp
#include "sql_query_helper.h"
#include <QSqlError>
#include <QSqlRecord>

SqlQueryHelper::SqlQueryHelper(QSqlDatabase db, QObject* parent)
    : QObject(parent), db(db)
{
}

QString SqlQueryHelper::sql1() const {
    return R"(
SELECT * FROM tapes;
)";
}

QString SqlQueryHelper::sql2() const {
    return R"(
SELECT * FROM rentals
WHERE tape_id = 3;
)";
}

QString SqlQueryHelper::sql3() const {
    return R"(
SELECT * FROM customers
WHERE full_name ILIKE '%ів%';
)";
}

QString SqlQueryHelper::sql4() const {
    return R"(
SELECT r.rental_id,
       c.full_name,
       t.title,
       r.copies,
       t.price,
       r.copies * t.price AS total
FROM rentals r
JOIN customers c ON r.customer_id = c.customer_id
JOIN tapes t ON r.tape_id = t.tape_id
ORDER BY total DESC;
)";
}

QString SqlQueryHelper::sql5() const {
    return R"(
SELECT tape_id, COUNT(*) AS total_rentals
FROM rentals
GROUP BY tape_id
ORDER BY total_rentals DESC;
)";
}

QString SqlQueryHelper::sql6() const {
    return R"(
SELECT c.full_name,
       SUM(r.copies) AS total_copies
FROM rentals r
JOIN customers c ON r.customer_id = c.customer_id
GROUP BY c.full_name
ORDER BY total_copies DESC;
)";
}

QString SqlQueryHelper::sql7() const {
    return R"(
SELECT *
FROM rentals
WHERE issue_date BETWEEN '2025-01-01' AND '2025-12-31';
)";
}

QString SqlQueryHelper::sql8() const {
    return R"(
SELECT *
FROM tapes
WHERE (price > 10 AND type = 'Фільм')
   OR (price <= 10 AND type = 'Мультфільм');
)";
}

QString SqlQueryHelper::sql9() const {
    return R"(
SELECT
    MIN(price) AS min_price,
    MAX(price) AS max_price,
    AVG(price) AS avg_price
FROM tapes;
)";
}

QString SqlQueryHelper::sql10() const {
    return R"(
SELECT
    c.full_name,
    COUNT(*) AS rentals_count
FROM rentals r
JOIN customers c ON r.customer_id = c.customer_id
GROUP BY c.full_name
ORDER BY rentals_count DESC;
)";
}

bool SqlQueryHelper::execute(const QString& sql,
                             QStandardItemModel* outModel,
                             QString& outError) const
{
    outModel->clear();
    outError.clear();

    QSqlQuery q(db);

    if (!q.exec(sql))
    {
        outError = q.lastError().text();
        return false;
    }

    // Формуємо заголовки
    for (int i = 0; i < q.record().count(); i++)
        outModel->setHorizontalHeaderItem(
            i, new QStandardItem(q.record().fieldName(i))
        );

    // Дані
    while (q.next())
    {
        QList<QStandardItem*> row;
        for (int c = 0; c < q.record().count(); c++)
            row.append(new QStandardItem(q.value(c).toString()));

        outModel->appendRow(row);
    }

    return true;
}

bool SqlQueryHelper::execAction(const QString& sql, QString& outError) const
{
    QSqlQuery q(db);

    if (!q.exec(sql))
    {
        outError = q.lastError().text();
        return false;
    }

    return true;
}