//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/shapes_tab.cpp
#include "shapes_tab.h"

#include <QLabel>

#include "../canvas/canvas.h"
#include "../widgets/analog_clock.h"

#include <QPushButton>
#include <QPainter>
#include <QTime>
#include <QWidget>

ShapesTab::ShapesTab(QWidget *uiRoot, Canvas *canvas)
    : QObject(uiRoot),   // QObject прив'язаний до uiRoot, щоб жити разом з вкладкою
      uiRoot_(uiRoot),   // зберігаємо вказівник на корінь UI вкладки
      canvas_(canvas)    // зберігаємо вказівник на канвас цієї вкладки
{
    // Потрібний розмір полотна для цієї вкладки
    canvas_->setCanvasSize(800, 400);

    // Кнопка "Показати"
    const auto btn = uiRoot_->findChild<QPushButton*>("btnShowShapes");

    connect(btn, &QPushButton::clicked, [this]
    {
        drawShapes();
    });

    // Додаємо годинник
    clock_ = AnalogClock::attachTo(uiRoot_->findChild<QWidget*>("shapesTimerWidget"));
}

void ShapesTab::drawShapes() const
{
    canvas_->clear();

    // Малюємо на внутрішньому буфері canvas
    QPainter p(&canvas_->buffer());

    // Увімкнути згладжування контурів
    p.setRenderHint(QPainter::Antialiasing, true);

    // Колір і шрифт для всіх фігур
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 11, QFont::Bold));

    // ---- ЛОГІКА СІТКИ ----
    // 4 стовпці × 2 рядки
    // Кожна комірка:
    // має свій верхній-лівий кут, від якого малюємо фігури
    // має однакову ширину і висоту
    constexpr int startX = 50;   // відступ зліва
    constexpr int startY = 50;   // відступ зверху
    constexpr int cellW  = 180;  // ширина однієї комірки
    constexpr int cellH  = 200;  // висота однієї комірки

    // Обчислює верхній-лівий кут комірки
    auto cell = [&](const int col, const int row)
    {
        return QPoint(startX + col * cellW,
                      startY + row * cellH);
    };

    // ============================================
    //  Перший ряд фігур (Arc, Chord, Ellipse, Pie)
    // ============================================

    // Arc
    {
        constexpr QPoint c = cell(0, 0);
        p.drawArc(c.x(), c.y(), 120, 90, 0 * 16, 180 * 16);
        p.drawText(c.x() + 45, c.y() + 105, "Arc");
    }

    // Chord
    {
        constexpr QPoint c = cell(1, 0);
        p.drawChord(c.x(), c.y(), 120, 90, 0 * 16, 180 * 16);
        p.drawText(c.x() + 40, c.y() + 105, "Chord");
    }

    // Ellipse
    {
        constexpr QPoint c = cell(2, 0);
        p.drawEllipse(c.x() + 10, c.y() + 20, 110, 55);
        p.drawText(c.x() + 40, c.y() + 105, "Ellipse");
    }

    // Pie
    {
        constexpr QPoint c = cell(3, 0);
        p.drawPie(c.x(), c.y(), 120, 90, 30 * 16, 120 * 16);
        p.drawText(c.x() + 45, c.y() + 105, "Pie");
    }

    // ===========================================================
    //  Другий ряд фігур (Polygon, Polyline, Rectangle, RoundRect)
    // ===========================================================

    // Polygon
    {
        constexpr QPoint c = cell(0, 1);
        const QVector<QPoint> poly {
            {c.x() + 30, c.y() + 60},
            {c.x() + 50, c.y() + 30},
            {c.x() + 70, c.y() + 50},
            {c.x() + 90, c.y() + 30},
            {c.x() + 110, c.y() + 60},
        };
        p.drawPolygon(poly);
        p.drawText(c.x() + 35, c.y() + 85, "Polygon");
    }

    // Polyline
    {
        constexpr QPoint c = cell(1, 1);
        const QVector<QPoint> poly {
            {c.x() + 30, c.y() + 60},
            {c.x() + 50, c.y() + 30},
            {c.x() + 70, c.y() + 50},
            {c.x() + 90, c.y() + 30},
            {c.x() + 110, c.y() + 60},
        };
        p.drawPolyline(poly);
        p.drawText(c.x() + 35, c.y() + 85, "Polyline");
    }

    // Rectangle
    {
        constexpr QPoint c = cell(2, 1);
        p.drawRect(c.x() + 40, c.y() + 25, 60, 50);
        p.drawText(c.x() + 30, c.y() + 90, "Rectangle");
    }

    // RoundRect
    {
        constexpr QPoint c = cell(3, 1);
        p.drawRoundedRect(c.x() + 40, c.y() + 25, 60, 50, 20, 20);
        p.drawText(c.x() + 28, c.y() + 90, "RoundRect");
    }

    canvas_->update();
}

