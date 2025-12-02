//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/relations_view.cpp
#include "relations_view.h"
#include "table_specs.h"
#include "../ui_rental.h"

RelationsView::RelationsView(Ui_Rental* ui,
                             QStandardItemModel* tapesModel,
                             QStandardItemModel* customersModel,
                             QStandardItemModel* rentalsModel,
                             QObject* parent)
    : QObject(parent),
      ui(ui),
      tapesModel(tapesModel),
      customersModel(customersModel),
      rentalsModel(rentalsModel)
{
    rentalSpec = RentalSpec;

    ui->rvTapesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rvCustomersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rvRentalsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Підключення таблиць в UI
    ui->rvTapesTable->setModel(tapesModel);
    ui->rvCustomersTable->setModel(customersModel);
    ui->rvRentalsTable->setModel(rentalsModel);

    // Сигнали вибору рядків
    connect(ui->rvTapesTable->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &RelationsView::onTapeSelected);

    connect(ui->rvCustomersTable->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &RelationsView::onCustomerSelected);

    // Кнопки фільтрування
    connect(ui->rvTapeLinkButton, &QPushButton::clicked,
            this, &RelationsView::onLinkByTape);

    connect(ui->rvCustomerLinkButton, &QPushButton::clicked,
            this, &RelationsView::onLinkByCustomer);

    connect(ui->rvClearLinkButton, &QPushButton::clicked,
            this, &RelationsView::onClearLinks);
}

// Вибір касети
void RelationsView::onTapeSelected()
{
    if (mode != RelationMode::ByTape)
        return;

    applyFilter();
}

//  Вибір клієнта
void RelationsView::onCustomerSelected()
{
    if (mode != RelationMode::ByCustomer)
        return;

    applyFilter();
}

// Увімкнути фільтр по касетах
void RelationsView::onLinkByTape()
{
    mode = RelationMode::ByTape;

    // якщо немає вибору, вибрати рядок 0
    if (ui->rvTapesTable->selectionModel()->selectedRows().isEmpty() &&
        tapesModel->rowCount() > 0)
    {
        ui->rvTapesTable->selectRow(0);
    }

    applyFilter();
}

// Увімкнути фільтр по клієнтах
void RelationsView::onLinkByCustomer()
{
    mode = RelationMode::ByCustomer;

    if (ui->rvCustomersTable->selectionModel()->selectedRows().isEmpty() &&
    customersModel->rowCount() > 0)
    {
        ui->rvCustomersTable->selectRow(0);
    }

    applyFilter();
}

// Забрати фільтри
void RelationsView::onClearLinks()
{
    mode = RelationMode::None;
    showAllRentals();
}

// Головна логіка фільтрування
void RelationsView::applyFilter()
{
    if (mode == RelationMode::None)
    {
        showAllRentals();
        return;
    }

    int filterValue = -1;

    if (mode == RelationMode::ByTape)
    {
        auto indexes = ui->rvTapesTable->selectionModel()->selectedRows();
        if (indexes.isEmpty()) return;

        filterValue = tapesModel->item(indexes.first().row(), 0)->text().toInt();
    }
    else if (mode == RelationMode::ByCustomer)
    {
        auto indexes = ui->rvCustomersTable->selectionModel()->selectedRows();
        if (indexes.isEmpty()) return;

        filterValue = customersModel->item(indexes.first().row(), 0)->text().toInt();
    }

    if (filterValue < 0)
        return;

    auto* filtered = new QStandardItemModel(this);

    QStringList headers;
    headers << rentalSpec.idColumn;
    for (const auto& col : rentalSpec.columns)
        headers << col;

    filtered->setHorizontalHeaderLabels(headers);

    for (int r = 0; r < rentalsModel->rowCount(); r++)
    {
        const bool match =
            (mode == RelationMode::ByTape &&
             rentalsModel->item(r, 1)->text().toInt() == filterValue)
            ||
            (mode == RelationMode::ByCustomer &&
             rentalsModel->item(r, 4)->text().toInt() == filterValue);

        if (match)
        {
            QList<QStandardItem*> rowItems;
            for (int c = 0; c < rentalsModel->columnCount(); c++)
                rowItems.append(rentalsModel->item(r, c)->clone());

            filtered->appendRow(rowItems);
        }
    }

    ui->rvRentalsTable->setModel(filtered);
}

// Показати все
void RelationsView::showAllRentals() const
{
    ui->rvRentalsTable->setModel(rentalsModel);
}
