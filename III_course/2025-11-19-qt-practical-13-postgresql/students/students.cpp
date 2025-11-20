//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/students/students.cpp
#include "students.h"
#include "ui_students.h"

#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QStandardItemModel>
#include <QPixmap>
#include <QTimer>
#include <QSqlError>
#include <QSqlQuery>

//=========================== Students::Students ==========================
//  Конструктор.
//  Ініціалізує UI, створює модель таблиці, підключає сигнали,
//  завантажує дані з бази, встановлює дефолтне фото.
//=========================================================================
Students::Students(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Students)
{
    ui->setupUi(this);

    renderPhoto("");

    // Модель, заголовки, встановлення моделі
    setupTableModel();

    // Вигляд таблиці
    setupTableView();

    if (!connectDatabase())
    {
        // Дефолтний рядок
        insertDefaultRow(0);
        QMessageBox::critical(this, "Помилка", "Немає підключення до бази даних.");
    } else
    {
        loadStudents();
    }

    // Прив'язка кнопок до слота
    connect(ui->loadPhotoButton, &QPushButton::clicked, this, &Students::onLoadPhotoClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &Students::onDeleteClicked);
    connect(ui->addRowButton, &QPushButton::clicked, this, [this]()
    {
        // Якщо вже є дефолтний рядок - нічого не робимо
        if (lastRowIsDefault()) return;
        insertDefaultRow(model->rowCount());
    });
    connect(ui->saveButton, &QPushButton::clicked,this, &Students::onSaveClicked);

    // Перемикання на фото обробного рядка
    connect(ui->studentsTable->selectionModel(),&QItemSelectionModel::currentRowChanged,
    this,&Students::onRowChanged);
}

//============================ Students::~Students ========================
//  Деструктор.
//  Звільняє UI. Модель видаляється автоматично (parent=this).
//=========================================================================
Students::~Students()
{
    delete ui;
}

//=========================== setupTableModel ============================
//  Створює модель таблиці студентів, задає кількість колонок,
//  встановлює заголовки та початковий порожній рядок.
//========================================================================
void Students::setupTableModel()
{
    model = new QStandardItemModel(1, 6, this);

    model->setHeaderData(0, Qt::Horizontal, "Код");
    model->setHeaderData(1, Qt::Horizontal, "Прізвище");
    model->setHeaderData(2, Qt::Horizontal, "Ім'я");
    model->setHeaderData(3, Qt::Horizontal, "По батькові");
    model->setHeaderData(4, Qt::Horizontal, "Дата народження");
    model->setHeaderData(5, Qt::Horizontal, "Фотографія");

    ui->studentsTable->setModel(model);
}

//=========================== setupTableView =============================
//  Налаштовує поведінку таблиці: розтягування колонок,
//  виділення рядків, заборона мультивибору, правила редагування.
//========================================================================
void Students::setupTableView() const
{
    // Розтягування таблиці на всю ширину.
    ui->studentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Підганяє висоту рядків під їхній вміст (наприклад, якщо довгий текст).
    // ui->studentsTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // якщо не потрібні номери рядків
    ui->studentsTable->verticalHeader()->setVisible(false);

    // При кліку виділяється весь рядок, а не одна комірка.
    ui->studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Дозволяє обирати тільки один рядок одночасно.
    ui->studentsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Дозволяє редагувати клітинку при: подвійному кліку, або виділенні клітинки (клік)
    // ui->studentsTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->studentsTable->setEditTriggers(QAbstractItemView::DoubleClicked);
}

//========================== Students::onRowChanged =======================
//  Викликається при зміні активного рядка у QTableView.
//  Оновлює прев’ю-фото, читаючи шлях із моделі.
//=========================================================================
void Students::onRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if (!current.isValid())
    {
        renderPhoto("");
        return;
    }

    const int row = current.row();
    const QString path = model->item(row, 5)->text().trimmed();

    // Файл існує? — рендеримо
    if (!path.isEmpty() && QFile::exists(path))
    {
        renderPhoto(path);
    }
    else
    {
        renderPhoto("");
    }
}

