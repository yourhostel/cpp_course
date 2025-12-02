//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/relations_view.h
#ifndef CPP_COURSE_RELATIONS_VIEW_H
#define CPP_COURSE_RELATIONS_VIEW_H

#include "sql_helper.h"
#include <QStandardItemModel>

class Ui_Rental;
class SqlHelper;

enum class RelationMode
{
    None,
    ByTape,
    ByCustomer
};

class RelationsView final : public QObject
{
    Q_OBJECT

public:
    RelationsView(Ui_Rental* ui,
                  QStandardItemModel* tapesModel,
                  QStandardItemModel* customersModel,
                  QStandardItemModel* rentalsModel,
                  QObject* parent = nullptr);

private:
    Ui_Rental* ui;

    TableSpec rentalSpec;

    QStandardItemModel* tapesModel;
    QStandardItemModel* customersModel;
    QStandardItemModel* rentalsModel;

    RelationMode mode = RelationMode::None;

private slots:
    void onTapeSelected();
    void onCustomerSelected();

    void onLinkByTape();
    void onLinkByCustomer();
    void onClearLinks();

private:
    void applyFilter();
    void showAllRentals() const;
};

#endif //CPP_COURSE_RELATIONS_VIEW_H