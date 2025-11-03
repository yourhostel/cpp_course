//
// Created by tysser on 03.11.25.
//

// III_course/2025-11-03-qt-gui-basics/exchange_form/mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct CurrencyRate {
    double buy = 0.0;
    double sale = 0.0;
};

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onDirectionClicked();
    void onBuySelected();
    void onSellSelected();
    void onConvertClicked() const;
    void onClearClicked() const;
    void onExitClicked();

    void onRatesLoaded(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    bool isBuyMode = true; // true = купівля (UAH -> VAL), false = продаж (VAL -> UAH)

    QNetworkAccessManager *networkManager;
    QMap<QString, CurrencyRate> rates; // EUR, USD…

    void updateDirectionUI() const;
    void requestRates() const;
    double currentRate() const;
};

#endif //MAINWINDOW_H
