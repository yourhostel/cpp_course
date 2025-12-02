//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/rental.cpp
#include "rental.h"
#include "ui_rental.h"
#include "view_tables.h"
#include "visual_components.h"
#include "records_view.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>

#include "debug_log.h"
#include "relations_view.h"

/**
 * Конструктор головного вікна.
 *
 * Алгоритм:
 *   1) Ініціалізувати UI.
 *   2) Підключитися до бази.
 *   3) Створити SqlHelper.
 *
 * @param parent батьківський QWidget або nullptr
 */
Rental::Rental(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Rental)
{
    // Створюємо UI
    ui->setupUi(this);

    // Підключення до БД
    if (!connectDatabase())
    {
        QMessageBox::critical(this, "Помилка", "База недоступна.");
        return;
    }

    // Створення helper
    helper = new SqlHelper(db, this);

    tapesModel = new QStandardItemModel(this);
    customersModel = new QStandardItemModel(this);
    rentalsModel = new QStandardItemModel(this);

    DLOG(QString("Before VC MODELS: tapes=%1 customers=%2 rentals=%3")
    .arg(tapesModel->rowCount())
    .arg(customersModel->rowCount())
    .arg(rentalsModel->rowCount()));

    viewTables = new ViewTables(ui, tapesModel, customersModel,
    rentalsModel, helper, this);

    visualComponents = new VisualComponents(ui, tapesModel, customersModel,
    rentalsModel, helper, this);

    recordsView = new RecordsView(ui, tapesModel, this);

    relationsView = new RelationsView(ui, tapesModel, customersModel,
    rentalsModel, this);

    calculatedFieldsView = new CalculatedFieldsView(ui, tapesModel, rentalsModel,
    viewTables,this);
}

/** ========================================================================
 * Деструктор.
 *
 * Звільняє UI та інші ресурси.
 */
Rental::~Rental()
{
    delete ui;
}

// =========================================================================
// bd
// =========================================================================

/** ========================================================================
 * Підключається до бази даних PostgreSQL.
 *
 * Алгоритм:
 *   1) Перевірити наявність драйвера "QPSQL".
 *      Якщо драйвер недоступний, повернути false.
 *   2) Створити екземпляр QSqlDatabase через addDatabase("QPSQL").
 *   3) Встановити параметри підключення.
 *   4) Викликати db.open().
 *   5) Повернути результат open(): true при успіху, false при помилці.
 *
 * Призначення:
 *   Ініціалізує з'єднання з PostgreSQL перед роботою SqlHelper та
 *   завантаженням моделей. Викликається у конструкторі Rental.
 *
 * @return true, якщо підключення успішне; false, якщо драйвер недоступний
 *         або база не відкрилася.
 */
bool Rental::connectDatabase()
{
    if (!QSqlDatabase::isDriverAvailable("QPSQL"))
        return false;

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("app-db");
    db.setUserName("serg");
    db.setPassword("1234");

    return db.open();
}
