//
// Created by tysser on 15.02.26.
//

#include "Components.h"

#include "ui_components.h"

#include "tabs/CounterTab.h"
#include "tabs/GridTab.h"

Components::Components(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Components)
{
    ui->setupUi(this);

    // Підключення логіки
    // Передаємо саму вкладку як контейнер
    // всередині якого Tab знайде всі віджети через findChild

    // Лічильник
    counterLogic = new CounterTab(ui->tab_counter);
    // таблиця
    gridLogic = new GridTab(ui->tab_grid);
}

Components::~Components()
{
    delete ui;
}
