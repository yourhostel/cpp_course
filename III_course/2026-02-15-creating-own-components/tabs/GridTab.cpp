//
// Created by tysser on 15.02.26.
//

#include "GridTab.h"

#include <QTableWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QShortcut>
#include <QFont>

GridTab::GridTab(QWidget *container, QObject *parent)
    : QObject(parent),
      container(container),
      tableWidget(nullptr),
      fillButton(nullptr),
      clearButton(nullptr),
      rowSpinBox(nullptr),
      columnSpinBox(nullptr),
      fontToggledFlag(true)
{
    // Якщо контейнер не переданий - нічого не робимо
    if (!this->container)
        return;

    // Отримуємо головне вікно для глобальних шорткатів
    auto *w = container->window();

    // Шорткат Insert заповнення таблиці по клавіші Insert
    auto *fillSc = new QShortcut(QKeySequence(Qt::Key_Insert), w);
    fillSc->setContext(Qt::WindowShortcut);
    connect(fillSc, &QShortcut::activated, this, &GridTab::fillRandomCells);

    // Шорткат Escape - очищення таблиці по клавіші Escape
    auto *clearSc = new QShortcut(QKeySequence(Qt::Key_Escape), w);
    clearSc->setContext(Qt::WindowShortcut);
    connect(clearSc, &QShortcut::activated, this, &GridTab::clearCells);

    // Пошук віджетів, створених у .ui
    tableWidget  = this->container->findChild<QTableWidget*>("tableWidget");
    fillButton   = this->container->findChild<QPushButton*>("fillButton");
    clearButton  = this->container->findChild<QPushButton*>("clearButton");
    rowSpinBox   = this->container->findChild<QSpinBox*>("rowSpinBox");
    columnSpinBox = this->container->findChild<QSpinBox*>("columnSpinBox");

    // Підключення кнопок
    if (fillButton)
        connect(fillButton, &QPushButton::clicked, this, &GridTab::fillRandomCells);

    if (clearButton)
        connect(clearButton, &QPushButton::clicked, this, &GridTab::clearCells);

    // Підключення зміни розмірності таблиці
    if (rowSpinBox)
        connect(rowSpinBox, &QSpinBox::valueChanged, this, &GridTab::updateRowCount);

    if (columnSpinBox)
        connect(columnSpinBox, &QSpinBox::valueChanged, this, &GridTab::updateColumnCount);

    // Підключення кліку по клітинці
    if (tableWidget)
        connect(tableWidget, &QTableWidget::cellClicked, this, &GridTab::toggleCellFont);

    // Налаштування таблиці
    this->container->setFocusPolicy(Qt::StrongFocus);

    if (tableWidget)
    {
        // Забороняємо редагування
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // Забороняємо виділення
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    }
}

void GridTab::fillRandomCells()
{
    if (!tableWidget)
        return;

    for (int r = 0; r < tableWidget->rowCount(); ++r)
    {
        for (int c = 0; c < tableWidget->columnCount(); ++c)
        {
            int value = QRandomGenerator::global()->bounded(21);

            QTableWidgetItem *item = tableWidget->item(r, c);
            if (!item)
            {
                item = new QTableWidgetItem;
                tableWidget->setItem(r, c, item);
            }

            item->setText(QString::number(value));
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void GridTab::clearCells()
{
    if (!tableWidget)
        return;

    for (int r = 0; r < tableWidget->rowCount(); ++r)
    {
        for (int c = 0; c < tableWidget->columnCount(); ++c)
        {
            QTableWidgetItem *item = tableWidget->item(r, c);
            if (!item)
            {
                item = new QTableWidgetItem;
                tableWidget->setItem(r, c, item);
            }

            item->setText(QString());
        }
    }
}

void GridTab::updateRowCount(int value)
{
    if (tableWidget)
        tableWidget->setRowCount(value);
}

void GridTab::updateColumnCount(int value)
{
    if (tableWidget)
        tableWidget->setColumnCount(value);
}

void GridTab::toggleCellFont(int row, int column)
{
    if (!tableWidget)
        return;

    QTableWidgetItem *item = tableWidget->item(row, column);
    if (!item)
        return;

    const int base = tableWidget->font().pointSize() > 0
                     ? tableWidget->font().pointSize()
                     : 10;

    QFont font = item->font();
    const int current = font.pointSize() > 0 ? font.pointSize() : base;

    font.setPointSize(current > base ? base : base * 2);
    item->setFont(font);
    item->setTextAlignment(Qt::AlignCenter);
}
