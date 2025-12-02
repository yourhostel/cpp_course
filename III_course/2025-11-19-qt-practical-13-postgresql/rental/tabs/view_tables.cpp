//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/view_tables.cpp
#include "view_tables.h"
#include <QMessageBox>

#include "no_edit_delegate.h"
#include "sql_helper.h"
#include "table_specs.h"

ViewTables::ViewTables(Ui::Rental* uiPtr,
                       QStandardItemModel* tapes_model,
                       QStandardItemModel* customers_model,
                       QStandardItemModel* rentals_model,
                       SqlHelper* helper,
                       QObject* parent)
    : QObject(parent),
      ui(uiPtr),
      helper(helper),
      tapesModel(tapes_model),
      customersModel(customers_model),
      rentalsModel(rentals_model)
{
    tapeSpec = TapeSpec;
    customerSpec = CustomerSpec;
    rentalSpec = RentalSpec;

    // 5. Створення моделей (порожніх)
    // Таблиця касет
    setupTapesTable();
    // Таблиця клієнтів
    setupCustomersTable();
    // Таблиця прокату
    setupRentalsTable();

    // Завантаження БД
    loadAllTables();

    // Підключення кнопок
    // Таблиця касет
    connect(ui->tapesAddButton, &QPushButton::clicked,
        this, &ViewTables::onAddTapeClicked);

    // прі зміні фокуса комірки
    connect(tapesModel, &QStandardItemModel::itemChanged,
    this, &ViewTables::refreshComboDelegates);      // рефрешим комбо в таблиці прокату

    connect(ui->tapesSaveButton, &QPushButton::clicked,
    this, &ViewTables::onSaveTapesClicked);

    connect(ui->tapesDeleteButton, &QPushButton::clicked, this, [this]()
    {
        deleteSelectedRow(ui->tapesTable, tapesModel, tapeSpec);
    });

    // Таблиця клієнтів
    connect(ui->customersAddButton, &QPushButton::clicked,
            this, &ViewTables::onAddCustomerClicked);

    // прі зміні фокусу комірки
    connect(customers_model, &QStandardItemModel::itemChanged,
            this, &ViewTables::refreshComboDelegates); // рефрешим комбо в таблиці прокату

    connect(ui->customersSaveButton, &QPushButton::clicked,
        this, &ViewTables::onSaveCustomersClicked);

    connect(ui->customersDeleteButton, &QPushButton::clicked, this, [this]()
    {
        deleteSelectedRow(ui->customersTable, customersModel, customerSpec);
    });

    // Таблиця прокату
    connect(ui->rentalsAddButton, &QPushButton::clicked,
            this, &ViewTables::onAddRentalClicked);

    connect(ui->rentalsSaveButton, &QPushButton::clicked,
        this, &ViewTables::onSaveRentalsClicked);

    connect(ui->rentalsDeleteButton, &QPushButton::clicked, this, [this]()
    {
        deleteSelectedRow(ui->rentalsTable, this->rentalsModel, rentalSpec);
    });

    if (auto sel = ui->tapesTable->selectionModel(); sel)
    {
        connect(sel, &QItemSelectionModel::currentRowChanged,
                this, &ViewTables::onTapeRowChanged);
    }

    if (auto sel = ui->customersTable->selectionModel(); sel)
    {
        connect(sel, &QItemSelectionModel::currentRowChanged,
                this, &ViewTables::onCustomerRowChanged);
    }

}

/** ========================================================================
 * Показує інформаційне повідомлення про успішне збереження таблиці.
 *
 * Алгоритм:
 *   1) Викликати QMessageBox::information.
 *   2) Показати назву таблиці у тексті повідомлення.
 *
 * Призначення:
 *   Використовується після успішного виконання saveModel() для того,
 *   щоб повідомити користувача про завершення операції збереження.
 *
 * @param tableName Назва таблиці, яка була збережена.
 */
void ViewTables::showSaveSuccess(const QString& tableName) const
{
    QMessageBox::information(
        ui->tapesTable,
        "Збережено",
        "Таблиця \"" + tableName + "\" успішно збережена."
    );
}

//==========================================================================
// Завантаження при запуску форми
//==========================================================================

/** ========================================================================
 * Завантажує таблицю касет з бази у модель tapesModel.
 *
 * Алгоритм:
 *   1) Викликати helper => loadModel для tapesModel.
 *   2) Якщо отримано помилку, показати QMessageBox::critical.
 *
 * Призначення:
 *   Синхронізує дані між таблицею "tapes" у PostgreSQL
 *   та відповідною QStandardItemModel.
 *
 * @return void
 */
