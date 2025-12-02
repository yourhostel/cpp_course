//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/calculated_fields_view.h
#ifndef CPP_COURSE_CALCULATED_FIELDS_VIEW_H
#define CPP_COURSE_CALCULATED_FIELDS_VIEW_H

#include <QStandardItemModel>
#include "rental.h"
#include "../ui_rental.h"
class ViewTables;

class CalculatedFieldsView final : public QObject
{
    Q_OBJECT

public:
    CalculatedFieldsView(Ui::Rental* ui,
                         QStandardItemModel* tapesModel,
                         QStandardItemModel* rentalsModel,
                         ViewTables* viewTables,
                         QObject* parent = nullptr);
    void initModels();

private:
    Ui::Rental* ui;

    QStandardItemModel* tapesModel;
    QStandardItemModel* rentalsModel;
    ViewTables* viewTables;

    QStandardItemModel* tapesCalcModel = nullptr;
    QStandardItemModel* rentalsCalcModel = nullptr;

    void refresh() const;
    void fillTapes() const;
    void fillRentals() const;
};

#endif //CPP_COURSE_CALCULATED_FIELDS_VIEW_H