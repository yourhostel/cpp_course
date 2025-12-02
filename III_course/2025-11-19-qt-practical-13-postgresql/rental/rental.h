//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/rental.h
#ifndef CPP_COURSE_RENTAL_H
#define CPP_COURSE_RENTAL_H

#include <QMainWindow>
#include "db/sql_helper.h"
#include "delegates/combo_delegate.h"

class ViewTables;
class RecordsView;
class VisualComponents;
class RelationsView;

QT_BEGIN_NAMESPACE
namespace Ui { class Rental; }
QT_END_NAMESPACE

class Rental final : public QMainWindow
{
    Q_OBJECT

public:
    explicit Rental(QWidget *parent = nullptr);
    ~Rental() override;

private:
    Ui::Rental *ui = nullptr;

    TableSpec tapeSpec;
    TableSpec customerSpec;
    TableSpec rentalSpec;

    // Таби
    VisualComponents* visualComponents = nullptr;
    ViewTables* viewTables = nullptr;
    RecordsView* recordsView = nullptr;
    RelationsView* relationsView = nullptr;

    QSqlDatabase db;

    QStandardItemModel* tapesModel = nullptr;
    QStandardItemModel* customersModel = nullptr;
    QStandardItemModel* rentalsModel = nullptr;

    ComboDelegate* tapeDelegate = nullptr;
    ComboDelegate* customerDelegate = nullptr;

    SqlHelper* helper = nullptr;

    bool connectDatabase();

private slots:

};

#endif //CPP_COURSE_RENTAL_H