//
// Created by tysser on 14.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/animation_tab.cpp
#include "animation_tab.h"

#include "../canvas/canvas.h"
#include "../widgets/analog_clock.h"

#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QtMath>

AnimationTab::AnimationTab(QWidget *uiRoot, Canvas *canvas)
    : QObject(uiRoot),
      uiRoot_(uiRoot),
      canvas_(canvas)
{
    canvas_->setCanvasSize(800, 400);

    // Кнопка Start/Stop
    const auto btn = uiRoot_->findChild<QPushButton*>("btnStartStop");

    connect(btn, &QPushButton::clicked, [this, btn]
    {
        running_ = !running_;

        if (running_) {
            btn->setText("Стоп");
            timer_->start(16);      // приблизно 60 FPS
        } else {
            btn->setText("Старт");
            timer_->stop();
        }
    });

    // Таймер анімації
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &AnimationTab::tick);

    // Годинник
    timerWidget_ = uiRoot_->findChild<QWidget*>("animationTimerWidget");
    clock_ = AnalogClock::attachTo(timerWidget_);
}

void AnimationTab::tick()
{
    canvas_->clear();
    QPainter p(&canvas_->buffer());
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::white, 2));

    const int w = canvas_->width();
    const int h = canvas_->height();

    // Земля
    p.drawLine(0, h - 160, w, h - 160);

    // Рух чоловічка
    t_ += 1;
    const int x = (t_ % (w + 50)) - 50;
    const int y = h - 160;

    // Кути анімації
    const double a = qSin(t_ * 0.15);      // руки
    const double b = qSin(t_ * 0.15 + 1.0); // ноги

    // Центр голови і радіус
    const QPoint c(x, y - 65);
    constexpr int r = 15;

    // Голова
    p.drawEllipse(c, r, r);

    // Капелюх
    constexpr int capW = r * 2;
    constexpr int capH = r + 3;

    const int capX = c.x() - capW / 2;
    const int capY = c.y() - r - 10;

    // Фігура Chord
    p.drawChord(capX, capY, capW, capH, 0 * 16, 180 * 16);

    // Козирок
    p.drawLine(c.x()+15, c.y() - r - 2, c.x() + 25, c.y() - r - 5);

    // Тулуб
    p.drawLine(x, y - 50, x, y - 20);

    // Руки
    p.drawLine(x, y - 45, x + 20 * a, y - 25);
    p.drawLine(x, y - 45, x - 20 * a, y - 25);

    // Ноги
    p.drawLine(x, y - 20, x + 20 * b, y);
    p.drawLine(x, y - 20, x - 20 * b, y);

    canvas_->update();
}

// Проста анімація кульки, що рухається по синусоїді
// void AnimationTab::tick()
// {
//     t_++;
//
//     canvas_->clear();
//     QPainter p(&canvas_->buffer());
//     p.setRenderHint(QPainter::Antialiasing);
//     p.setPen(Qt::white);
//     p.setBrush(Qt::white);
//
//     const int w = canvas_->width();
//     const int h = canvas_->height();
//
//     const double x = (t_ % w);
//     const double y = h/2 + qSin(t_ * 0.05) * (h/3);
//
//     p.drawEllipse(QPointF(x, y), 8, 8);
//
//     canvas_->update();
// }