void ViewTables::loadTapes()
{
    if (QString err; !helper->loadModel(tapesModel, tapeSpec, err))
        QMessageBox::critical(ui->tapesTable, "Помилка", err);
}

/** ========================================================================
 * Завантажує таблицю клієнтів з бази у модель customersModel.
 *
 * Алгоритм:
 *   1) Викликати helper => loadModel для customersModel.
 *   2) Якщо сталася помилка, показати QMessageBox::critical.
 *
 * Призначення:
 *   Актуалізує дані про клієнтів перед відображенням у UI.
 *
 * @return void
 */
void ViewTables::loadCustomers()
{
    if (QString err; !helper->loadModel(customersModel, customerSpec, err))
        QMessageBox::critical(ui->customersTable, "Помилка", err);
}

/** ========================================================================
 * Завантажує таблицю прокату з бази у модель rentalsModel.
 *
 * Алгоритм:
 *   1) Викликати helper => loadModel для rentalsModel.
 *   2) Якщо запит не виконано, показати QMessageBox::critical.
 *
 * Призначення:
 *   Забезпечує відображення актуальної інформації про прокат
 *   (строки видачі, повернення, копії, клієнт, касета).
 *
 * @return void
 */
void ViewTables::loadRentals()
{
    if (QString err; !helper->loadModel(rentalsModel, rentalSpec, err))
        QMessageBox::critical(ui->rentalsTable, "Помилка", err);
}

/** ========================================================================
 * Завантажує всі таблиці додатку з бази.
 *
 * Алгоритм:
 *   1) Викликати loadTapes().
 *   2) Викликати loadCustomers().
 *   3) Викликати loadRentals().
 *   4) Оновити комбоделегати, щоб вони використовували
 *      актуальні списки касет і клієнтів.
 *
 * Призначення:
 *   Метод для повного оновлення усіх моделей після запуску
 *   або після змін у базі даних.
 *
 * @return void
 */
void ViewTables::loadAllTables()
{
    loadTapes();
    loadCustomers();
    loadRentals();

    // оновити комбо
    refreshComboDelegates();

    emit dataReloaded();
}

//==========================================================================
// Обробка подій
//==========================================================================

/** ========================================================================
 * Обробляє подію натискання кнопки збереження таблиці касет.
 *
 * Алгоритм:
 *   1) Викликати helper => saveModel(tapesModel, tapeSpec).
 *   2) Якщо saveModel повертає помилку:
 *        - показати QMessageBox::critical з текстом помилки;
 *        - завершити метод через return.
 *   3) Якщо збереження виконано успішно,
 *        показати повідомлення через showSaveSuccess("Касети").
 *
 * Призначення:
 *   Зберігає змінені та нові записи таблиці касет у базу PostgreSQL
 *   (таблиця "tapes"). Викликається кнопкою "Зберегти" у вкладці касет.
 *
 * @return void
 */
void ViewTables::onSaveTapesClicked()
{
    if (QString err; !helper->saveModel(tapesModel, tapeSpec, err))
    {
        QMessageBox::critical(ui -> tapesTable, "Помилка", err);
        return;
    }

    showSaveSuccess("Касети");

    emit dataReloaded();
}

/** ========================================================================
 * Обробляє подію натискання кнопки збереження таблиці клієнтів.
 *
 * Алгоритм:
 *   1) Викликати helper => saveModel(customersModel, customerSpec).
 *   2) Якщо saveModel повертає помилку:
 *        - показати QMessageBox::critical з текстом помилки;
 *        - завершити метод через return.
 *   3) Якщо збереження успішне, показати повідомлення
 *        через showSaveSuccess("Клієнти").
 *
 * Призначення:
 *   Зберігає усі зміни, зроблені користувачем у таблиці клієнтів,
 *   до відповідної таблиці PostgreSQL ("customers").
 *   Викликається напряму кнопкою "Зберегти" з UI.
 *
 * @return void
 */
void ViewTables::onSaveCustomersClicked() const
{
    if (QString err; !helper->saveModel(customersModel, customerSpec, err))
    {
        QMessageBox::critical(ui -> customersTable, "Помилка", err);
        return;
    }

    showSaveSuccess("Клієнти");
}