//======================== Students::lastRowIsDefault =====================
//  Перевіряє, чи останній рядок таблиці - дефолтний шаблон.
//  Використовується, щоб не додавати дубльовані дефолтні рядки.
//=========================================================================
bool Students::lastRowIsDefault() const
{
    if (model->rowCount() == 0)
        return false;

    // Дивимось першу колонку (id)
    const QString id = model->item(model->rowCount() - 1, 0)->text().trimmed();
    return id == "-";
}

//========================= Students::insertDefaultRow ====================
//  Додає у таблицю порожній (дефолтний) рядок.
//  ID та стовпець Фото робляться нередагованими.
//=========================================================================
void Students::insertDefaultRow(const int row) const
{
    model->insertRow(row);

    // ID не редагується
    const auto id = new QStandardItem("-");
    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
    model->setItem(row, 0, id);

    model->setItem(row, 1, new QStandardItem("Прізвище"));
    model->setItem(row, 2, new QStandardItem("Ім'я"));
    model->setItem(row, 3, new QStandardItem("По батькові"));
    model->setItem(row, 4, new QStandardItem("1970-01-01"));

    // Фотографія не редагується
    const auto photo = new QStandardItem("нема фото");
    photo->setFlags(photo->flags() & ~Qt::ItemIsEditable);
    model->setItem(row, 5, photo);
}

//========================= Students::makePhotoName =======================
//  Формує ім’я файлу фото: Прізвище-Ім'я-Дата.jpg
//  Замінює пробіли, обрізає зайве. Використовується при збереженні фото.
//=========================================================================
QString Students::makePhotoName(const int row) const
{
    const QString last  = model->item(row, 1)->text().trimmed();
    const QString first = model->item(row, 2)->text().trimmed();
    const QString birth = model->item(row, 4)->text().trimmed();

    const QString safeLast  = last.simplified().replace(" ", "_");
    const QString safeFirst = first.simplified().replace(" ", "_");
    const QString safeBirth = birth.isEmpty() ? "unknown" : birth;

    return QString("%1-%2-%3.jpg")
            .arg(safeLast)
            .arg(safeFirst)
            .arg(safeBirth);
}

//======================= Students::onLoadPhotoClicked ====================
//  Обробник кнопки "Завантажити фото".
//  1. Вибирає файл
//  2. Генерує правильне ім'я
//  3. Копіює фото в директорію photos/
//  4. Записує шлях у таблицю
//  5. Малює фото у прев’ю
//=========================================================================
void Students::onLoadPhotoClicked()
{
    // 1. Перевіряємо, чи вибрано рядок
    const QModelIndex idx = ui->studentsTable->currentIndex();

    if (!idx.isValid()) {
        QMessageBox::warning(this,
                             "Рядок не обрано",
                             "Спочатку вибери рядок у таблиці студентів.");
        return;     // Без обраного рядка нічого не робимо
    }

    const int row = idx.row();

    // 2. Вибір фото
    const QString srcFile = QFileDialog::getOpenFileName(
            this,
            "Обрати фото",
            QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.bmp)"
    );

    // Користувач натиснув Скасовувати
    if (srcFile.isEmpty()) return;

    // 3. Перевіряємо, що каталог photos існує
    if (const QDir dir(photosDir); !dir.exists())
    {
        QMessageBox::warning(this, "Помилка",
                             "Тека photos не існує. Створіть її вручну.");
        return;
    }

    // 4. Створюємо назву фото Прізвище-Ім'я-Дата.jpg
    const QString finalFileName = makePhotoName(row);

    // 5. Повний шлях збереження
    const QString destPath = photosDir + "/" + finalFileName;

    // 6. Якщо файл із такою назвою вже існує — видаляємо
    QFile::remove(destPath);

    // 7. Копіюємо фото в директорію
    if (!QFile::copy(srcFile, destPath))
    {
        QMessageBox::warning(this, "Помилка", "Не вдалося скопіювати файл.");
        return;
    }

    // 8. Заносимо шлях до моделі (стовпець 'Фото')
    model->setItem(row, 5, new QStandardItem(destPath));

    // 7. Відображаємо фото
    renderPhoto(destPath);
}

