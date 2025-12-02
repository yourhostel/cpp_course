//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/filtering_view.cpp
#include "debug_log.h"
#include "../ui_rental.h"

#include "filtering_view.h"
#include "../ui_rental.h"

FilteringView::FilteringView(Ui_Rental* uiPtr,
                             QStandardItemModel* tapes,
                             QStandardItemModel* rentals,
                             QObject* parent)
    : QObject(parent),
      ui(uiPtr),
      tapesModel(tapes),
      rentalsModel(rentals)
{
    // Касети. Проксі для текстового фільтра
    tapesProxy = new QSortFilterProxyModel(this);
    tapesProxy->setSourceModel(tapesModel);
    tapesProxy->setFilterKeyColumn(1); // title
    tapesProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->filterTapesTable->setModel(tapesProxy);

    // Прокати. Проксі з кастомним фільтром по даті
    rentalsProxy = new DateFilterProxyModel(this);
    rentalsProxy->setSourceModel(rentalsModel);
    ui->filterRentalsTable->setModel(rentalsProxy);

    // Сігнали фільтра назви
    connect(ui->filterTitleEdit, &QLineEdit::textChanged,
            this, &FilteringView::onTitleChanged);

    connect(ui->filterTitleCheckBox, &QCheckBox::toggled,
            this, &FilteringView::onTitleCheckChanged);

    // Сігнали фільтра дат
    connect(ui->filterDateCheckBox, &QCheckBox::toggled,
            this, &FilteringView::onDateCheckChanged);

    connect(ui->filterDateFromEdit, &QDateEdit::dateChanged,
            this, &FilteringView::onDateFromChanged);

    connect(ui->filterDateToEdit, &QDateEdit::dateChanged,
            this, &FilteringView::onDateToChanged);
}

// Оновлення фільтра по назві
void FilteringView::onTitleChanged(const QString& text) const
{
    if (!ui->filterTitleCheckBox->isChecked())
    {
        tapesProxy->setFilterRegularExpression(QString());
        return;
    }

    tapesProxy->setFilterRegularExpression("^" + text + ".*");
}

// Викликається при зміні стану чекбоксу фільтра назви
void FilteringView::onTitleCheckChanged(bool on) const
{
    onTitleChanged(ui->filterTitleEdit->text());
}

// Увімкнення або вимкнення фільтра дат
void FilteringView::onDateCheckChanged(const bool on) const
{
    rentalsProxy->setEnabled(on);
}

// Оновлення фільтра при зміні дати "з"
void FilteringView::onDateFromChanged(const QDate& d) const
{
    rentalsProxy->setDateRange(d, ui->filterDateToEdit->date());
}

// Оновлення фільтра при зміні дати "по"
void FilteringView::onDateToChanged(const QDate& d) const
{
    rentalsProxy->setDateRange(ui->filterDateFromEdit->date(), d);
}

// Оновлення обох проксі після перезавантаження таблиць
void FilteringView::reloadView() const
{
    tapesProxy->invalidate();
    rentalsProxy->invalidate();
}