void ViewTables::onSaveRentalsClicked() const
{
    if (QString err; !helper->saveModel(rentalsModel, rentalSpec, err))
    {
        QMessageBox::critical(ui -> rentalsTable, "Помилка", err);
        return;
    }

    showSaveSuccess("Прокат");
}

/** ========================================================================
 * Додає порожній рядок у модель.
 *
 * Алгоритм:
 *   1) Визначити індекс нового рядка (кількість існуючих).
 *   2) Виконати insertRow(r) у модель.
 *   3) Створити порожній QStandardItem("") для кожної колонки.
 *   4) Якщо це таблиця прокату (rentalsModel):
 *        - встановити у колонку "Касета" ID першої касети,
 *        - встановити у колонку "Клієнт" ID першого клієнта.
 *     (делегат пізніше відобразить відповідний текст).
 *   5) Оновити комбоделегати, щоб вони враховували можливі зміни моделей.
 *
 * Пояснення:
 *   QStandardItemModel не створює елементів автоматично після insertRow,
 *   тому кожну клітинку необхідно заповнювати вручну.
 *   Для таблиці прокату новий рядок одразу отримує валідні значення у
 *   combo-колонках (ID першої касети та ID першого клієнта), щоб у UI
 *   одразу відображались відповідні комбібокси з коректними даними.
 *
 * @param model Модель, у яку додається новий рядок.
 */
void ViewTables::addEmptyRow(QStandardItemModel* model) const
{
    //model->blockSignals(true);
    const int r = model->rowCount();
    model->insertRow(r);

    for (int c = 0; c < model->columnCount(); c++)
        model->setItem(r, c, new QStandardItem(""));

    // Якщо додаємо рядок у таблицю прокату
    if (model == rentalsModel)
    {
        // перша касета
        const int firstTapeId = getFirstId(tapesModel);
        model->setItem(r, 1, new QStandardItem(QString::number(firstTapeId)));

        // перший клієнт
        const int firstCustomerId = getFirstId(customersModel);
        model->setItem(r, 4, new QStandardItem(QString::number(firstCustomerId)));
    }

    refreshComboDelegates();
}

/** ========================================================================
 * Обробка кнопки додавання касети.
 *
 * @return void
 */
void ViewTables::onAddTapeClicked() const { addEmptyRow(tapesModel); }

/** ========================================================================
 * Обробка кнопки додавання клієнта.
 *
 * @return void
 */
void ViewTables::onAddCustomerClicked() const { addEmptyRow(customersModel); }

/** ========================================================================
 * Обробка кнопки додавання прокату.
 *
 * @return void
 */
void ViewTables::onAddRentalClicked() const { addEmptyRow(rentalsModel); }

void ViewTables::deleteSelectedRow(const QTableView* table,
                               QStandardItemModel* model,
                               const TableSpec& spec)
{
    const QModelIndex idx = table->currentIndex();

    if (!idx.isValid())
    {
        QMessageBox::warning(nullptr, "Увага", "Рядок не вибрано.");
        return;
    }

    const int row = idx.row();
    const QString id = model->item(row, 0)->text();

    if (id.isEmpty())
    {
        // просто видаляємо рядок без БД
        model->removeRow(row);
        refreshComboDelegates();
        emit dataReloaded();
        return;
    }

    // підтвердження
    if (QMessageBox::question(nullptr,
         "Підтвердження",
         "Видалити запис з ID " + id + "?"
        ) != QMessageBox::Yes)
    {
        return;
    }

    if (QString err; !helper->deleteRow(spec, id.toInt(), err))
    {
        QMessageBox::critical(nullptr, "Помилка", err);
        return;
    }

    // успішне видалення
    QMessageBox::information(nullptr, "Успіх", "Запис успішно видалено.");

    model->removeRow(row);
    refreshComboDelegates();

    // оновлення відображення після змін
    loadAllTables();
}

void ViewTables::onTapeRowChanged(const QModelIndex &current, const QModelIndex &previous) const
{
    if (!current.isValid()) {
        ui->tapeInfoText->clear();
        return;
    }

    const int row = current.row();
    const QString description = tapesModel->item(row, 4)->text();

    ui->tapeInfoText->setPlainText(description);
}

void ViewTables::onCustomerRowChanged(const QModelIndex &current, const QModelIndex &previous) const
{
    if (!current.isValid()) {
        ui->customerInfoText->clear();
        return;
    }

    const int row = current.row();
    const QString info = customersModel->item(row, 2)->text();

    ui->customerInfoText->setPlainText(info);
}

