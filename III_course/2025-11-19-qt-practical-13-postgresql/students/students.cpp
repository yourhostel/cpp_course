//
// Created by tysser on 19.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/students/students.cpp
#include "students.h"
#include "ui_students.h"

Students::Students(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Students)
{
    ui->setupUi(this);
}

Students::~Students()
{
    delete ui;
}
