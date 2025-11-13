//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/shapes_tab.h
#ifndef SHAPES_TAB_H
#define SHAPES_TAB_H

#include <QLabel>
#include <QObject>
#include <QPoint>

class QWidget;
class Canvas;
class AnalogClock;

// Клас логіки вкладки “Фігури”
class ShapesTab final : public QObject {

    Q_OBJECT

public:
    // uiRoot – це корінь UI вкладки (сам QWidget вкладки)
    // canvas – це канвас, який належить цій вкладці
    ShapesTab(QWidget *uiRoot, Canvas *canvas);

private:
    QWidget *uiRoot_; // зберігаємо доступ до UI вкладки
    Canvas *canvas_; // канвас, на якому будемо малювати

    // головна функція, яка малює всі фігури
    void drawShapes() const;

    QWidget *timerWidget_ = nullptr; // контейнер під годинник
    AnalogClock *clock_ = nullptr;   // годинник
};


#endif //SHAPES_TAB_H
