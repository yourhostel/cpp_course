//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/sorting_view.cpp
#include "sorting_view.h"

#include <qdatetime.h>

#include "debug_log.h"
#include "../ui_rental.h"

SortingView::SortingView(Ui_Rental* ui,
                         QStandardItemModel* tapesModel,
                         QStandardItemModel* rentalsModel,
                         const SortingSpec& tapeSortSpec,
                         const SortingSpec& rentalSortSpec,
                         QObject* parent)
    : QObject(parent),
      ui(ui),
      tapesModel(tapesModel),
      rentalsModel(rentalsModel),
      tapeSortSpec(tapeSortSpec),
      rentalSortSpec(rentalSortSpec)
{
    ui->sortTapesTable->setModel(tapesModel);
    ui->sortRentalsTable->setModel(rentalsModel);

    fillTapesCombo();
    fillRentalsCombo();

    ui->sortTapesCombo->setCurrentIndex(0);
    ui->sortRentalsCombo->setCurrentIndex(0);

    connect(ui->sortTapesButton,   &QPushButton::clicked, this, &SortingView::onSortTapes);
    connect(ui->sortRentalsButton, &QPushButton::clicked, this, &SortingView::onSortRentals);
}

// Наповнення комбобоксів назвами стовпців
void SortingView::fillTapesCombo() const
{
    ui->sortTapesCombo->clear();
    ui->sortTapesCombo->addItem(QString());

    for (int c = 0; c < tapesModel->columnCount(); c++)
        ui->sortTapesCombo->addItem(tapesModel->headerData(c, Qt::Horizontal).toString());

    DLOG("TAPES COMBO FILLED. COUNT =", ui->sortTapesCombo->count());
}

void SortingView::fillRentalsCombo() const
{
    ui->sortRentalsCombo->clear();
    ui->sortRentalsCombo->addItem(QString());

    for (int c = 0; c < rentalsModel->columnCount(); c++)
        ui->sortRentalsCombo->addItem(rentalsModel->headerData(c, Qt::Horizontal).toString());

    DLOG("RENTALS COMBO FILLED. COUNT =", ui->sortRentalsCombo->count());
}

// Сортування касет
void SortingView::onSortTapes()
{
    const QString text = ui->sortTapesCombo->currentText().trimmed();
    DLOG("Sort Tapes text =", text);

    if (text.isEmpty()) {
        DLOG("RESET TAPES SORT");
        emit requestReloadAllTables();
        return;
    }

    const int col = ui->sortTapesCombo->currentIndex() - 1;

    applySortRole(tapesModel, tapeSortSpec, col);
    tapesModel->sort(col, Qt::AscendingOrder);
}

// Сортування прокату
void SortingView::onSortRentals()
{
    const QString text = ui->sortRentalsCombo->currentText().trimmed();
    DLOG("Sort Rentals text =", text);

    if (text.isEmpty()) {
        DLOG("RESET RENTALS SORT");
        emit requestReloadAllTables();
        return;
    }

    const int col = ui->sortRentalsCombo->currentIndex() - 1;

    applySortRole(rentalsModel, rentalSortSpec, col);
    rentalsModel->sort(col, Qt::AscendingOrder);
}

void SortingView::reloadView() const
{
    ui->sortTapesTable->setModel(tapesModel);
    ui->sortRentalsTable->setModel(rentalsModel);
}

void SortingView::applySortRole(QStandardItemModel* model,
                                const SortingSpec& spec,
                                const int col)
{
    const auto& [name, type] = spec.columns[col];

    for (int r = 0; r < model->rowCount(); r++)
    {
        QStandardItem* item = model->item(r, col);
        if (!item) continue;

        QVariant raw = item->text();

        switch (type)
        {
        case SortFieldType::Integer:
            item->setData(raw.toInt(), Qt::UserRole);
            break;

        case SortFieldType::Real:
            item->setData(raw.toDouble(), Qt::UserRole);
            break;

        case SortFieldType::Boolean:
            item->setData(raw == "true" ? 1 : 0, Qt::UserRole);
            break;

        case SortFieldType::Date:
            item->setData(QDate::fromString(raw.toString(), "yyyy-MM-dd"), Qt::UserRole);
            break;

        default:
            item->setData(raw.toString(), Qt::UserRole);
            break;
        }
    }

    model->setSortRole(Qt::UserRole);
}
