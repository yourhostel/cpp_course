//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/rental.h
#ifndef CPP_COURSE_RENTAL_H
#define CPP_COURSE_RENTAL_H

#include <QMainWindow>
#include <qtableview.h>

#include "db/sql_helper.h"
#include "delegates/combo_delegate.h"
#include "tabs/visual_components.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Rental; }
QT_END_NAMESPACE

class Rental final : public QMainWindow
{
    Q_OBJECT

    TableSpec tapeSpec;
    TableSpec customerSpec;
    TableSpec rentalSpec;

public:
    explicit Rental(QWidget *parent = nullptr);
    ~Rental() override;

private:
    Ui::Rental *ui = nullptr;
    VisualComponents* visualComponents = nullptr;

    QSqlDatabase db;

    QStandardItemModel* tapesModel = nullptr;
    QStandardItemModel* customersModel = nullptr;
    QStandardItemModel* rentalsModel = nullptr;

    ComboDelegate* tapeDelegate = nullptr;
    ComboDelegate* customerDelegate = nullptr;

    SqlHelper* helper = nullptr;

    void setupTapesTable();
    void setupCustomersTable();
    void setupRentalsTable();
    static QList<int> getIds(const QStandardItemModel* model);
    static QStringList getTexts(const QStandardItemModel* model);
    static int getFirstId(const QStandardItemModel* model) ;
    [[nodiscard]] QStringList getCustomerNames() const;
    void refreshComboDelegates() const;
    void showSaveSuccess(const QString& tableName);
    void addEmptyRow(QStandardItemModel* model) const;

    void loadAllTables();
    void loadTapes();
    void loadCustomers();
    void loadRentals();

    bool connectDatabase();

private slots:
    void onAddTapeClicked() const;
    void onAddCustomerClicked() const;
    void onAddRentalClicked() const;
    void deleteSelectedRow(const QTableView* table, QStandardItemModel* model, const TableSpec& spec);

    void onSaveTapesClicked();
    void onSaveCustomersClicked();
    void onSaveRentalsClicked();

    void onTapeRowChanged(const QModelIndex &current, const QModelIndex &previous) const;
    void onCustomerRowChanged(const QModelIndex &current, const QModelIndex &previous) const;
};

#endif //CPP_COURSE_RENTAL_H