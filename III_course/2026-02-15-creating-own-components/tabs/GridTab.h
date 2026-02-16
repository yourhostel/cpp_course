//
// Created by tysser on 15.02.26.
//

#ifndef CPP_COURSE_GRIDTAB_H
#define CPP_COURSE_GRIDTAB_H


#include <QObject>

class QWidget;
class QTableWidget;
class QPushButton;
class QSpinBox;
class QLabel;
class QKeyEvent;

/*
 * GridTab це логіка вкладки таблиці.
 * Віджети не створює, бере з components.ui через container.
 * Insert заповнює випадковими 0..20.
 * Esc очищує.
 * Клік по комірці збільшує або зменшує шрифт.
 * SpinBox керують кількістю рядків та стовпців.
*/
class GridTab : public QObject
{
    Q_OBJECT

public:
    explicit GridTab(QWidget *container, QObject *parent = nullptr);

private slots:
    void fillRandomCells();
    void clearCells();
    void updateRowCount(int value);
    void updateColumnCount(int value);
    void toggleCellFont(int row, int column);

private:
    QWidget *container;

    QTableWidget *tableWidget;
    QPushButton  *fillButton;
    QPushButton  *clearButton;
    QSpinBox     *rowSpinBox;
    QSpinBox     *columnSpinBox;

    bool fontToggledFlag;
};

#endif //CPP_COURSE_GRIDTAB_H