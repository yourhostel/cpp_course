//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/calculated_fields_view.cpp
#include "calculated_fields_view.h"

#include "view_tables.h"
#include "../ui_rental.h"

CalculatedFieldsView::CalculatedFieldsView(Ui::Rental* uiPtr,
                                           QStandardItemModel* tapesModel,
                                           QStandardItemModel* rentalsModel,
                                           ViewTables* viewTables,
                                           QObject* parent)
    : QObject(parent),
      ui(uiPtr),
      tapesModel(tapesModel),
      rentalsModel(rentalsModel),
      viewTables(viewTables)
{
    initModels();

    ui->cfTapesTable->setModel(tapesCalcModel);
    ui->cfRentalsTable->setModel(rentalsCalcModel);

     connect(tapesModel,
         &QStandardItemModel::itemChanged,
         this,
         &CalculatedFieldsView::refresh);

     connect(rentalsModel,
         &QStandardItemModel::itemChanged,
         this,
         &CalculatedFieldsView::refresh);

     connect(viewTables,
         &ViewTables::dataReloaded,
         this,
         &CalculatedFieldsView::refresh);

    refresh();
}

void CalculatedFieldsView::initModels()
{
    tapesCalcModel = new QStandardItemModel(this);
    tapesCalcModel->setHorizontalHeaderLabels(
        {"ID","Назва","Тип","Ціна","Опис","Прайс-лист"}
    );

    rentalsCalcModel = new QStandardItemModel(this);
    rentalsCalcModel->setHorizontalHeaderLabels(
        {"ID","Касета","Дата видачі","Дата прийому",
         "Клієнт","Копії","Термін","Повернено","Сума"}
    );
}

void CalculatedFieldsView::refresh() const
{

    tapesCalcModel->removeRows(0, tapesCalcModel->rowCount());
    rentalsCalcModel->removeRows(0, rentalsCalcModel->rowCount());

    fillTapes();
    fillRentals();
}

void CalculatedFieldsView::fillTapes() const
{
    for (int r = 0; r < tapesModel->rowCount(); r++)
    {
        const auto *idItem = tapesModel->item(r, 0);

        // захист от порожніх рядків
        if (!idItem) continue;

        QString id    = idItem->text();

        const auto *titleItem = tapesModel->item(r, 1);
        const auto *typeItem  = tapesModel->item(r, 2);
        const auto *priceItem = tapesModel->item(r, 3);
        const auto *descItem  = tapesModel->item(r, 4);

        if (!titleItem || !typeItem || !priceItem || !descItem)
            continue; // рядок ще не повністю створений

        QString title = titleItem->text();
        QString type  = typeItem->text();
        QString price = priceItem->text();
        QString desc  = descItem->text();

        QString priceList = title + " - " + price + " грн.";

        QList row {
            new QStandardItem(id),
            new QStandardItem(title),
            new QStandardItem(type),
            new QStandardItem(price),
            new QStandardItem(desc),
            new QStandardItem(priceList)
        };

        tapesCalcModel->appendRow(row);
    }
}

void CalculatedFieldsView::fillRentals() const
{
    for (int r = 0; r < rentalsModel->rowCount(); r++)
    {
        const auto *idItem = rentalsModel->item(r, 0);
        const auto *tapeIdItem = rentalsModel->item(r, 1);
        const auto *copiesItem = rentalsModel->item(r, 5);

        if (!idItem || !tapeIdItem || !copiesItem)
            continue; // рядок ще не готов

        QString id = idItem->text();
        const int tapeId = tapeIdItem->text().toInt();
        const int copies = copiesItem->text().toInt();

        const auto *issueItem = rentalsModel->item(r, 2);
        const auto *retItem   = rentalsModel->item(r, 3);
        const auto *custItem  = rentalsModel->item(r, 4);
        const auto *deadItem  = rentalsModel->item(r, 6);
        const auto *retuItem  = rentalsModel->item(r, 7);

        if (!issueItem || !retItem || !custItem || !deadItem || !retuItem)
            continue;

        QString issue    = issueItem->text();
        QString ret      = retItem->text();
        QString customer = custItem->text();
        QString deadline = deadItem->text();
        QString returned = retuItem->text();

        double price = 0.0;
        for (int tr = 0; tr < tapesModel->rowCount(); tr++)
        {
            const auto *idT = tapesModel->item(tr, 0);
            const auto *prT = tapesModel->item(tr, 3);
            if (!idT || !prT) continue;

            if (idT->text().toInt() == tapeId)
            {
                price = prT->text().toDouble();
                break;
            }
        }

        const double sum = price * copies;

        QList row {
            new QStandardItem(id),
            new QStandardItem(QString::number(tapeId)),
            new QStandardItem(issue),
            new QStandardItem(ret),
            new QStandardItem(customer),
            new QStandardItem(QString::number(copies)),
            new QStandardItem(deadline),
            new QStandardItem(returned),
            new QStandardItem(QString::number(sum))
        };

        rentalsCalcModel->appendRow(row);
    }
}

