//
// Created by tysser on 14.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/animation_tab.h
#ifndef CPP_COURSE_ANIMATION_TAB_H
#define CPP_COURSE_ANIMATION_TAB_H

#include <QObject>
#include <QPoint>

class QWidget;
class Canvas;
class QTimer;
class AnalogClock;

class AnimationTab final : public QObject {

    Q_OBJECT

public:
    AnimationTab(QWidget *uiRoot, Canvas *canvas);

private slots:
    void tick();    // один крок анімації

private:
    QWidget *uiRoot_;
    Canvas *canvas_;

    QWidget *timerWidget_ = nullptr;
    AnalogClock *clock_ = nullptr;

    QTimer *timer_ = nullptr;
    bool running_ = false;     // стан анімації

    int t_ = 0;                // поточний кадр
};

#endif //CPP_COURSE_ANIMATION_TAB_H