//==========================================================================
// Налаштування таблиць
//==========================================================================

/** ========================================================================
 * Налаштовує зовнішній вигляд і поведінку QTableView.
 *
 * Алгоритм:
 *   1) Встановити режим розширення колонок.
 *   2) Приховати вертикальний заголовок.
 *   3) Увімкнути виділення рядків.
 *   4) Дозволити редагування тільки по подвійному кліку.
 *
 * @param table Вказівник на таблицю, яку потрібно налаштувати
 * @return void
 */
static void setupTableView(QTableView* table)
{
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QTableView::SelectRows);
    table->setEditTriggers(QAbstractItemView::DoubleClicked);
}

/** ========================================================================
 * Встановлює заголовки колонок моделі.
 *
 * Алгоритм:
 *   1) Пройти по списку назв.
 *   2) Присвоїти кожній колонці відповідний текст.
 *
 * @param model Модель, у яку встановлюються назви колонок
 * @param names Список назв колонок у правильному порядку
 * @return void
 */
static void setHeaders(QStandardItemModel* model,
                       const QStringList& names)
{
    for (int i = 0; i < names.size(); i++)
        model->setHeaderData(i, Qt::Horizontal, names[i]);
}

/** ========================================================================
 * Налаштування таблиці касет.
 *
 * Алгоритм:
 *   1) Створити модель.
 *   2) Встановити заголовки через setHeaders.
 *   3) Привязати модель до TableView.
 *   4) Додати делегат блокування редагування ID.
 *
 * @return void
 */
void ViewTables::setupTapesTable()
{
    tapesModel->setColumnCount(5);

    setHeaders(tapesModel, {"Код","Назва","Тип","Ціна/день","Опис"});

    ui->tapesTable->setModel(tapesModel);

    ui->tapesTable->setItemDelegateForColumn(0, new NoEditDelegate(this));

    setupTableView(ui->tapesTable);
}

/** ========================================================================
 * Налаштування таблиці клієнтів.
 *
 * Алгоритм:
 *   1) Створити модель з потрібною кількістю колонок.
 *   2) Встановити заголовки.
 *   3) Привязати модель до таблиці.
 *   4) Заблокувати редагування ID через делегат.
 *   5) Налаштувати зовнішній вигляд таблиці методом setupTableView.
 *
 * @return void
 */
void ViewTables::setupCustomersTable()
{
    customersModel->setColumnCount(3);

    setHeaders(customersModel, {"Код","ПІБ","Інформація"});

    ui->customersTable->setModel(customersModel);

    ui->customersTable->setItemDelegateForColumn(0, new NoEditDelegate(this));

    setupTableView(ui->customersTable);
}

/** ========================================================================
 * Налаштовує таблицю прокату.
 *
 * Алгоритм:
 *   1) Створити модель з потрібною кількістю колонок.
 *   2) Встановити заголовки через setHeaders.
 *   3) Привязати модель до таблиці.
 *   4) Заблокувати редагування колонки ID.
 *   5) Налаштувати зовнішній вигляд таблиці методом setupTableView.
 *   6) Створити два комбоделегати:
 *        tapeDelegate для вибору касети,
 *        customerDelegate для вибору клієнта.
 *   7) Закріпити відповідні делегати за колонками.
 *
 * @return void
 */
void ViewTables::setupRentalsTable()
{
    rentalsModel->setColumnCount(8);

    setHeaders(rentalsModel,{
        "Код","Касета","Дата видачі","Дата прийому",
        "Клієнт","К-сть копій","Термін","Повернено"
    });

    ui->rentalsTable->setModel(rentalsModel);

    ui->rentalsTable->setItemDelegateForColumn(0, new NoEditDelegate(this));

    setupTableView(ui->rentalsTable);

    // Додаємо делегати
    tapeDelegate = new ComboDelegate(
    getTexts(tapesModel),   // текстові назви
    getIds(tapesModel),     // відповідні ID
    this
     );

    customerDelegate = new ComboDelegate(
    getTexts(customersModel),
    getIds(customersModel),
    this
     );

    ui->rentalsTable->setItemDelegateForColumn(1, tapeDelegate);
    ui->rentalsTable->setItemDelegateForColumn(4, customerDelegate);
}

// ==========================================================================
// Логіка Combo
// ==========================================================================

