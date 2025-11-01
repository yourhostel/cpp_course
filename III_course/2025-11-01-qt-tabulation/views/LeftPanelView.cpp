//
// Created by tysser on 01.11.25.
//

// views/LeftPanelView.cpp
#include "LeftPanelView.h"
#include <Point.h>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QComboBox>
#include <QLabel>

void LeftPanelView::init(QComboBox *combo, QTableWidget *table)
{
    combo->addItem("sin(x)");
    combo->addItem("cos(x)");
    combo->addItem("x^2 + 2x + 1");

    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"x", "y"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setDefaultSectionSize(25);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setMinimumSize(250, 400);

    table->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "background-color: #f0f0f0;"
        "font-weight: bold;"
        "padding: 5px;"
        "}"
    );
}

void LeftPanelView::updateTable(QTableWidget *table, const std::vector<Point> &data)
{
    table->setRowCount(data.size());

    for (int i = 0; i < data.size(); i++) {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(data[i].x)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(data[i].y)));
    }
}

void LeftPanelView::updateFormula(const QComboBox *combo, QLabel *label)
{
    if (const QString func = combo->currentText(); func == "sin(x)") {
        label->setText("y = sin(x)");
    }
    else if (func == "cos(x)") {
        label->setText("y = cos(x)");
    }
    else if (func == "x^2 + 2x + 1") {
        label->setText("y = x<sup>2</sup> + 2x + 1");
    }
    else {
        label->setText("y = f(x)");
    }
}