//
// Created by tysser on 12.11.25.
//

// III_course/2025-11-12-qt-drawing/drawing.cpp

#include "drawing.h"
#include "ui_drawing.h"

Drawing::Drawing(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Drawing)
{
    ui->setupUi(this);


    // Тимчасовий фон
    setWindowTitle("Qt Drawing");
    resize(800, 600);
}

Drawing::~Drawing()
{
    delete ui;
}
