//
// Created by tysser on 01.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/visual_components.cpp
#include "visual_components.h"
#include "sql_helper.h"
#include "table_specs.h"
#include "../ui_rental.h"

#include <QMessageBox>

VisualComponents::VisualComponents(Ui_Rental* ui,
                                   QStandardItemModel* tapesModel,
                                   QStandardItemModel* customersModel,
                                   QStandardItemModel* rentalsModel,
                                   SqlHelper* helper,
                                   QObject* parent)
    : QObject(parent),
      ui(ui),
      tapesModel(tapesModel),
      customersModel(customersModel),
      rentalsModel(rentalsModel),
      helper(helper)
{
    tapeSpec = TapeSpec;
    rentalSpec = RentalSpec;

    // ===== CONNECT NAVIGATION =====
    connect(ui->vcTapeFirstButton,  &QToolButton::clicked, this, &VisualComponents::onTapeFirst);
    connect(ui->vcTapePrevButton,   &QToolButton::clicked, this, &VisualComponents::onTapePrev);
    connect(ui->vcTapeNextButton,   &QToolButton::clicked, this, &VisualComponents::onTapeNext);
    connect(ui->vcTapeLastButton,   &QToolButton::clicked, this, &VisualComponents::onTapeLast);

    connect(ui->vcRentalFirstButton, &QToolButton::clicked, this, &VisualComponents::onRentalFirst);
    connect(ui->vcRentalPrevButton,  &QToolButton::clicked, this, &VisualComponents::onRentalPrev);
    connect(ui->vcRentalNextButton,  &QToolButton::clicked, this, &VisualComponents::onRentalNext);
    connect(ui->vcRentalLastButton,  &QToolButton::clicked, this, &VisualComponents::onRentalLast);

    // ===== CONNECT TAPE BUTTONS =====
    connect(ui->vcTapeAddButton,    &QPushButton::clicked, this, &VisualComponents::onTapeAdd);
    connect(ui->vcTapeEditButton,   &QPushButton::clicked, this, &VisualComponents::onTapeEdit);
    connect(ui->vcTapeDeleteButton, &QPushButton::clicked, this, &VisualComponents::onTapeDelete);
    connect(ui->vcTapeCancelButton, &QPushButton::clicked, this, &VisualComponents::onTapeCancel);
    connect(ui->vcTapeSaveButton,   &QPushButton::clicked, this, &VisualComponents::onTapeSave);

    // ===== CONNECT RENTAL BUTTONS =====
    connect(ui->vcRentalAddButton,    &QPushButton::clicked, this, &VisualComponents::onRentalAdd);
    connect(ui->vcRentalEditButton,   &QPushButton::clicked, this, &VisualComponents::onRentalEdit);
    connect(ui->vcRentalDeleteButton, &QPushButton::clicked, this, &VisualComponents::onRentalDelete);
    connect(ui->vcRentalCancelButton, &QPushButton::clicked, this, &VisualComponents::onRentalCancel);
    connect(ui->vcRentalSaveButton,   &QPushButton::clicked, this, &VisualComponents::onRentalSave);

    // Початкове заповнення
    loadFirstTape();
    loadFirstRental();
}

// ====================================================================
// Навігація по касетах
// ====================================================================

void VisualComponents::onTapeFirst()
{
    if (!checkTapeEditingBeforeNavigate()) return;
    if (tapesModel->rowCount() == 0) return;
    loadTapeFields(0);
}

void VisualComponents::onTapePrev()
{
    if (!checkTapeEditingBeforeNavigate()) return;
    if (tapesModel->rowCount() == 0) return;

    int newIndex = currentTapeIndex - 1;
    if (newIndex < 0) newIndex = 0;

    loadTapeFields(newIndex);
}

void VisualComponents::onTapeNext()
{
    if (!checkTapeEditingBeforeNavigate()) return;
    const int total = tapesModel->rowCount();
    if (total == 0) return;

    int newIndex = currentTapeIndex + 1;
    if (newIndex >= total) newIndex = total - 1;

    loadTapeFields(newIndex);
}

void VisualComponents::onTapeLast()
{
    if (!checkTapeEditingBeforeNavigate()) return;
    const int total = tapesModel->rowCount();
    if (total == 0) return;

    loadTapeFields(total - 1);
}

