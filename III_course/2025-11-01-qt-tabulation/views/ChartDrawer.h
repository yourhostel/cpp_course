//
// Created by tysser on 01.11.25.
//

// views/ChartDrawer.h
#ifndef CHARTDRAWER_H
#define CHARTDRAWER_H

#pragma once
#include <vector>
#include <QtCharts/QChartView>
#include "Point.h"

class ChartDrawer {
public:
    static void init(QChartView *chartView);
    static void updateChart(QChartView *chartView,
                            const std::vector<Point>& data);
};

#endif //CHARTDRAWER_H
