//
// Created by tysser on 12.11.25.
//

// III_course/2025-11-12-qt-drawing/drawing.h
#ifndef DRAWING_H
#define DRAWING_H

// Підключаємо базовий клас основного вікна Qt
#include <QMainWindow>

QT_BEGIN_NAMESPACE
// Ui::Drawing – це клас, який Qt Designer автоматично генерує з файла drawing.ui
namespace Ui { class Drawing; }
QT_END_NAMESPACE

// Drawing – головне вікно програми.
// Наслідуємо QMainWindow, щоб мати меню, статус-бар, центральний віджет і т.д.
class Drawing final : public QMainWindow {
    Q_OBJECT

public:
    explicit Drawing(QWidget *parent = nullptr); // створюємо вікно і піднімаємо UI
    ~Drawing() override;                         // прибираємо UI

private:
    Ui::Drawing *ui; // вказівник на згенерований клас інтерфейсу
};

#endif //DRAWING_H
