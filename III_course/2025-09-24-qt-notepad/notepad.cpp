// # III_course/2025-09-24-qt-notepad/notepad.cpp
#include "notepad.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Notepad::Notepad() {
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    auto *fileMenu = menuBar()->addMenu("&File");
    QAction *openAct = fileMenu->addAction("&Open");
    QAction *saveAct = fileMenu->addAction("&Save");
    QAction *exitAct = fileMenu->addAction("E&xit");

    connect(openAct, &QAction::triggered, this, &Notepad::openFile);
    connect(saveAct, &QAction::triggered, this, &Notepad::saveFile);
    connect(exitAct, &QAction::triggered, this, &Notepad::close);

    resize(800, 600);
}

void Notepad::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }
    QTextStream in(&file);
    textEdit->setText(in.readAll());
}

void Notepad::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file");
        return;
    }
    QTextStream out(&file);
    out << textEdit->toPlainText();
}
