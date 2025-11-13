//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/lines_tab.h
#ifndef LINES_TAB_H
#define LINES_TAB_H

#include <QObject>

class QWidget;
class Canvas;
class AnalogClock;

class LinesTab final : public QObject {
    Q_OBJECT

public:
    LinesTab(QWidget *uiRoot, Canvas *canvas);

private:
    QWidget *uiRoot_;
    Canvas *canvas_;

    void drawLines() const;

    QWidget *timerWidget_ = nullptr;
    AnalogClock *clock_ = nullptr;
};

#endif //CPP_COURSE_LINES_TAB_H