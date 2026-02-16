//
// Created by tysser on 15.02.26.
//

#ifndef CPP_COURSE_COUNTERTAB_H
#define CPP_COURSE_COUNTERTAB_H


#include <QObject>

class QWidget;
class QPushButton;
class QLabel;

/*
 * CounterTab - логіка вкладки лічильника.
 * Не створює віджети, а працює з уже існуючими з .ui.
 */
class CounterTab : public QObject
{
    Q_OBJECT

public:
    explicit CounterTab(QWidget *container, QObject *parent = nullptr);

private slots:
    void onCounterClicked();
    void onResetClicked();

private:
    QPushButton *counterButton;
    QPushButton *resetButton;
    QLabel *counterLabel;

    int counterValue;

    void updateLabel();
};

#endif //CPP_COURSE_COUNTERTAB_H