//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/canvas.cpp
#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    img_ = QImage(size(), QImage::Format_RGB32);
    img_.fill(Qt::black);
}

void Canvas::setCanvasSize(const int w, const int h)
{
    setMinimumSize(w, h);
    resize(w, h);

    img_ = QImage(w, h, QImage::Format_RGB32);
    img_.fill(Qt::black);

    update();
}

void Canvas::clear()
{
    img_.fill(Qt::black);
    update();
}

QImage& Canvas::buffer()
{
    return img_;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, img_);
}
