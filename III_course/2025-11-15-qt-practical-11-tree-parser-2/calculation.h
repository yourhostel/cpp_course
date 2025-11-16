//
// Created by tysser on 10.11.25.
//

// III_course/2025-11-15-qt-practical-11-tree-parser-2/calculation.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Підключаємо базовий клас Qt-вікна.
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculation; }
QT_END_NAMESPACE

class Calculation final : public QMainWindow{
    // Макрос Qt, який вмикає механізм сигналів і слотів (MOC)
    // connect() та slots:
    Q_OBJECT

public:
    // Конструктор - створює вікно, підключає UI, сигнали
    explicit Calculation(QWidget *parent = nullptr);

    // Деструктор — прибирає UI
    ~Calculation() override;

private slots:
    void onBtnCalculateClicked();
    void onBtnExitClicked();

private:
    // Вказівник на автоматично згенерований UI-клас
    Ui::Calculation *ui{};
};

#endif //MAINWINDOW_H
