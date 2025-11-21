//
// Created by tysser on 21.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/db/sql_helper.h
#ifndef CPP_COURSE_SQL_HELPER_H
#define CPP_COURSE_SQL_HELPER_H

#include <QSqlDatabase>
#include <QStandardItemModel>

struct TableSpec
{
    QString tableName;                 // "tapes"
    QString idColumn;                  // "tape_id"
    QVector<QString> columns;          // {"title","type","price","description"}
};

class SqlHelper final : public QObject
{
protected:
    ~SqlHelper() override = default;

    Q_OBJECT

public:
    explicit SqlHelper(QSqlDatabase& db, QObject* parent = nullptr)
    : QObject(parent),
      db_(db)
    {}

    bool loadModel(QStandardItemModel* model, const TableSpec& spec, QString& error) const;
    bool saveModel(QStandardItemModel* model, const TableSpec& spec, QString& error) const;
    bool deleteRow(const TableSpec& spec, int id, QString& error) const;

private:
    QSqlDatabase& db_;
};


#endif //CPP_COURSE_SQL_HELPER_H