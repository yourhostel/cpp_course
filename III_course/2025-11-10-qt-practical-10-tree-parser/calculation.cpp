//
// Created by tysser on 10.11.25.
//

// III_course/2025-11-10-qt-practical-10-tree-parser/calculation.cpp
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

    // Підключення кнопок
    // ігноруємо попередження(“QAbstractButton::clicked is not a signal”) статичного аналізатора clazy
    // Сигнал clicked насправді існує саме в QAbstractButton, його декларація в qabstractbutton.h
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
        const QString xExpr = ui->lineX->text();
        const QString fExpr = ui->lineFx->text();

        // обчислення x
        const std::unique_ptr<Telement> xTree(parseExpression(xExpr));
        const double xValue = xTree->result(0); // x не використовується

        // обчислення f(x)
        const std::unique_ptr<Telement> fTree(parseExpression(fExpr));
        const double fValue = fTree->result(xValue);

        const int precision = ui->comboPrecision->currentText().toInt();

        ui->lineResultX->setText(QString::number(xValue, 'f', precision));
        ui->lineResultFx->setText(QString::number(fValue, 'f', precision));
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
