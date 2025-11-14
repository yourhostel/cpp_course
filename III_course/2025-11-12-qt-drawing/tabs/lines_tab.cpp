//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/lines_tab.cpp
#include "lines_tab.h"

#include "../canvas/canvas.h"
#include "../widgets/analog_clock.h"

#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QWidget>

LinesTab::LinesTab(QWidget *uiRoot, Canvas *canvas)
    : QObject(uiRoot),
      uiRoot_(uiRoot),
      canvas_(canvas)
{
    canvas_->setCanvasSize(400, 400);

    // Кнопка Показати
    const auto btn = uiRoot_->findChild<QPushButton*>("btnShowLines");

    connect(btn, &QPushButton::clicked, [this]
    {
        drawLines();
    });

    // Додаємо годинник у lineTimerWidget
    timerWidget_ = uiRoot_->findChild<QWidget*>("lineTimerWidget");
    clock_ = AnalogClock::attachTo(timerWidget_);
}

void LinesTab::drawLines() const
{
    canvas_->clear();

    QPainter p(&canvas_->buffer());
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::white);

    constexpr int startX = 20;
    int y = 22;
    constexpr int step = 57;

    auto draw = [&](const Qt::PenStyle style) {
        const QPen pen(Qt::white, 3, style);
        p.setPen(pen);
        p.drawLine(startX, y, startX + 360, y);
        y += step;
    };

    draw(Qt::SolidLine);        // psSolid
    draw(Qt::DashLine);         // psDash
    draw(Qt::DotLine);          // psDot
    draw(Qt::DashDotLine);      // psDashDot
    draw(Qt::DashDotDotLine);   // psDashDotDot
    draw(Qt::NoPen);            // psClear
    draw(Qt::SolidLine);        // psInsideFrame - в Qt SolidLine

    canvas_->update();
}
