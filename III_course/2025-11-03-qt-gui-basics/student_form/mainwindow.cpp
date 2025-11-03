//
// Created by tysser on 03.11.25.
//

// III_course/2025-11-03-qt-gui-basics/student_form/mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Student Form");

    // Завантажуємо лого
    QPixmap logo(":/images/logo.png");
    // Масштабування картинки під розмір виджета
    logo = logo.scaled(ui->collegeLogoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // Встановлюємо картинку в QLabel
    ui->collegeLogoLabel->setPixmap(logo);

    // Завантажуємо фото
    m_photo1.load(":/images/photo1.png");
    m_photo2.load(":/images/photo2.png");
    m_photo3.load(":/images/photo3.png");

    // Початковий статус
    ui->photoLabel->clear();
    ui->labelStatusValue->setText("Фото не вибране");

    // Прив'язуємо кнопки

    // Qt6 стиль
    // connect(ui->btnPhoto1, &QPushButton::clicked, this, [this] {
    // setActivePhoto(1);
    // });

    // Qt5 стиль
    connect(ui->btnPhoto1, &QPushButton::clicked, this, &MainWindow::onPhoto1Clicked);
    connect(ui->btnPhoto2, &QPushButton::clicked, this, &MainWindow::onPhoto2Clicked);
    connect(ui->btnPhoto3, &QPushButton::clicked, this, &MainWindow::onPhoto3Clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setActivePhoto(int id)
{
    // Вибір картинки
    QPixmap pix;
    switch (id) {
    case 1: pix = m_photo1; break;
    case 2: pix = m_photo2; break;
    case 3: pix = m_photo3; break;
    default: return;
    }

    // Масштабування під розмір QLabel
    pix = pix.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Відображення
    ui->photoLabel->setPixmap(pix);

    // Оновлення статусу
    ui->labelStatusValue->setText(QString("Фото %1").arg(id));

    // Вимикаємо кнопку активного фото
    ui->btnPhoto1->setEnabled(id != 1);
    ui->btnPhoto2->setEnabled(id != 2);
    ui->btnPhoto3->setEnabled(id != 3);
}

// Слоти, на які підписані кнопки через connect(...)
// Вони передають конкретний номер фото у єдину функцію setActivePhoto(int id)
// одна логіка - багато тригерів
void MainWindow::onPhoto1Clicked() { setActivePhoto(1); }
void MainWindow::onPhoto2Clicked() { setActivePhoto(2); }
void MainWindow::onPhoto3Clicked() { setActivePhoto(3); }