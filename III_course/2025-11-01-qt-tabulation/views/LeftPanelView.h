//
// Created by tysser on 01.11.25.
//

// views/LeftPanelView.h
#ifndef LEFTPANELVIEW_H
#define LEFTPANELVIEW_H

#include <QTableWidget>
#include <QComboBox>
#include <QLabel>

#include <vector>
#include <Point.h>

class QComboBox;

class LeftPanelView {
public:
    static void init(QComboBox *combo, QTableWidget *table);
    static void updateTable(QTableWidget *table, const std::vector<Point> &data);
    static void updateFormula(const QComboBox *combo, QLabel *label);
};

#endif // LEFTPANELVIEW_H