/** ========================================================================
 * Повертає ID першого запису у вказаній моделі.
 *
 * Алгоритм:
 *   1) Перевірити кількість рядків у моделі.
 *   2) Якщо рядків немає, повернути 0 як дефолтне значення.
 *   3) Якщо рядок існує, взяти комірку колонки 0 першого рядка.
 *   4) Прочитати текстове значення та конвертувати його у int.
 *   5) Повернути отриманий ID.
 *
 * Призначення:
 *   Використовується при створенні нового рядка прокату для того,
 *   щоб автоматично заповнювати combo-поля першим валідним ID
 *   (першої касети або першого клієнта).
 *
 * @param model Модель, з якої потрібно отримати перший ID.
 * @return Цілочисельний ID першого елементу або 0, якщо модель порожня.
 */
int ViewTables::getFirstId(const QStandardItemModel* model) const
{
    if (model->rowCount() == 0)
        return 0;
    return model->item(0, 0)->text().toInt();
}

/** ========================================================================
 * Повертає список усіх ID із колонки 0 заданої моделі.
 *
 * Алгоритм:
 *   1) Створити порожній список ids.
 *   2) Пройти всі рядки моделі.
 *   3) У кожному рядку прочитати комірку колонки 0 (ID).
 *   4) Якщо елемент існує, конвертувати його текст у int
 *      і додати до списку ids.
 *   5) Повернути сформований список.
 *
 * Призначення:
 *   Метод використовується делегатами ComboDelegate для формування
 *   відповідного списку ID, що записуватимуться у модель при виборі.
 *
 * @param model Модель, з якої зчитуються ID.
 * @return QList<int> - список ID усіх рядків таблиці.
 */
QList<int> ViewTables::getIds(const QStandardItemModel* model) const
{
    QList<int> ids;
    for (int r = 0; r < model->rowCount(); r++)
    {
        const QStandardItem* item = model->item(r, 0); // колонка ID
        if (!item) continue;
        ids << item->text().toInt();
    }
    return ids;
}

/** ========================================================================
 * Повертає список текстових значень із колонки 1 заданої моделі.
 *
 * Алгоритм:
 *   1) Створити порожній список list.
 *   2) Пройти всі рядки моделі.
 *   3) Прочитати комірку колонки 1 (текстове поле).
 *   4) Якщо елемент існує, додати його текст до списку list.
 *   5) Повернути сформований список.
 *
 * Призначення:
 *   Метод використовується ComboDelegate для відображення текстових
 *   значень (назв касет, ПІБ клієнтів) у QComboBox та у displayText().
 *
 * @param model Модель, з якої зчитуються текстові значення.
 * @return QStringList - список назв або текстів, прив’язаних до ID.
 */
QStringList ViewTables::getTexts(const QStandardItemModel* model) const
{
    QStringList list;
    for (int r = 0; r < model->rowCount(); r++)
    {
        const QStandardItem* item = model->item(r, 1); // колонка тексту
        if (!item) continue;
        list << item->text();
    }
    return list;
}

/** ========================================================================
 * Повертає список імен клієнтів (текстове поле колонки 1).
 *
 * Алгоритм:
 *   1) Створити порожній список list.
 *   2) Пройти всі рядки моделі customersModel.
 *   3) Для кожного рядка прочитати комірку колонки 1 (ПІБ клієнта).
 *   4) Якщо елемент існує. одати його текст до list.
 *   5) Повернути сформований список.
 *
 * Призначення:
 *   Службовий метод для роботи комбоделегатів, коли потрібно отримати
 *   список текстових назв клієнтів (ПІБ) з моделі.
 *   Використовується при формуванні ComboBox у таблиці прокату.
 *
 * @return QStringList - список ПІБ клієнтів у тому порядку, як у моделі.
 */
QStringList ViewTables::getCustomerNames() const
{
    QStringList list;
    for (int r = 0; r < customersModel->rowCount(); r++)
    {
        if (const auto *item = customersModel->item(r, 1))
            list << item->text();
    }
    return list;
}

/** ========================================================================
 * Оновлює список значень у комбоделегатах.
 *
 * Алгоритм:
 *   1) Зібрати список касет.
 *   2) Зібрати список клієнтів.
 *   3) Передати їх у делегати.
 *
 * @return void
 */
void ViewTables::refreshComboDelegates() const
{
    if (tapeDelegate)
        tapeDelegate->updateData(getTexts(tapesModel), getIds(tapesModel));

    if (customerDelegate)
        customerDelegate->updateData(getTexts(customersModel), getIds(customersModel));
}

