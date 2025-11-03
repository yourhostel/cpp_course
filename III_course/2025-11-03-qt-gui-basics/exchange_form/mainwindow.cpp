//
// Created by tysser on 03.11.25.
//

// III_course/2025-11-03-qt-gui-basics/exchange_form/mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkRequest>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Exchange form");

    // Початковий стан
    isBuyMode = true;
    ui->radioBuy->setChecked(true);

    ui->lineRightAmount->setReadOnly(true);
    ui->lineRate->setReadOnly(true);

    // Підключення сигналів
    connect(ui->btnDirection, &QPushButton::clicked, this, &MainWindow::onDirectionClicked);
    connect(ui->radioBuy, &QRadioButton::clicked, this, &MainWindow::onBuySelected);
    connect(ui->radioSell, &QRadioButton::clicked, this, &MainWindow::onSellSelected);
    connect(ui->btnConvert, &QPushButton::clicked, this, &MainWindow::onConvertClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);

    // HTTP download ініціалізація і запит
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &MainWindow::onRatesLoaded);

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this] {
    updateDirectionUI();
    });

    requestRates();

    updateDirectionUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateDirectionUI() const
{
    if (isBuyMode) {
        ui->btnDirection->setText("→");
        ui->lineLeftAmount->setReadOnly(false);
        ui->lineRightAmount->setReadOnly(true);
    } else {
        ui->btnDirection->setText("←");
        ui->lineLeftAmount->setReadOnly(true);
        ui->lineRightAmount->setReadOnly(false);
    }

    ui->lineRate->setText(QString::number(currentRate(), 'f', 2));
}

void MainWindow::onDirectionClicked()
{
    isBuyMode = !isBuyMode;
    ui->radioBuy->setChecked(isBuyMode);
    ui->radioSell->setChecked(!isBuyMode);
    updateDirectionUI();
}

void MainWindow::onBuySelected()
{
    isBuyMode = true;
    updateDirectionUI();
}

void MainWindow::onSellSelected()
{
    isBuyMode = false;
    updateDirectionUI();
}

void MainWindow::onClearClicked() const
{
    ui->lineLeftAmount->clear();
    ui->lineRightAmount->clear();
}

void MainWindow::onExitClicked()
{
    close();
}

void MainWindow::onConvertClicked() const
{
    const double amountLeft  = ui->lineLeftAmount->text().toDouble();
    const double amountRight = ui->lineRightAmount->text().toDouble();
    const double rate = currentRate();

    if (rate <= 0) return;

    if (isBuyMode) {
        // Купівля: UAH → валюта
        const double result = amountLeft / rate;
        ui->lineRightAmount->setText(QString::number(result, 'f', 2));
    } else {
        // Продаж: валюта → UAH
        const double result = amountRight * rate;
        ui->lineLeftAmount->setText(QString::number(result, 'f', 2));
    }
}

// Функції запиту
void MainWindow::requestRates() const
{
    // Отримуємо дійсний курс з API приватбанку
    // у наступному форматі:
    // [{"ccy":"EUR","base_ccy":"UAH","buy":"47.80000","sale":"48.80000"},{"ccy":"USD","base_ccy":"UAH","buy":"41.47000","sale":"42.07000"}]
    const QUrl url("https://api.privatbank.ua/p24api/pubinfo?json&exchange&coursid=5");

    networkManager->get(QNetworkRequest(url));
}

// Обробка відповіді запиту
void MainWindow::onRatesLoaded(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(this, "Помилка", "Не вдалося отримати курси валют");
        reply->deleteLater();
        return;
    }

    const auto data = reply->readAll();
    reply->deleteLater();

    const QJsonDocument doc = QJsonDocument::fromJson(data);

    for (QJsonArray arr = doc.array(); auto v : arr) {
        QJsonObject obj = v.toObject();
        QString code = obj["ccy"].toString();
        CurrencyRate r;
        r.buy = obj["buy"].toString().toDouble();
        r.sale = obj["sale"].toString().toDouble();
        rates[code] = r;
    }

    // Заповнюємо валютний список
    ui->comboBox->clear();
    for (const auto& code : rates.keys())
        ui->comboBox->addItem(code);

    // Встановлюємо курс залежно від режиму
    ui->lineRate->setText(QString::number(currentRate(), 'f', 2));
}

// Отримання активного курсу
double MainWindow::currentRate() const
{
    const QString cur = ui->comboBox->currentText();
    if (!rates.contains(cur)) return 0.0;

    const auto & [buy, sale] = rates[cur];
    return isBuyMode ? buy : sale;
}

