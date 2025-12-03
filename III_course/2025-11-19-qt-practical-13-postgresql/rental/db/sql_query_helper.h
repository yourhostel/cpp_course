//
// Created by tysser on 03.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/db/sql_query_helper.h
#ifndef CPP_COURSE_SQL_QUERY_HELPER_H
#define CPP_COURSE_SQL_QUERY_HELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>

class SqlQueryHelper final : public QObject
{
    Q_OBJECT

public:
    explicit SqlQueryHelper(QSqlDatabase db, QObject* parent = nullptr);

    [[nodiscard]] QString sql1() const;
    [[nodiscard]] QString sql2() const;
    [[nodiscard]] QString sql3() const;
    [[nodiscard]] QString sql4() const;
    [[nodiscard]] QString sql5() const;
    [[nodiscard]] QString sql6() const;
    [[nodiscard]] QString sql7() const;
    [[nodiscard]] QString sql8() const;
    [[nodiscard]] QString sql9() const;
    [[nodiscard]] QString sql10() const;

    bool execute(const QString& sql,
                 QStandardItemModel* outModel,
                 QString& outError) const;

    bool execAction(const QString& sql,
        QString& outError) const;

private:
    QSqlDatabase db;
};

#endif //CPP_COURSE_SQL_QUERY_HELPER_H