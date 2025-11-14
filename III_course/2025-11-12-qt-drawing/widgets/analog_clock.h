//
// Created by tysser on 13.11.25.
//

// III_course/widgets/analog_clock.h
#ifndef ANALOG_CLOCK_H
#define ANALOG_CLOCK_H

#pragma once
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QTime>

class AnalogClock final : public QWidget {

    Q_OBJECT

public:
    explicit AnalogClock(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        // Таймер, який кожну секунду викликає update().
        // Update() перезапускає paintEvent і перемальовує годинник
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
        timer->start(1000);
    }

    // Фабрика для швидкого прикріплення годинника до контейнера.
    // Створює об'єкт всередині контейнера і розтягує на весь його розмір.
    static AnalogClock* attachTo(QWidget *container, int minw = 120, int minh = 120)
    {
        if (!container) return nullptr;

        // Мінімальний розмір контейнера, щоб годинник не стискався в нуль.
        container->setMinimumSize(minw, minh);

        // Створення годинника в контейнері, геометрія 0 0 w h.
        auto *clk = new AnalogClock(container);
        clk->setGeometry(0, 0, container->width(), container->height());
        clk->show();

        return clk;
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        // Трикутники для годинникової та хвилинної стрілки.
        static constexpr QPoint hourHand[3] = {
            QPoint(7,8),
            QPoint(-7,8),
            QPoint(0,-40)
        };
        static constexpr QPoint minuteHand[3] = {
            QPoint(7,8),
            QPoint(-7,8),
            QPoint(0,-70)
        };

        // Кольори стрілок.
        constexpr QColor hourColor(127,0,127);
        constexpr QColor minuteColor(0,127,127);
        constexpr QColor secondColor(200,0,0);

        // Множник масштабу - підлаштовує малюнок під квадратну область.
        const int side = qMin(width(), height());

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // Переносимо початок координат у центр.
        p.translate(width() / 2, height() / 2);

        // Масштабуємо так, щоб годинник завжди займав 200x200 логічних одиниць.
        p.scale(side / 200.0, side / 200.0);

        const QTime time = QTime::currentTime();

        // Годинникова стрілка
        p.setPen(Qt::NoPen);
        p.setBrush(hourColor);
        p.save();

        // Кут годинникової стрілки з урахуванням хвилин.
        p.rotate(30.0 * (time.hour() + time.minute() / 60.0));
        p.drawConvexPolygon(hourHand, 3);
        p.restore();

        // Поділки годин
        p.setPen(hourColor);
        for (int i = 0; i < 12; i++)
        {
            p.drawLine(88, 0, 96, 0);
            p.rotate(30.0);
        }

        // Хвилинна стрілка
        p.setPen(Qt::NoPen);
        p.setBrush(minuteColor);
        p.save();
        p.rotate(6.0 * (time.minute() + time.second() / 60.0));
        p.drawConvexPolygon(minuteHand, 3);
        p.restore();

        // Поділки хвилин
        p.setPen(minuteColor);
        for (int j = 0; j < 60; j++)
        {
            if (j % 5 != 0)
                p.drawLine(92, 0, 96, 0);
            p.rotate(6.0);
        }

        // Секундна стрілка
        p.setPen(QPen(secondColor, 2));
        p.save();
        p.rotate(6.0 * time.second());
        p.drawLine(0, 0, 0, -90);
        p.restore();
    }
};

#endif //ANALOG_CLOCK_H
