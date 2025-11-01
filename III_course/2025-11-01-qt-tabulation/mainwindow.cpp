//
// Created by tysser on 01.11.25.
//

// III_course/2025-11-01-qt-tabulation/mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->comboFunc, &QComboBox::currentIndexChanged,
        this, &MainWindow::onFunctionChanged);

    setWindowTitle("Табулювання функції");

    // Наповнення комбобокса
    ui->comboFunc->addItem("sin(x)");
    ui->comboFunc->addItem("cos(x)");
    ui->comboFunc->addItem("x^2 + 2x + 1");

    // налаштування таблиці
    ui->tableXY->setColumnCount(2);
    ui->tableXY->setHorizontalHeaderLabels({"x", "y"});

    // Авто-ширина колонок
    ui->tableXY->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Висота рядків
    ui->tableXY->verticalHeader()->setDefaultSectionSize(25);

    // Сховати нумерацію рядків якщо не треба
    ui->tableXY->verticalHeader()->setVisible(false);

    // Заборонити редагування вручну
    ui->tableXY->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Мінімальний розмір таблиці
    ui->tableXY->setMinimumSize(250, 400);

    // Шапка (жирний текст, фон)
    ui->tableXY->horizontalHeader()->setStyleSheet(
    "QHeaderView::section {"
    "background-color: #f0f0f0;"
    "font-weight: bold;"
    "padding: 5px;"
    "}"
    );
}

void MainWindow::onFunctionChanged(int index) const
{
    const QString func = ui->comboFunc->currentText();

    if (func == "sin(x)") {
        ui->formulaLabel->setText("y = sin(x)");
    }
    else if (func == "cos(x)") {
        ui->formulaLabel->setText("y = cos(x)");
    }
    else if (func == "x^2 + 2x + 1") {
        ui->formulaLabel->setText("y = x<sup>2</sup> + 2x + 1");
    }
    else {
        ui->formulaLabel->setText("y = f(x)");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}


