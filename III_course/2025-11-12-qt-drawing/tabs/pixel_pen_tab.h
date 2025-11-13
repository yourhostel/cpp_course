//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/pixel_pen_tab.h
#ifndef PIXEL_PEN_TAB_H
#define PIXEL_PEN_TAB_H

#include <QObject>
#include <QPoint>

#include "analog_clock.h"

class QWidget;
class Canvas;

class PixelPenTab final : public QObject {
    Q_OBJECT

public:
    PixelPenTab(QWidget *uiRoot, Canvas *canvas);

private:
    QWidget *uiRoot_;
    Canvas *canvas_;

    // Режим роботи: false - точки, true - відрізки
    bool drawLines_ = false;

    // Для режиму точок, показує чи кнопка миші зараз затиснута
    bool drawing_ = false;

    // Для режиму ліній (PEN)
    QPoint last_;                 // попередня точка
    bool hasLast_ = false;        // чи є попередня точка

    // Перехоплюємо події миші з Canvas
    bool eventFilter(QObject *obj, QEvent *ev) override;

    // Логіка малювання точками
    void handlePixelPress(const QPoint &p);
    void handlePixelMove(const QPoint &p) const;

    // Логіка малювання відрізками
    void handlePenClick(const QPoint &p);

    // Малювання астроїди кнопками
    void drawAstroidPixels();
    void drawAstroidPen();

    // Контейнер під годинник та годинник
    QWidget *timerWidget_ = nullptr;
    AnalogClock *clock_ = nullptr;
};

#endif //PIXEL_PEN_TAB_H
