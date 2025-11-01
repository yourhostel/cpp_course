//
// Created by tysser on 01.11.25.
//

#include "ChartDrawer.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QPainter>
#include <cmath>

void ChartDrawer::init(QChartView *chartView)
{
    std::vector<Point> pts;
    for (double x = -10; x <= 10; x += 0.1)
        pts.push_back({x, std::sin(x)});

    updateChart(chartView, pts);
}

void ChartDrawer::updateChart(QChartView *chartView,
                              const std::vector<Point> &data)
{
    auto *chart  = new QChart();
    auto *series = new QLineSeries();

    for (const auto &p : data)
        series->append(p.x, p.y);

    chart->addSeries(series);

    auto *axisX = new QValueAxis();
    axisX->setTitleText("x");

    auto *axisY = new QValueAxis();
    axisY->setTitleText("y");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->setTitle("Графік функції");
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);
}



