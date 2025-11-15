//
// Created by tysser on 10.11.25.
//

// III_course/2025-11-15-qt-practical-11-tree-parser-2/calculation.cpp
#include "calculation.h"
#include "ui_calculation.h"
#include "expressiontree.h"
#include "parser.h"
#include <QMessageBox>

#include <QScreen>
#include <QGuiApplication>

Calculation::Calculation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculation)
{
    ui->setupUi(this);

    // повністю без рамки:
    setWindowFlags(Qt::FramelessWindowHint);

    // Центруємо по екрану
    const QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    connect(ui->btnCalculate, &QPushButton::clicked, this, &Calculation::onBtnCalculateClicked);
    connect(ui->btnExit, &QPushButton::clicked, this, &Calculation::onBtnExitClicked);
}

Calculation::~Calculation()
{
    delete ui;
}

void Calculation::onBtnCalculateClicked()
{
    try
    {

    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(this, "Помилка", // Чекаємо на помилки з parser.h
                             QString("Помилка під час обчислення:\n%1").arg(e.what()));
    }
}

void Calculation::onBtnExitClicked()
{
    close();
}
