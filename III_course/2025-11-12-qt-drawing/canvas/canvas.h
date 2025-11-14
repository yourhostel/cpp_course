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
    // Конструктор створює виджет і одразу робить внутрішній буфер QImage чорним.
    explicit Canvas(QWidget *parent = nullptr);

    // Стирає малюнок. Просто заливає буфер чорним і робить update().
    void clear();

    // Встановлює розмір канвасу і створює новий буфер QImage заданого розміру.
    void setCanvasSize(int w, int h);

    // Повертає внутрішній буфер, у який таби малюють через QPainter.
    QImage& buffer();

protected:
    // Малює внутрішній QImage на екран. Єдина точка рендеру.
    void paintEvent(QPaintEvent *event) override;

private:
    // Основний буфер. Все малювання йде сюди, а paintEvent показує його на екрані.
    QImage img_;
};

#endif //CANVAS_H
