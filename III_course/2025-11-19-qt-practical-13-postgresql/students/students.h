//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/students/students.h
#ifndef CPP_COURSE_STUDENTS_H
#define CPP_COURSE_STUDENTS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class Students; }
QT_END_NAMESPACE

class Students final : public QMainWindow
{
    Q_OBJECT

public:
    // Створює форму, ініціалізує модель, підключає сигнали
    explicit Students(QWidget *parent = nullptr);

    // Звільняє UI та модель
    ~Students() override;

    // Реакція на зміну активного рядка таблиці (оновлення фото)
    void onRowChanged(const QModelIndex& current,
                      const QModelIndex& previous);

private:
    Ui::Students* ui = nullptr;

    // Модель таблиці студентів
    QStandardItemModel* model = nullptr;

    // Каталог зі збереженими фотографіями
    QString photosDir =
        "/home/tysser/Scripts/jetbrains/cpp_course/III_course/"
        "2025-11-19-qt-practical-13-postgresql/students/photos";

    // Малює фото або сіру заглушку в QLabel
    void renderPhoto(const QString& path);

    // При зміні розміру оновлюємо прев’ю фото
    void resizeEvent(QResizeEvent* event) override;

    // Створення моделі й заголовків
    void setupTableModel();

    // Налаштування вигляду таблиці
    void setupTableView() const;

    // Перевіряє коректність введених даних у рядку моделі
    bool validateRow(int row, QString& error) const;

    // Додає нового студента до БД (INSERT)
    bool insertRowToDb(int row, QString& error) const;

    // Оновлює існуючого студента (UPDATE)
    bool updateRowInDb(int row, QString& error) const;

    // Додає дефолтний рядок у таблицю
    void insertDefaultRow(int row) const;

    // Формує ім’я файлу фото: Прізвище-Ім'я-Дата.jpg
    QString makePhotoName(int row) const;

    // Перевіряє, чи останній рядок
    bool lastRowIsDefault() const;

    // Малює сірий прямокутник з написом "Фото"
    static void skeleton(QPainter& painter, int w, int h);

    // Малює зображення, центроване та масштабоване під область
    static void paintImage(QPainter& painter, const QPixmap& img,int w, int h);

    // Об'єкт підключення до PostgreSQL
    QSqlDatabase db;

    // Встановлює підключення до бази даних
    bool connectDatabase();

    // Завантажує всі записи з таблиці students у модель
    void loadStudents();

private slots:
    // Кнопка: завантажити фото
    void onLoadPhotoClicked();

    // Кнопка: видалити обраного студента
    void onDeleteClicked();

    // Кнопка: зберегти всі зміни в БД
    void onSaveClicked();
};

#endif //CPP_COURSE_STUDENTS_H