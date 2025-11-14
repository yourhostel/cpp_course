//
// Created by tysser on 12.11.25.
//

// III_course/2025-11-12-qt-drawing/drawing.cpp
#include "drawing.h"

#include <QScreen>

#include "ui_drawing.h"
#include "tabs/animation_tab.h"
#include "tabs/lines_tab.h"
#include "tabs/pixel_pen_tab.h"
#include "tabs/shapes_tab.h"
#include "tabs/sinusoids_tab.h"

Drawing::Drawing(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Drawing)
{
    ui->setupUi(this);

    // Центруємо вікно на екрані
    // screen – об’єкт, який містить інформацію про основний монітор
    const QScreen *screen = QApplication::primaryScreen();

    // screenGeometry – реальні кордони області екрана, де можна розміщувати вікна
    const QRect screenGeometry = screen->availableGeometry();

    // move(...) – фізично переносимо вікно у центр:
    // беремо розмір екрана, віднімаємо розмір вікна і ділимо на 2
    move(
        (screenGeometry.width()  - width())  / 2,
        (screenGeometry.height() - height()) / 2
    );

    // Встановлюємо вкладку за замовчуванням.
    // 0 – це PixelPenTab (перша вкладка)
    ui->tabWidget->setCurrentIndex(0);

    // Підключаємо кнопку виходу
    connect(ui->btnExit, &QPushButton::clicked, this, &QWidget::close);

    // Ініціалізуємо логіку вкладки Pixel/Pen.
    // Передаємо корінь її UI (this) і канвас drawArea
    new PixelPenTab(this, ui->drawArea);

    // Ініціалізуємо логіку вкладки Shapes.
    // Передаємо QWidget вкладки і її окремий канвас drawAreaShapes
    new ShapesTab(ui->tabShapes, ui->drawAreaShapes);

    new LinesTab(ui->tabLineStyles, ui->drawAreaLines);

    new SinusoidsTab(ui->tabSinusoids, ui->drawAreaPen, ui->drawAreaPixel);

    new AnimationTab(ui->tabAnimation, ui->drawAreaAnimation);
}

Drawing::~Drawing()
{
    delete ui;
}