//======================= Students::onDeleteClicked =======================
//  Обробник кнопки "Видалити".
//  1. Питає підтвердження
//  2. Видаляє запис з БД
//  3. Видаляє рядок з таблиці
//  4. Видаляє фото з файлової системи
//  5. Перемальовує прев’ю
//=========================================================================
void Students::onDeleteClicked()
{
    // 1. Має бути обраний рядок
    const QModelIndex idx = ui->studentsTable->currentIndex();
    if (!idx.isValid())
    {
        QMessageBox::warning(this, "Помилка", "Спочатку оберіть рядок.");
        return;
    }

    const int row = idx.row();

    // 2. Дістаємо ID
    const QString id = model->item(row, 0)->text().trimmed();
    if (id == "-" || id.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Цей запис ще не збережено у БД.");
        return;
    }

    // 3. Дістаємо імʼя та прізвище
    const QString last = model->item(row, 1)->text();
    const QString first = model->item(row, 2)->text();

    // 4. Підтвердження
    const QString msg =
        "Ви дійсно хочете видалити студента:\n" +
        first + " " + last + " ?";

    if (QMessageBox::question(this, "Підтвердження", msg)
        != QMessageBox::Yes)
    {
        return;
    }

    // 5. Перевіряємо БД
    if (!db.isOpen())
    {
        QMessageBox::critical(this, "Помилка", "Немає підключення до БД.");
        return;
    }

    // Зберегти photoPath ДО removeRow
    const QString photoPath = model->item(row, 5)->text();

    // 6. Готуємо delete
    QSqlQuery q(db);
    q.prepare("DELETE FROM students WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec())
    {
        QMessageBox::critical(this, "Помилка видалення", q.lastError().text());
        return;
    }

    // 7. Локально видаляємо рядок із таблиці
    model->removeRow(row);

    // 8. Якщо таблиця порожня - додаємо дефолтний рядок
    if (model->rowCount() == 0)
        insertDefaultRow(0);

    QMessageBox::information(this, "OK", "Запис видалено.");

    // 9. Видаляємо фото, з photoPath, взятого до removeRow
    if (!photoPath.isEmpty() && QFile::exists(photoPath))
        QFile::remove(photoPath);

    // Оновити фото
    renderPhoto("");
}

//============================= Students::skeleton ========================
//  Малює порожній світло-сірий прямокутник з текстом "Фото".
//  Використовується, якщо файл не існує або фото порожнє.
//=========================================================================
void Students::skeleton(QPainter& painter, const int w, const int h)
{
    // Колір рамки
    painter.setPen(Qt::darkGray);

    // Малюємо прямокутник по краю
    painter.drawRect(0, 0, w - 1, h - 1);

    // Пишемо текст по центру
    painter.drawText(QRect(0, 0, w, h), Qt::AlignCenter, "Фото");
}

//============================= Students::paintImage ======================
//  Малює зображення, масштабоване по розміру QLabel,
//  з вирівнюванням по центру та згладжуванням.
//=========================================================================
void Students::paintImage(QPainter& painter, const QPixmap& img, const int w, const int h)
{
    // Масштабуємо зображення із збереженням пропорцій,
    // але так, щоб покрити всю область QLabel.
    const QPixmap scaled = img.scaled(
        w, h,
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
    );

    // Обчислюємо зміщення для центрування
    const int x = (w - scaled.width()) / 2;
    const int y = (h - scaled.height()) / 2;

    // Малюємо результат
    painter.drawPixmap(x, y, scaled);
}

//============================ Students::renderPhoto =======================
//  Завантажує фото з диска та малює його у QLabel.
//  Якщо файл не існує - малює сірий "скелетон".
//  Якщо QLabel ще не має коректного розміру - відкладає рендер.
//=========================================================================
void Students::renderPhoto(const QString& path)
{
    // 1. Перевіряємо, чи файл існує
    const bool hasImage = (!path.isEmpty() && QFile::exists(path));

    // 2. Розміри області відображення
    const int w = ui->photoPreviewLabel->width();
    const int h = ui->photoPreviewLabel->height();

    // 3. Якщо Qt ще не виставив коректний розмір - відкладаємо рендер
    if (w < 50 || h < 50)
    {
        QTimer::singleShot(10, this, [this, path]() {
            renderPhoto(path);
        });
        return;
    }

    // 4. Створюємо порожнє полотно (віртуальне зображення), розміром як сам QLabel
    QPixmap canvas(w, h);
    // Заливаємо полотно світло-сірим кольором - це фон, на якому малюватиметься фото або рамка
    canvas.fill(Qt::lightGray);
    // Створюємо об’єкт художника, який малює на полотні (canvas)
    QPainter painter(&canvas);
    // Вмикаємо згладжування та якісне масштабування, щоб фото виглядало без "драбинок"
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // 5. Якщо фото існує — малюємо його
    if (hasImage)
    {
        // Якщо картинка не пошкоджена
        if (const QPixmap img(path); !img.isNull())
        {
            paintImage(painter, img, w, h);
        }
        else
        {
            // Якщо файл існує, але не відкривається - малюємо "скелетон"
            skeleton(painter, w, h);
        }
    }
    else
    {
        // 6. Фото відсутнє — рамка "Фото"
        skeleton(painter, w, h);
    }

    // 7. Встановлюємо результат у QLabel
    ui->photoPreviewLabel->setPixmap(canvas);
}

//============================ Students::resizeEvent =======================
//  Викликається при зміні розміру вікна.
//  Перемальовує фото з урахуванням нового розміру прев’ю.
//=========================================================================
void Students::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    if (const int row = ui->studentsTable->currentIndex().row(); row >= 0)
    {
        const QString path = model->item(row, 5)->text();
        renderPhoto(path);
    }
    else
    {
        renderPhoto("");
    }
}

