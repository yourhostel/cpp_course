//
// Created by tysser on 15.02.26.
//

#ifndef CPP_COURSE_COMPONENTS_H
#define CPP_COURSE_COMPONENTS_H

#include <QWidget>

class CounterTab;
class GridTab;

QT_BEGIN_NAMESPACE
namespace Ui { class Components; }
QT_END_NAMESPACE

class Components : public QWidget
{
    Q_OBJECT

public:
    explicit Components(QWidget *parent = nullptr);
    ~Components() override;

private:
    Ui::Components *ui;

    CounterTab *counterLogic;
    GridTab    *gridLogic;
};

#endif //CPP_COURSE_COMPONENTS_H