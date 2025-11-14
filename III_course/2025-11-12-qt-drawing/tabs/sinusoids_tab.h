//
// Created by tysser on 14.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/sinusoids_tab.h
#ifndef CPP_COURSE_SINUSOIDS_TAB_H
#define CPP_COURSE_SINUSOIDS_TAB_H

#pragma once
#include <QObject>

class Canvas;
class QWidget;
class AnalogClock;

class SinusoidsTab final : public QObject {

    Q_OBJECT

public:
    SinusoidsTab(QWidget *uiRoot, Canvas *canvasPixel, Canvas *canvasPen);
    void drawSinusoids() const;

private:
    QWidget *uiRoot_;
    Canvas *canvasPixel_;
    Canvas *canvasPen_;

    QWidget *timerWidget_;
    AnalogClock *clock_;
};

#endif //CPP_COURSE_SINUSOIDS_TAB_H