//============================ Students::validateRow =======================
//  Перевіряє коректність введених даних у рядку моделі.
//  Вимагає: Прізвище, Ім’я. Інакше повертає false + текст помилки.
//=========================================================================
bool Students::validateRow(const int row, QString& error) const
{
    const QString last = model->item(row, 1)->text().trimmed();
    const QString first = model->item(row, 2)->text().trimmed();

    // Дата народження, фото, по-батькові не перевіряємо
    // const QString middle = model->item(row, 3)->text().trimmed();
    // const QString birth = model->item(row, 4)->text().trimmed();
    // const QString photo = model->item(row, 5)->text().trimmed();

    if (last.isEmpty() || last == "Прізвище")
    {
        error = "Поле 'Прізвище' не заповнене.";
        return false;
    }

    if (first.isEmpty() || first == "Ім'я")
    {
        error = "Поле 'Ім'я' не заповнене.";
        return false;
    }

    return true;
}

//=========================== Students::insertRowToDb =====================
//  INSERT нового студента в БД.
//  Повертає id через RETURNING id і записує в модель.
//=========================================================================
bool Students::insertRowToDb(const int row, QString& error) const
{
    QSqlQuery q(db);

    q.prepare(R"(
        INSERT INTO students (last_name, first_name, middle_name, birth_date, photo_path)
        VALUES (:ln, :fn, :mn, :bd, :pp)
        RETURNING id
    )");

    q.bindValue(":ln", model->item(row, 1)->text().trimmed());
    q.bindValue(":fn", model->item(row, 2)->text().trimmed());
    q.bindValue(":mn", model->item(row, 3)->text().trimmed());
    q.bindValue(":bd", model->item(row, 4)->text().trimmed());
    q.bindValue(":pp", model->item(row, 5)->text().trimmed());

    if (!q.exec())
    {
        error = q.lastError().text();
        return false;
    }

    if (q.next())
    {
        const QString newId = q.value(0).toString();
        model->setItem(row, 0, new QStandardItem(newId)); // ставимо новий id
    }

    return true;
}

//=========================== Students::updateRowInDb =====================
//  UPDATE існуючого запису студента.
//  Викликається, якщо id > 0 і не "-".
//=========================================================================
bool Students::updateRowInDb(const int row, QString& error) const
{
    QSqlQuery q(db);

    q.prepare(R"(
        UPDATE students
        SET last_name = :ln,
            first_name = :fn,
            middle_name = :mn,
            birth_date = :bd,
            photo_path = :pp
        WHERE id = :id
    )");

    q.bindValue(":ln", model->item(row, 1)->text().trimmed());
    q.bindValue(":fn", model->item(row, 2)->text().trimmed());
    q.bindValue(":mn", model->item(row, 3)->text().trimmed());
    q.bindValue(":bd", model->item(row, 4)->text().trimmed());
    q.bindValue(":pp", model->item(row, 5)->text().trimmed());
    q.bindValue(":id", model->item(row, 0)->text().trimmed());

    if (!q.exec())
    {
        error = q.lastError().text();
        return false;
    }

    return true;
}