bool VisualComponents::checkTapeEditingBeforeNavigate()
{
    // Перевірити чи стан редагування
    if (!tapeState.editing && !tapeState.adding)
        return true;

    if (!askCancelEditing("Стан касет", "Скасувати редагування?"))
        return false;

    // Скасувати редагування/додавання
    onTapeCancel();
    return true;
}

// ====================================================================
// Навігація по прокатах
// ====================================================================

void VisualComponents::onRentalFirst()
{
    if (!checkRentalEditingBeforeNavigate()) return;
    if (rentalsModel->rowCount() == 0) return;
    loadRentalFields(0);
}

void VisualComponents::onRentalPrev()
{
    if (!checkRentalEditingBeforeNavigate()) return;
    if (rentalsModel->rowCount() == 0) return;

    int newIndex = currentRentalIndex - 1;
    if (newIndex < 0) newIndex = 0;

    loadRentalFields(newIndex);
}

void VisualComponents::onRentalNext()
{
    if (!checkRentalEditingBeforeNavigate()) return;
    const int total = rentalsModel->rowCount();
    if (total == 0) return;

    int newIndex = currentRentalIndex + 1;
    if (newIndex >= total) newIndex = total - 1;

    loadRentalFields(newIndex);
}

void VisualComponents::onRentalLast()
{
    if (!checkRentalEditingBeforeNavigate()) return;
    const int total = rentalsModel->rowCount();
    if (total == 0) return;

    loadRentalFields(total - 1);
}

bool VisualComponents::checkRentalEditingBeforeNavigate()
{
    if (!rentalState.editing && !rentalState.adding)
        return true;

    if (!askCancelEditing("Стан прокату", "Скасувати редагування?"))
        return false;

    onRentalCancel();
    return true;
}

// ====================================================================
// Кнопки дій над станом касет
// ====================================================================

void VisualComponents::onTapeAdd()
{
    if (tapeState.adding || tapeState.editing)
        return; // Вже в режимі редагування

    tapeState.adding = true;
    tapeState.prevIndex = currentTapeIndex;

    // Додаємо новий порожній рядок
    tapesModel->insertRow(tapesModel->rowCount());
    tapeState.newIndex = tapesModel->rowCount() - 1;

    currentTapeIndex = tapeState.newIndex;
    tapesModel->setItem(currentTapeIndex, 0, new QStandardItem("-"));

    clearTapeFields();
    setTapeFieldsEditable(true);
}

void VisualComponents::onTapeEdit()
{
    if (tapeState.adding || tapeState.editing)
        return;

    tapeState.editing = true;

    setTapeFieldsEditable(true);
}

void VisualComponents::onTapeCancel()
{
    if (tapeState.adding)
    {
        // Видаляємо новий рядок
        if (tapeState.newIndex >= 0 &&
            tapeState.newIndex < tapesModel->rowCount())
        {
            tapesModel->removeRow(tapeState.newIndex);
        }

        // Повертаємось на попередній запис
        loadTapeFields(tapeState.prevIndex);
    }
    else if (tapeState.editing)
    {
        // Перезавантажуємо те, що було в моделі
        loadTapeFields(currentTapeIndex);
    }

    setTapeFieldsEditable(false);

    // Обнуляємо стан
    tapeState = {};
}

void VisualComponents::onTapeSave()
{
    if (!tapeState.adding && !tapeState.editing)
        return;

    const int row = currentTapeIndex;

    // Перенести значення з UI у модель
    tapesModel->setItem(row, 1, new QStandardItem(ui->vcTapeTitleEdit->text()));
    tapesModel->setItem(row, 2, new QStandardItem(ui->vcTapeTypeEdit->text()));
    tapesModel->setItem(row, 3, new QStandardItem(ui->vcTapePriceEdit->text()));
    tapesModel->setItem(row, 4, new QStandardItem(ui->vcTapeDescriptionEdit->toPlainText()));

    QString error;
    if (!helper->saveModel(tapesModel, tapeSpec, error))
    {
        QMessageBox::critical(nullptr, "Помилка збереження", error);
        return;
    }

    // Отримати id з моделі після save
    const QString savedId = tapesModel->item(row, 0)->text();

    // Оновити модель повністю
    if (!helper->loadModel(tapesModel, tapeSpec, error))
    {
        QMessageBox::critical(nullptr, "Помилка оновлення", error);
        return;
    }

    // Оновити комбо у rentals
    fillTapeCombo();

    // Знайти рядок з id у оновленій моделі
    int newIndex = 0;
    for (int i = 0; i < tapesModel->rowCount(); i++)
    {
        if (tapesModel->item(i, 0)->text() == savedId)
        {
            newIndex = i;
            break;
        }
    }

    // Показати оновлені дані
    loadTapeFields(newIndex);
    currentTapeIndex = newIndex;

    setTapeFieldsEditable(false);
    tapeState = {};
}

