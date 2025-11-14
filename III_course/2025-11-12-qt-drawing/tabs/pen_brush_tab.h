//
// Created by tysser on 14.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/pen_brush_tab.h
#ifndef CPP_COURSE_PEN_BRUSH_TAB_H
#define CPP_COURSE_PEN_BRUSH_TAB_H

#include <QObject>
#include <QPainter>

class QWidget;
class Canvas;
class AnalogClock;
class QMouseEvent;

class PenBrushTab final : public QObject {

    Q_OBJECT

public:
    PenBrushTab(QWidget *uiRoot, Canvas *canvas);

private:
    QWidget *uiRoot_;
    Canvas  *canvas_;

    QWidget *timerWidget_ = nullptr;
    AnalogClock *clock_ = nullptr;

    // Застосування вибраних стилів
    void applyBrushStyle(QPainter &p) const;
    void applyPenMode(QPainter &p) const;

    // Подія миші через eventFilter
    bool eventFilter(QObject *obj, QEvent *event) override;

    // Обробка малювання по кліку
    void handleClick(const QPoint &pos) const;
};


#endif //CPP_COURSE_PEN_BRUSH_TAB_H