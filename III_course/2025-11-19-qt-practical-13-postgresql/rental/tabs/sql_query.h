//
// Created by tysser on 03.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/sql_query.h
#ifndef CPP_COURSE_SQL_QUERY_H
#define CPP_COURSE_SQL_QUERY_H

#include <QObject>
#include <QStandardItemModel>

class Ui_Rental;
class SqlQueryHelper;

class SqlQuery final : public QObject
{
    Q_OBJECT

public:
    SqlQuery(Ui_Rental* ui, SqlQueryHelper* helper, QObject* parent = nullptr);

private:
    Ui_Rental* ui;
    SqlQueryHelper* helper;
    QStandardItemModel* resultModel;

private slots:
    void onQueryButton(int index);
    void onRun();
    void onClearSql();
    void onClearTable();
    void onNavFirst();
    void onNavPrev();
    void onNavNext();
    void onNavLast();

    [[nodiscard]] bool isSelectQuery(const QString& sql) const;
    void runSelectQuery(const QString& sql);
    void runActionQuery(const QString& sql);

    void showError(const QString& text);
    void updateTable();

};

#endif //CPP_COURSE_SQL_QUERY_H