void VisualComponents::onTapeDelete()
{
    if (tapeState.adding || tapeState.editing)
    {
        QMessageBox::warning(nullptr, "Увага",
                             "Спочатку завершіть або скасуйте редагування.");
        return;
    }

    const int row = currentTapeIndex;
    if (row < 0 || row >= tapesModel->rowCount())
        return;

    const int id = tapesModel->item(row, 0)->text().toInt();

    if (QMessageBox::question(nullptr, "Підтвердження",
                              "Видалити запис?",
                              QMessageBox::Yes | QMessageBox::No)
        != QMessageBox::Yes)
        return;

    QString error;
    if (!helper->deleteRow(tapeSpec, id, error))
    {
        QMessageBox::critical(nullptr, "Помилка видалення", error);
        return;
    }

    // Reload моделі після delete
    if (!helper->loadModel(tapesModel, tapeSpec, error))
    {
        QMessageBox::critical(nullptr, "Помилка оновлення", error);
        return;
    }

    // Оновити комбо у rentals
    fillTapeCombo();

    int newRow = row;
    if (newRow >= tapesModel->rowCount())
        newRow = tapesModel->rowCount() - 1;
    if (newRow < 0)
    {
        clearTapeFields();
        return;
    }

    loadTapeFields(newRow);
    currentTapeIndex = newRow;
}

// ====================================================================
// Кнопки дій над станом прокату
// ====================================================================

void VisualComponents::onRentalAdd()
{
    if (rentalState.adding || rentalState.editing)
        return;

    rentalState.adding = true;
    rentalState.prevIndex = currentRentalIndex;

    rentalsModel->insertRow(rentalsModel->rowCount());
    rentalState.newIndex = rentalsModel->rowCount() - 1;

    currentRentalIndex = rentalState.newIndex;
    rentalsModel->setItem(currentRentalIndex, 0, new QStandardItem("-"));

    clearRentalFields();
    setRentalFieldsEditable(true);
}

void VisualComponents::onRentalEdit()
{
    if (rentalState.adding || rentalState.editing)
        return;

    rentalState.editing = true;

    setRentalFieldsEditable(true);
}

void VisualComponents::onRentalCancel()
{
    if (rentalState.adding)
    {
        if (rentalState.newIndex >= 0 &&
            rentalState.newIndex < rentalsModel->rowCount())
        {
            rentalsModel->removeRow(rentalState.newIndex);
        }

        loadRentalFields(rentalState.prevIndex);
    }
    else if (rentalState.editing)
    {
        loadRentalFields(currentRentalIndex);
    }

    setRentalFieldsEditable(false);

    rentalState = {};
}

void VisualComponents::onRentalSave()
{
    if (!rentalState.adding && !rentalState.editing)
        return;

    const int row = currentRentalIndex;

    // Отримуємо вибрані ID з комбо
    const int tapeId = findTapeIdByName(ui->vcRentalTapeCombo->currentText());
    const int customerId = findCustomerIdByName(ui->vcRentalCustomerCombo->currentText());

    // Переносимо у модель
    rentalsModel->setItem(row, 1, new QStandardItem(QString::number(tapeId)));
    rentalsModel->setItem(row, 2, new QStandardItem(ui->vcRentalIssueDateEdit->text()));
    rentalsModel->setItem(row, 3, new QStandardItem(ui->vcRentalReturnDateEdit->text()));
    rentalsModel->setItem(row, 4, new QStandardItem(QString::number(customerId)));
    rentalsModel->setItem(row, 5, new QStandardItem(ui->vcRentalCopiesEdit->text()));
    rentalsModel->setItem(row, 6, new QStandardItem(ui->vcRentalDeadlineEdit->text()));
    rentalsModel->setItem(row, 7, new QStandardItem(ui->vcRentalReturnedCheck->isChecked() ? "true" : "false"));

    QString error;
    if (!helper->saveModel(rentalsModel, rentalSpec, error))
    {
        QMessageBox::critical(nullptr, "Помилка збереження", error);
        return;
    }

    // Зберегти id
    const QString savedId = rentalsModel->item(row, 0)->text();

    // Перезавантажити прокати
    if (!helper->loadModel(rentalsModel, rentalSpec, error))
    {
        QMessageBox::critical(nullptr, "Помилка оновлення", error);
        return;
    }

    // Оновлюємо комбо
    fillTapeCombo();
    fillCustomerCombo();

    // Знайти рядок з цим id
    int newIndex = 0;
    for (int i = 0; i < rentalsModel->rowCount(); i++)
    {
        if (rentalsModel->item(i, 0)->text() == savedId)
        {
            newIndex = i;
            break;
        }
    }

    loadRentalFields(newIndex);
    currentRentalIndex = newIndex;

    setRentalFieldsEditable(false);
    rentalState = {};
}

