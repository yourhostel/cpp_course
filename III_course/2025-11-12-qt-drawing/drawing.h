//
// Created by tysser on 12.11.25.
//

// III_course/2025-11-12-qt-drawing/drawing.h
#ifndef DRAWING_H
#define DRAWING_H

// Підключаємо базовий клас Qt-вікна.
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Drawing; }
QT_END_NAMESPACE

class Drawing final : public QMainWindow{
    // Макрос Qt, який вмикає механізм сигналів і слотів (MOC)
    // connect() та slots:
    Q_OBJECT

public:
    // Конструктор - створює вікно, підключає UI, сигнали
    explicit Drawing(QWidget *parent = nullptr);

    // Деструктор — прибирає UI
    ~Drawing() override;

private slots:
    //TODO slots

private:
    /**
     * Вказівник на автоматично згенерований UI-клас
     */
    Ui::Drawing *ui;
};

#endif //DRAWING_H
