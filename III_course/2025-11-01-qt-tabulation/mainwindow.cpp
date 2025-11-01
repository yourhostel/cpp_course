//
// Created by tysser on 01.11.25.
//

// III_course/2025-11-01-qt-tabulation/mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "FunctionCalculator.h"
#include "FunctionController.h"
#include "TabulationController.h"
#include "LeftPanelView.h"
#include "ChartDrawer.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Спочатку створюємо UI
    ui->setupUi(this);

    // Конекти

    // Табулювання з кнопки
    connect(ui->btnTabulate, &QPushButton::clicked,
        this, &MainWindow::onTabulateClicked);

    // Табулювання з меню
    connect(ui->actionTabulate, &QAction::triggered,
        this, &MainWindow::onTabulateClicked);

    // Управління комбобокс (обрати функцію)
    connect(ui->comboFunc, &QComboBox::currentIndexChanged,
        this, &MainWindow::onFunctionChanged);

    // Скинути до дефолту таблицю поля та графік до дефолтного синусу
    connect(ui->actionClearOutput, &QAction::triggered,
        this, &MainWindow::onClearOutput);

    // Закрити вікно
    connect(ui->actionQuit, &QAction::triggered,
        this, &MainWindow::close);

    connect(ui->actionAbout, &QAction::triggered, this, [this]()
    {
        QMessageBox::about(this,
                           "Про програму",
                           "<b>Табуляція математичних функцій</b><br><br>"
                           "Програма дозволяє вибирати функцію, "
                           "задати інтервал та крок,<br>"
                           "побудувати таблицю значень і графік.<br><br>"
                           "Розробив: Тищенко Сергій<br>"
                           "Група: ALK-43<br>"
                           "2025"
        );
    });

    setWindowTitle("Табулювання функції");

    // Налаштування таблиці та комбобокса
    LeftPanelView::init(ui->comboFunc, ui->tableXY);

    // Ініціалізація чарту синусом
    m_chartView = new QChartView();
    ui->chartLayout->addWidget(m_chartView);
    ChartDrawer::init(m_chartView);
}

void MainWindow::onFunctionChanged(int) const
{
    LeftPanelView::updateFormula(ui->comboFunc, ui->formulaLabel);
}

void MainWindow::onTabulateClicked() const
{
    bool okA, okB, okH;

    const double a = ui->lineA->text().toDouble(&okA);
    const double b = ui->lineB->text().toDouble(&okB);
    const double h = ui->lineH->text().toDouble(&okH);

    if(!okA || !okB || !okH || h <= 0 || b <= a) {
        ui->formulaLabel->setText("Помилка вводу");
        return;
    }

    const auto f = FunctionController::getFunction(ui->comboFunc->currentText());

    const auto data = TabulationController::calculate(a, b, h, f);

    LeftPanelView::updateTable(ui->tableXY, data);
    ChartDrawer::updateChart(m_chartView, data);
}

void MainWindow::onClearOutput() const
{
    // Очистка полів
    ui->lineA->clear();
    ui->lineB->clear();
    ui->lineH->clear();

    // Очистка таблиці
    ui->tableXY->clearContents();
    ui->tableXY->setRowCount(0);

    // Повертаємо формулу у комбо
    ui->comboFunc->setCurrentIndex(0);
    LeftPanelView::updateFormula(ui->comboFunc, ui->formulaLabel);

    // Скидаємо графік на дефолт (sin)
    ChartDrawer::init(m_chartView);
}

MainWindow::~MainWindow() {
    delete ui;
}


