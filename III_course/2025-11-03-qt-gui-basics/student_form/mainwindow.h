//
// Created by tysser on 03.11.25.
//

// III_course/2025-11-03-qt-gui-basics/student_form/mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Підключаємо базовий клас Qt-вікна і клас картинки.
#include <QMainWindow>
#include <QPixmap>

QT_BEGIN_NAMESPACE

// Оголошення класу головного вікна. Наслідуємось від QMainWindow, тому маємо:
// меню
// статусбар
// центральний віджет
// систему сигналів/слотів
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    // Макрос Qt, який вмикає механізм сигналів і слотів (MOC)
    // connect() та slots:
    Q_OBJECT

public:
    // Конструктор - створює вікно, підключає UI, сигнали, завантажує фото
    explicit MainWindow(QWidget *parent = nullptr);

    // Деструктор — прибирає UI
    ~MainWindow() override;

private slots:
    void onPhoto1Clicked();
    void onPhoto2Clicked();
    void onPhoto3Clicked();

private:
    // Вказівник на автоматично згенерований UI-клас
    Ui::MainWindow *ui;

    // Зображення, завантажені в пам’ять, щоб не читати файл кожного разу
    QPixmap m_photo1;
    QPixmap m_photo2;
    QPixmap m_photo3;

    // Логіка перемикання фото - встановлює картинку, міняє кнопки, статус
    void setActivePhoto(int id);
};

#endif //MAINWINDOW_H