//=========================== Students::onSaveClicked =====================
//  Обробник кнопки "Зберегти".
//  Проходить по всіх рядках моделі:
//  - валідація
//  - INSERT або UPDATE
//=========================================================================
void Students::onSaveClicked()
{
    if (!db.isOpen())
    {
        QMessageBox::critical(this, "Помилка", "Немає підключення до БД.");
        return;
    }

    for (int row = 0; row < model->rowCount(); row++)
    {
        QString err;

        // 1. Перевіряємо полях (окрім фото і дати)
        if (!validateRow(row, err))
        {
            QMessageBox::warning(this, "Помилка введення", err);
            return;
        }

        // 2. Визначаємо INSERT або UPDATE
        const QString id = model->item(row, 0)->text().trimmed();

        bool ok = false;
        if (id == "-" || id.isEmpty())
            ok = insertRowToDb(row, err);
        else
            ok = updateRowInDb(row, err);

        if (!ok)
        {
            QMessageBox::critical(this, "Помилка збереження", err);
            return;
        }
    }

    QMessageBox::information(this, "OK", "Усі зміни збережено.");
}

//========================== Students::connectDatabase ====================
//  Підключається до PostgreSQL через QPSQL.
//  Створює або отримує існуюче з’єднання.
//=========================================================================
bool Students::connectDatabase()
{
    if (!QSqlDatabase::isDriverAvailable("QPSQL")) {
        QMessageBox::critical(this, "Помилка",
                              "Драйвер PostgreSQL (QPSQL) недоступний.");
        return false;
    }

    // Уникаємо дублювання підключень
    if (QSqlDatabase::contains("main_connection"))
    {
        db = QSqlDatabase::database("main_connection");
    }
    else {
        db = QSqlDatabase::addDatabase("QPSQL", "main_connection");
    }

    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("app-db");
    db.setUserName("serg");
    db.setPassword("1234");

    if (!db.open())
    {
        QMessageBox::critical(
            this,
            "Помилка з’єднання",
            "Не вдалося підключитися до PostgreSQL:\n" + db.lastError().text()
        );
        return false;
    }

    return true;
}

//========================== Students::loadStudents =======================
//  SELECT * FROM students ORDER BY id.
//  Завантажує всі записи з бази в модель.
//  Для id та photo_path встановлюється "нередаговано".
//=========================================================================
void Students::loadStudents()
{
    if (!db.isOpen())
    {
        QMessageBox::warning(this, "Помилка", "Немає підключення до бази даних.");
        return;
    }

    QSqlQuery query(db);

    const auto sql = R"(
        SELECT
            id,
            last_name,
            first_name,
            middle_name,
            birth_date,
            photo_path
        FROM students
        ORDER BY id ASC
    )";

    if (!query.exec(sql))
    {
        QMessageBox::critical(this, "Помилка SELECT", query.lastError().text());
        return;
    }

    // Скидаємо модель
    model->removeRows(0, model->rowCount());

    int row = 0;
    while (query.next())
    {
        model->insertRow(row);

        // ID нередагований
        auto id = std::make_unique<QStandardItem>(query.value(0).toString());
        id->setFlags(id->flags() & ~Qt::ItemIsEditable);
        model->setItem(row, 0, id.release());

        model->setItem(row, 1, new QStandardItem(query.value(1).toString()));
        model->setItem(row, 2, new QStandardItem(query.value(2).toString()));
        model->setItem(row, 3, new QStandardItem(query.value(3).toString()));
        model->setItem(row, 4, new QStandardItem(query.value(4).toString()));

        // Фото нередаговане
        auto photo = std::make_unique<QStandardItem>(query.value(5).toString());
        photo->setFlags(photo->flags() & ~Qt::ItemIsEditable);
        model->setItem(row, 5, photo.release());

        row++;
    }

    if (row == 0)
    {
        // Якщо таблиця порожня створюємо дефолтний рядок
        insertDefaultRow(0);
    }
}
