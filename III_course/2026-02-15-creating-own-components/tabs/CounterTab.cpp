//
// Created by tysser on 15.02.26.
//

#include "CounterTab.h"

#include <QPushButton>
#include <QLabel>

CounterTab::CounterTab(QWidget *container, QObject *parent)
    : QObject(parent),
      counterButton(nullptr),
      resetButton(nullptr),
      counterLabel(nullptr),
      counterValue(0)
{
    if (!container)
        return;

    counterButton = container->findChild<QPushButton*>("counterButton");
    resetButton   = container->findChild<QPushButton*>("resetButton");
    counterLabel  = container->findChild<QLabel*>("counterLabel");

    if (counterLabel)
        counterValue = counterLabel->text().toInt();

    if (counterButton)
        connect(counterButton, &QPushButton::clicked,
                this, &CounterTab::onCounterClicked);

    if (resetButton)
        connect(resetButton, &QPushButton::clicked,
                this, &CounterTab::onResetClicked);

    updateLabel();
}

void CounterTab::onCounterClicked()
{
    ++counterValue;
    updateLabel();
}

void CounterTab::onResetClicked()
{
    counterValue = 0;
    updateLabel();
}

void CounterTab::updateLabel()
{
    if (counterLabel)
        counterLabel->setText(QString::number(counterValue));
}