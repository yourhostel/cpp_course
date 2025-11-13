//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/canvas.h
#ifndef CANVAS_H
#define CANVAS_H

#pragma once
#include <QWidget>
#include <QImage>

class Canvas final : public QWidget {
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    void clear();
    void setCanvasSize(int w, int h);

    QImage& buffer();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage img_;
};

#endif //CANVAS_H
