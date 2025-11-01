//
// Created by tysser on 01.11.25.
//

// III_course/2025-11-01-qt-tabulation/mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT
    QChartView* m_chartView {};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

private slots:
    void onFunctionChanged(int index) const;
    void onTabulateClicked() const;
    void onClearOutput() const;
};

#endif // MAINWINDOW_H

