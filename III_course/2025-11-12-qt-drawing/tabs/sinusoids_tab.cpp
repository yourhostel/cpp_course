//
// Created by tysser on 14.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/sinusoids_tab.cpp
#include "sinusoids_tab.h"

#include "../canvas/canvas.h"
#include "../widgets/analog_clock.h"

#include <QPushButton>
#include <QPainter>
#include <QWidget>
#include <QtMath>

SinusoidsTab::SinusoidsTab(QWidget *uiRoot,
                           Canvas *canvasPixel,
                           Canvas *canvasPen)
    : QObject(uiRoot),
      uiRoot_(uiRoot),
      canvasPixel_(canvasPixel),
      canvasPen_(canvasPen)
{
    canvasPixel_->setCanvasSize(400, 400);
    canvasPen_->setCanvasSize(400, 400);

    // кнопка "Показати"
    const auto btn = uiRoot_->findChild<QPushButton*>("btnShowSinusoids");

    connect(btn, &QPushButton::clicked, [this]
    {
        drawSinusoids();
    });

    // Годинник у sinusoidsTimerWidget
    timerWidget_ = uiRoot_->findChild<QWidget*>("sinusoidsTimerWidget");
    clock_ = AnalogClock::attachTo(timerWidget_);
}

void SinusoidsTab::drawSinusoids() const
{
    canvasPixel_->clear();
    canvasPen_->clear();

    QPainter px(&canvasPixel_->buffer());
    QPainter pn(&canvasPen_->buffer());

    px.setPen(Qt::red);
    pn.setPen(Qt::green);

    const int w = canvasPixel_->width();
    const int h = canvasPixel_->height();

    constexpr double Pi = 3.14159;

    int prevX = 0;
    int prevY = h / 2;

    for (int PX = 0; PX <= w; PX++) {

        const double X = PX * 4.0 * Pi / w;
        const double Y = sin(X);

        const int PY = h - (Y + 1.0) * h / 2.0;

        // Піксельний графік
        px.drawPoint(PX, PY);

        // Ламана (аналог MoveTo/LineTo у Borland VCL-методи)
        if (PX > 0) {
            pn.drawLine(prevX, prevY, PX, PY);
        }

        prevX = PX;
        prevY = PY;
    }

    canvasPixel_->update();
    canvasPen_->update();
}
