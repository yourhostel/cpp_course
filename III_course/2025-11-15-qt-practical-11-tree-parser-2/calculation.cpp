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
        // 1. Зчитуємо вхідні дані
        const QString exprX = ui->mathModelTimeLineEdit->text();   // користувач ввів час x
        const QString exprF = ui->mathModelPathLineEdit->text();   // формула шляху f(x)

        if (exprX.trimmed().isEmpty())
            throw std::runtime_error("Не вказано значення часу");

        // заборонити символ 'x' у часі(x)
        if (exprX.contains('x', Qt::CaseInsensitive))
            throw std::runtime_error("У виразі часу не можна використовувати x");

        if (exprF.trimmed().isEmpty())
            throw std::runtime_error("Поле формули шляху порожнє");

        // TODO: розкоментувати для послідовної перевірки юнікоду введених рядків
        // {
        //     qDebug() << "===== час _exprX_ =======";
        //     for (int i = 0; i < exprX.size(); ++i)
        //     {
        //         QChar c = exprX[i];
        //         qDebug() << i << ":" << c << "unicode:" << c.unicode();
        //     }
        //     qDebug() << "=== f(x) _exprF_ ===";
        //     for (int i = 0; i < exprF.size(); ++i)
        //     {
        //         QChar c = exprF[i];
        //         qDebug() << i << ":" << c << "unicode:" << c.unicode();
        //     }
        //     qDebug() << "============";
        // }

        // 2. Парсимо час x
        const auto xExpr = parseExpression(exprX);

        // У виразі часу не може бути 'x', отже setVar не потрібен
        const double xValue = xExpr->result();

        // 3. Парсимо f(x), f'(x), f''(x)
        const auto f  = parseExpression(exprF);
        const auto f1 = f->differ();      // перша похідна
        const auto f2 = f1->differ();     // друга похідна

        // 4. Прокидаємо значення x по всьому дереву. Підставляємо x
        f->setVar(xValue);
        f1->setVar(xValue);
        f2->setVar(xValue);

        // 5. Обчислюємо значення
        const double pathValue  = f->result();   // f(x)
        const double speedValue = f1->result();  // f'(x)
        const double accValue   = f2->result();  // f''(x)

        // 6. Форматоване виведення, читаємо ComboBox
        const int accuracy = ui->accuracyComboBox->currentText().toInt();

        // Застосуємо значення з ComboBox для рівня точності
        ui->resultTimeLine->setText(QString::number(xValue,  'f', accuracy));
        ui->resultPathLine->setText(QString::number(pathValue,  'f', accuracy));
        ui->resultSpeedLine->setText(QString::number(speedValue, 'f', accuracy));
        ui->resultAccelerationLine->setText(QString::number(accValue, 'f', accuracy));
    }

    catch (const std::exception& e)
    {
        QMessageBox::warning(
      this,
     "Помилка",
        QString("Помилка під час обчислення:\n%1").arg(e.what())
        );
    }
}

void Calculation::onBtnExitClicked()
{
    close();
}
