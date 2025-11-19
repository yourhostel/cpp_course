//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/students/students.h
#ifndef CPP_COURSE_STUDENTS_H
#define CPP_COURSE_STUDENTS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Students; }
QT_END_NAMESPACE

class Students final : public QMainWindow
{
    Q_OBJECT

public:
    explicit Students(QWidget *parent = nullptr);
    ~Students() override;

private:
    Ui::Students *ui;
};

#endif //CPP_COURSE_STUDENTS_H