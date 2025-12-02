//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/view_tables.h
#ifndef CPP_COURSE_VIEW_TABLES_H
#define CPP_COURSE_VIEW_TABLES_H

#include "rental.h"
#include "sql_helper.h"
#include "../ui_rental.h"
#include "../delegates/combo_delegate.h"

class ViewTables final : public QObject
{
    Q_OBJECT

    // Специ таблиць
    TableSpec tapeSpec;
    TableSpec customerSpec;
    TableSpec rentalSpec;

public:
    explicit ViewTables(Ui::Rental* ui,
                        QStandardItemModel* tapes_model,
                        QStandardItemModel* customers_model,
                        QStandardItemModel* rentals_model,
                        SqlHelper* helper,
                        QObject* parent = nullptr);

private:
    Ui::Rental* ui;
    SqlHelper* helper;

    // Моделі отримані з Rental
    QStandardItemModel* tapesModel;
    QStandardItemModel* customersModel;
    QStandardItemModel* rentalsModel;

    // Делегати
    ComboDelegate* tapeDelegate{};
    ComboDelegate* customerDelegate{};

private:
    // Налаштування таблиць
    void setupTapesTable();
    void setupCustomersTable();
    void setupRentalsTable();

    // Загальні завантаження
    void loadTapes() const;
    void loadCustomers() const;
    void loadRentals() const;
    void loadAllTables() const;

    // Додавання (CRUD)
    void addEmptyRow(QStandardItemModel* model) const;
    void onAddTapeClicked() const;
    void onAddCustomerClicked() const;
    void onAddRentalClicked() const;

    // Збереження
    void onSaveTapesClicked() const;
    void onSaveCustomersClicked() const;
    void onSaveRentalsClicked() const;

    // Видалення
    void deleteSelectedRow(const QTableView* table,
                           QStandardItemModel* model,
                           const TableSpec& spec) const;

    // Події вибору рядків
    void onTapeRowChanged(const QModelIndex& current,
                          const QModelIndex& previous) const;
    void onCustomerRowChanged(const QModelIndex& current,
                              const QModelIndex& previous) const;

    // Допоміжні
    void refreshComboDelegates() const;
    int getFirstId(const QStandardItemModel* model) const;
    QList<int> getIds(const QStandardItemModel* model) const;
    QStringList getTexts(const QStandardItemModel* model) const;
    QStringList getCustomerNames() const;
    void showSaveSuccess(const QString& tableName) const;

    //ViewTables(Ui_Rental* ui, SqlHelper* helper, QObject* parent);
};



#endif //CPP_COURSE_VIEW_TABLES_H