void VisualComponents::onRentalDelete()
{
    if (rentalState.adding || rentalState.editing)
    {
        QMessageBox::warning(nullptr, "Увага",
                             "Спочатку завершіть або скасуйте редагування.");
        return;
    }

    const int row = currentRentalIndex;
    if (row < 0 || row >= rentalsModel->rowCount())
        return;

    const int id = rentalsModel->item(row, 0)->text().toInt();

    if (QMessageBox::question(nullptr, "Підтвердження",
                              "Видалити запис?",
                              QMessageBox::Yes | QMessageBox::No)
        != QMessageBox::Yes)
        return;

    QString error;
    if (!helper->deleteRow(rentalSpec, id, error))
    {
        QMessageBox::critical(nullptr, "Помилка видалення", error);
        return;
    }

    // Перезавантажити прокати
    if (!helper->loadModel(rentalsModel, rentalSpec, error))
    {
        QMessageBox::critical(nullptr, "Помилка оновлення", error);
        return;
    }

    int newRow = row;
    if (newRow >= rentalsModel->rowCount())
        newRow = rentalsModel->rowCount() - 1;

    if (newRow < 0)
    {
        clearRentalFields();
        return;
    }

    loadRentalFields(newRow);
    currentRentalIndex = newRow;
}


// ====================================================================
// Логіка завантажувача касет
// ====================================================================

void VisualComponents::loadTapeFields(const int row)
{
    if (row < 0 || row >= tapesModel->rowCount()) {
        clearTapeFields();
        return;
    }

    currentTapeIndex = row;

    ui->vcTapeIdEdit->setText(tapesModel->item(row, 0)->text());
    ui->vcTapeTitleEdit->setText(tapesModel->item(row, 1)->text());
    ui->vcTapeTypeEdit->setText(tapesModel->item(row, 2)->text());
    ui->vcTapePriceEdit->setText(tapesModel->item(row, 3)->text());
    ui->vcTapeDescriptionEdit->setPlainText(tapesModel->item(row, 4)->text());
}

void VisualComponents::fillTapeCombo() const
{
    ui->vcRentalTapeCombo->clear();

    for (int i = 0; i < tapesModel->rowCount(); ++i)
    {
        if (const auto* item = tapesModel->item(i, 1))
            ui->vcRentalTapeCombo->addItem(item->text());
    }
}

void VisualComponents::loadFirstTape()
{
    if (tapesModel->rowCount() == 0) {
        clearTapeFields();
        return;
    }
    loadTapeFields(0);
    fillTapeCombo();
}

// ====================================================================
// Логіка завантажувача прокатів
// ====================================================================

QString VisualComponents::getTapeNameById(const int id) const
{
    for (int i = 0; i < tapesModel->rowCount(); ++i)
    {
        if (tapesModel->item(i, 0)->text().toInt() == id)
            return tapesModel->item(i, 1)->text();
    }
    return "";
}

QString VisualComponents::getCustomerNameById(const int id) const
{
    for (int i = 0; i < customersModel->rowCount(); ++i)
    {
        if (customersModel->item(i, 0)->text().toInt() == id)
            return customersModel->item(i, 1)->text();
    }
    return "";
}

