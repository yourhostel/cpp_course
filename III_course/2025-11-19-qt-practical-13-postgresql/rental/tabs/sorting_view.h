//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/sorting_view.h
#ifndef CPP_COURSE_SORTING_VIEW_H
#define CPP_COURSE_SORTING_VIEW_H

#include <QObject>
#include <QStandardItemModel>

#include "sql_helper.h"
#include "table_specs.h"

class Ui_Rental;

class SortingView final : public QObject
{
    Q_OBJECT

public:
    SortingView(Ui_Rental* ui,
                QStandardItemModel* tapesModel,
                QStandardItemModel* rentalsModel,
                const SortingSpec& tapeSortSpec,
                const SortingSpec& rentalSortSpec,
                QObject* parent = nullptr);

private:
    Ui_Rental* ui;
    QStandardItemModel* tapesModel;
    QStandardItemModel* rentalsModel;

    SortingSpec tapeSortSpec;
    SortingSpec rentalSortSpec;
    static void applySortRole(QStandardItemModel* model,
                              const SortingSpec& spec,
                              int col);

    void fillTapesCombo() const;
    void fillRentalsCombo() const;

private slots:
    void onSortTapes();
    void onSortRentals();

public slots:
    void reloadView() const;

signals:
     void requestReloadAllTables();
};

#endif //CPP_COURSE_SORTING_VIEW_H