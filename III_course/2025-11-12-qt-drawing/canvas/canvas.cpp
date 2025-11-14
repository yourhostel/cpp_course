//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/canvas.cpp
#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    // Створюємо буфер з розміром поточного QWidget.
    // Це QImage, в який малюємо ВСІ фігури.
    img_ = QImage(size(), QImage::Format_RGB32);

    // Початкове заповнення чорним, бо у нас чорний фон.
    img_.fill(Qt::black);
}

void Canvas::setCanvasSize(const int w, const int h)
{
    // Встановлюємо мінімальний розмір щоб лейаути не зжимали канвас.
    setMinimumSize(w, h);

    // Фактичне встановлення розміру.
    resize(w, h);

    // Створюємо нове зображення-буфер з заданими розмірами.
    img_ = QImage(w, h, QImage::Format_RGB32);

    // Почорнюємо весь буфер.
    img_.fill(Qt::black);

    // Оновлюємо відображення на екрані.
    update();
}

void Canvas::clear()
{
    // Стираємо буфер (чорний фон).
    img_.fill(Qt::black);

    // Оновлюємо малюнок.
    update();
}

QImage& Canvas::buffer()
{
    // Повертаємо посилання на QImage,
    // в яке таби малюють через QPainter(&canvas->buffer()).
    return img_;
}

void Canvas::paintEvent(QPaintEvent *)
{
    // Малюємо буфер на сам QWidget.
    // Тобто QImage -> на екран.
    QPainter p(this);
    p.drawImage(0, 0, img_);
}