void VisualComponents::loadRentalFields(const int row)
{
    if (row < 0 || row >= rentalsModel->rowCount()) {
        clearRentalFields();
        return;
    }

    currentRentalIndex = row;

    ui->vcRentalIdEdit->setText(rentalsModel->item(row, 0)->text());
    ui->vcRentalTapeIdEdit->setText(rentalsModel->item(row, 1)->text());

    // ComboBox: назва касети
    const int tapeId = rentalsModel->item(row, 1)->text().toInt();
    ui->vcRentalTapeCombo->setCurrentText(getTapeNameById(tapeId));

    ui->vcRentalIssueDateEdit->setText(rentalsModel->item(row, 2)->text());
    ui->vcRentalReturnDateEdit->setText(rentalsModel->item(row, 3)->text());

    ui->vcRentalCustomerIdEdit->setText(rentalsModel->item(row, 4)->text());

    // ComboBox: імʼя клієнта
    const int customerId = rentalsModel->item(row, 4)->text().toInt();
    ui->vcRentalCustomerCombo->setCurrentText(getCustomerNameById(customerId));

    ui->vcRentalCopiesEdit->setText(rentalsModel->item(row, 5)->text());
    ui->vcRentalDeadlineEdit->setText(rentalsModel->item(row, 6)->text());
    ui->vcRentalReturnedCheck->setChecked(
        rentalsModel->item(row, 7)->text() == "true"
    );
}

void VisualComponents::fillCustomerCombo() const
{
    ui->vcRentalCustomerCombo->clear();

    for (int i = 0; i < customersModel->rowCount(); ++i)
    {
        if (const auto* item = customersModel->item(i, 1))
            ui->vcRentalCustomerCombo->addItem(item->text());
    }
}

void VisualComponents::loadFirstRental()
{
    if (rentalsModel->rowCount() == 0) {
        clearRentalFields();
        return;
    }
    loadRentalFields(0);
    fillCustomerCombo();
}

// ====================================================================
// Внутрішні допоміжні функції
// ====================================================================

void VisualComponents::setTapeFieldsEditable(const bool enabled) const
{
    // ID завжди вимкнено
    ui->vcTapeIdEdit->setEnabled(false);

    ui->vcTapeTitleEdit->setEnabled(enabled);
    ui->vcTapeTypeEdit->setEnabled(enabled);
    ui->vcTapePriceEdit->setEnabled(enabled);
    ui->vcTapeDescriptionEdit->setEnabled(enabled);
}

void VisualComponents::setRentalFieldsEditable(const bool enabled) const
{
    ui->vcRentalIdEdit->setEnabled(false);          // ID операції
    ui->vcRentalTapeIdEdit->setEnabled(false);      // ID касети
    ui->vcRentalCustomerIdEdit->setEnabled(false);  // ID клієнта

    ui->vcRentalIssueDateEdit->setEnabled(enabled);
    ui->vcRentalReturnDateEdit->setEnabled(enabled);

    ui->vcRentalTapeCombo->setEnabled(enabled);
    ui->vcRentalCustomerCombo->setEnabled(enabled);

    ui->vcRentalCopiesEdit->setEnabled(enabled);
    ui->vcRentalDeadlineEdit->setEnabled(enabled);
    ui->vcRentalReturnedCheck->setEnabled(enabled);
}

void VisualComponents::clearTapeFields() const
{
    ui->vcTapeIdEdit->clear();
    ui->vcTapeTitleEdit->clear();
    ui->vcTapeTypeEdit->clear();
    ui->vcTapePriceEdit->clear();
    ui->vcTapeDescriptionEdit->clear();
}

void VisualComponents::clearRentalFields() const
{
    ui->vcRentalIdEdit->clear();
    ui->vcRentalTapeIdEdit->clear();

    ui->vcRentalIssueDateEdit->clear();
    ui->vcRentalReturnDateEdit->clear();

    ui->vcRentalCustomerIdEdit->clear();

    ui->vcRentalCopiesEdit->clear();
    ui->vcRentalDeadlineEdit->clear();

    ui->vcRentalReturnedCheck->setChecked(false);
}

int VisualComponents::findTapeIdByName(const QString& name) const
{
    for (int i = 0; i < tapesModel->rowCount(); i++)
    {
        if (tapesModel->item(i, 1)->text() == name)
            return tapesModel->item(i, 0)->text().toInt();
    }
    return -1;
}

int VisualComponents::findCustomerIdByName(const QString& name) const
{
    for (int i = 0; i < customersModel->rowCount(); i++)
    {
        if (customersModel->item(i, 1)->text() == name)
            return customersModel->item(i, 0)->text().toInt();
    }
    return -1;
}

bool VisualComponents::askCancelEditing(const QString& title,
                                        const QString& message)
{
    const QMessageBox::StandardButton reply =
        QMessageBox::question(nullptr,
            title,
            message,
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);

    return reply == QMessageBox::Yes;
}
