//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/search_view.cpp
#include "search_view.h"
#include "../ui_rental.h"
#include <QMessageBox>

SearchView::SearchView(Ui_Rental* ui,
                       QStandardItemModel* tapesModel,
                       QStandardItemModel* rentalsModel,
                       QStandardItemModel* customersModel,
                       QObject* parent)
    : QObject(parent),
      ui(ui),
      tapesModel(tapesModel),
      rentalsModel(rentalsModel),
      customersModel(customersModel)

{
    ui->srClientsTable->setModel(customersModel);
    ui->srRentalsTable->setModel(rentalsModel);

    fillCombo();

    connect(ui->srSbnButton, &QPushButton::clicked, this, &SearchView::onSearchByName);
    connect(ui->srStfButton, &QPushButton::clicked, this, &SearchView::onSearchTwoFields);
    connect(ui->srSluButton, &QPushButton::clicked, this, &SearchView::onSearchLookup);

    connect(ui->srClientsFirstButton, &QToolButton::clicked, this, &SearchView::onClientsFirst);
    connect(ui->srClientsPrevButton,  &QToolButton::clicked, this, &SearchView::onClientsPrev);
    connect(ui->srClientsNextButton,  &QToolButton::clicked, this, &SearchView::onClientsNext);
    connect(ui->srClientsLastButton,  &QToolButton::clicked, this, &SearchView::onClientsLast);

    connect(ui->srRentalsFirstButton, &QToolButton::clicked, this, &SearchView::onRentalsFirst);
    connect(ui->srRentalsPrevButton,  &QToolButton::clicked, this, &SearchView::onRentalsPrev);
    connect(ui->srRentalsNextButton,  &QToolButton::clicked, this, &SearchView::onRentalsNext);
    connect(ui->srRentalsLastButton,  &QToolButton::clicked, this, &SearchView::onRentalsLast);
}

void SearchView::fillCombo()
{
    ui->srStfCombo->clear();

    for (int r = 0; r < customersModel->rowCount(); r++)
    {
        const QString code = customersModel->item(r, 0)->text();
        const QString name = customersModel->item(r, 1)->text();

        ui->srStfCombo->addItem(code + " " + name);
    }
}

void SearchView::moveCursorClients(int row) const
{
    if (row >= 0 && row < customersModel->rowCount())
        ui->srClientsTable->selectRow(row);
}

void SearchView::moveCursorRentals(int row) const
{
    if (row >= 0 && row < rentalsModel->rowCount())
        ui->srRentalsTable->selectRow(row);
}

int SearchView::findClientRowByName(const QString& text) const
{
    for (int r = 0; r < customersModel->rowCount(); r++)
    {
        const QString name = customersModel->item(r, 1)->text();
        if (name.contains(text, Qt::CaseInsensitive))
            return r;
    }
    return -1;
}

int SearchView::findRentalRow(const QDate& date, const QString& clientCode) const
{
    for (int r = 0; r < rentalsModel->rowCount(); r++)
    {
        // Дата прийому. Дата з моделі у вигляді QString, конвертуємо в QDate
        QDate d = QDate::fromString(rentalsModel->item(r, 3)->text(), "yyyy-MM-dd");

        // Клієнт (код)
        const QString c = rentalsModel->item(r, 4)->text();

        // Порівняння QDate + код
        if (d.isValid() && d == date && c == clientCode)
            return r;
    }
    return -1;
}

bool SearchView::lookupTape(const QString& title,
                            const QString& type,
                            QString& outCode,
                            QString& outPrice) const
{
    for (int r = 0; r < tapesModel->rowCount(); r++)
    {
        const QString t = tapesModel->item(r, 1)->text();
        const QString ty = tapesModel->item(r, 2)->text();
        if (t == title && ty == type)
        {
            outCode = tapesModel->item(r, 0)->text();
            outPrice = tapesModel->item(r, 3)->text();
            return true;
        }
    }
    return false;
}

void SearchView::onSearchByName()
{
    const QString text = ui->srSbnInput->text().trimmed();
    if (text.isEmpty())
        return;

    const int row = findClientRowByName(text);
    if (row < 0)
    {
        QMessageBox::information(nullptr, "Пошук", "Клієнта не знайдено");
        return;
    }

    moveCursorClients(row);

    const QString code = customersModel->item(row, 0)->text();

    for (int r = 0; r < rentalsModel->rowCount(); r++)
    {
        const QString c = rentalsModel->item(r, 4)->text();
        if (c == code)
        {
            moveCursorRentals(r);
            return;
        }
    }

    ui->srRentalsTable->clearSelection();
}

void SearchView::onSearchTwoFields()
{
    QDate date = ui->srStfDateInput->date();

    const QString combo = ui->srStfCombo->currentText();
    const QString clientCode = combo.left(combo.indexOf(' '));

    const int row = findRentalRow(date, clientCode);
    if (row < 0)
    {
        QMessageBox::information(nullptr, "Пошук", "Запис не знайдено");
        return;
    }

    moveCursorRentals(row);
}

void SearchView::onSearchLookup()
{
    const QString title = ui->srSluTitleInput->text().trimmed();
    const QString type  = ui->srSluTypeInput->text().trimmed();

    if (title.isEmpty() || type.isEmpty())
        return;

    QString code, price;
    if (!lookupTape(title, type, code, price))
    {
        ui->srSluResultOutput->setText("Не знайдено");
        return;
    }

    ui->srSluResultOutput->setText("Код касети=" + code + " Ціна=" + price);
}

void SearchView::onClientsFirst()
{
    if (customersModel->rowCount() > 0)
        moveCursorClients(0);
}

void SearchView::onClientsPrev()
{
    int row = ui->srClientsTable->currentIndex().row();
    if (row > 0)
        moveCursorClients(row - 1);
}

void SearchView::onClientsNext()
{
    int row = ui->srClientsTable->currentIndex().row();
    if (row < customersModel->rowCount() - 1)
        moveCursorClients(row + 1);
}

void SearchView::onClientsLast()
{
    if (customersModel->rowCount() > 0)
        moveCursorClients(customersModel->rowCount() - 1);
}

void SearchView::onRentalsFirst()
{
    if (rentalsModel->rowCount() > 0)
        moveCursorRentals(0);
}

void SearchView::onRentalsPrev()
{
    int row = ui->srRentalsTable->currentIndex().row();
    if (row > 0)
        moveCursorRentals(row - 1);
}

void SearchView::onRentalsNext()
{
    int row = ui->srRentalsTable->currentIndex().row();
    if (row < rentalsModel->rowCount() - 1)
        moveCursorRentals(row + 1);
}

void SearchView::onRentalsLast()
{
    if (rentalsModel->rowCount() > 0)
        moveCursorRentals(rentalsModel->rowCount() - 1);
}

void SearchView::reloadView()
{
    // Очищаємо комбобокс
    ui->srStfCombo->clear();

    // Наповнюємо заново: "код ПІБ"
    for (int r = 0; r < customersModel->rowCount(); r++)
    {
        const QString code = customersModel->item(r, 0)->text();
        const QString name = customersModel->item(r, 1)->text();
        ui->srStfCombo->addItem(code + " " + name);
    }
}