//
// Created by tysser on 03.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/sql_query.cpp
#include "sql_query.h"

#include <QMessageBox>
#include <QSqlError>

#include "sql_query_helper.h"
#include "../ui_rental.h"

SqlQuery::SqlQuery(Ui_Rental* ui, SqlQueryHelper* helper, QObject* parent)
    : QObject(parent),
      ui(ui),
      helper(helper)
{
    resultModel = new QStandardItemModel(this);

    ui->sqlResultTable->setModel(resultModel);

    //Прив'язуємо 10 кнопок
    connect(ui->sqlBtn1,  &QPushButton::clicked, this, [this](){ onQueryButton(1); });
    connect(ui->sqlBtn2,  &QPushButton::clicked, this, [this](){ onQueryButton(2); });
    connect(ui->sqlBtn3,  &QPushButton::clicked, this, [this](){ onQueryButton(3); });
    connect(ui->sqlBtn4,  &QPushButton::clicked, this, [this](){ onQueryButton(4); });
    connect(ui->sqlBtn5,  &QPushButton::clicked, this, [this](){ onQueryButton(5); });
    connect(ui->sqlBtn6,  &QPushButton::clicked, this, [this](){ onQueryButton(6); });
    connect(ui->sqlBtn7,  &QPushButton::clicked, this, [this](){ onQueryButton(7); });
    connect(ui->sqlBtn8,  &QPushButton::clicked, this, [this](){ onQueryButton(8); });
    connect(ui->sqlBtn9,  &QPushButton::clicked, this, [this](){ onQueryButton(9); });
    connect(ui->sqlBtn10, &QPushButton::clicked, this, [this](){ onQueryButton(10); });

    connect(ui->sqlRunButton,         &QPushButton::clicked, this, &SqlQuery::onRun);
    connect(ui->sqlClearSqlButton,    &QPushButton::clicked, this, &SqlQuery::onClearSql);
    connect(ui->sqlClearTableButton,  &QPushButton::clicked, this, &SqlQuery::onClearTable);

    connect(ui->sqlNavFirstButton, &QToolButton::clicked, this, &SqlQuery::onNavFirst);
    connect(ui->sqlNavPrevButton,  &QToolButton::clicked, this, &SqlQuery::onNavPrev);
    connect(ui->sqlNavNextButton,  &QToolButton::clicked, this, &SqlQuery::onNavNext);
    connect(ui->sqlNavLastButton,  &QToolButton::clicked, this, &SqlQuery::onNavLast);
}

void SqlQuery::onQueryButton(int index)
{
    onClearSql();

    QString sql;
    switch (index)
    {
        case 1: sql = helper->sql1(); break;
        case 2: sql = helper->sql2(); break;
        case 3: sql = helper->sql3(); break;
        case 4: sql = helper->sql4(); break;
        case 5: sql = helper->sql5(); break;
        case 6: sql = helper->sql6(); break;
        case 7: sql = helper->sql7(); break;
        case 8: sql = helper->sql8(); break;
        case 9: sql = helper->sql9(); break;
        case 10: sql = helper->sql10(); break;
    }

    ui->sqlEditorInput->setPlainText(sql.trimmed());
}

void SqlQuery::onRun()
{
    QString sql = ui->sqlEditorInput->toPlainText().trimmed();
    if (sql.isEmpty()) return;

    if (isSelectQuery(sql))
    {
        runSelectQuery(sql);
    }
    else
    {
        runActionQuery(sql);
    }
}

void SqlQuery::showError(const QString& text)
{
    QMessageBox::critical(ui->sqlEditorInput, "SQL помилка", text);
}

void SqlQuery::updateTable()
{
    ui->sqlResultTable->setModel(resultModel);
}

void SqlQuery::onClearSql()
{
    ui->sqlEditorInput->clear();
}

void SqlQuery::onClearTable()
{
    resultModel->clear();
}

void SqlQuery::onNavFirst()
{
    ui->sqlResultTable->selectRow(0);
}

void SqlQuery::onNavPrev()
{
    int row = ui->sqlResultTable->currentIndex().row();
    if (row > 0)
        ui->sqlResultTable->selectRow(row - 1);
}

void SqlQuery::onNavNext()
{
    int row = ui->sqlResultTable->currentIndex().row();
    if (row + 1 < resultModel->rowCount())
        ui->sqlResultTable->selectRow(row + 1);
}

void SqlQuery::onNavLast()
{
    if (resultModel->rowCount() > 0)
        ui->sqlResultTable->selectRow(resultModel->rowCount() - 1);
}

// Визначення SELECT запиту
bool SqlQuery::isSelectQuery(const QString& sql) const
{
    QString s = sql.trimmed().toUpper();
    return s.startsWith("SELECT");
}

// Функція для SELECT
void SqlQuery::runSelectQuery(const QString& sql)
{
    QString err;

    if (!helper->execute(sql, resultModel, err))
    {
        showError(err);
        return;
    }

    updateTable();
}

void SqlQuery::runActionQuery(const QString& sql)
{
    QString err;

    if (!helper->execAction(sql, err))
    {
        showError(err);
        return;
    }

    // Якщо успішно, очищаємо все
    onClearTable();
    onClearSql();

    QMessageBox::information(
        nullptr,
        "SQL запит",
        "Операція успішно виконана."
    );
}