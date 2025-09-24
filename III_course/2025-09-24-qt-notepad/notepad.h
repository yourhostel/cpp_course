// # III_course/2025-09-24-qt-notepad/notepad.h
#pragma once
#include <QMainWindow>
#include <QTextEdit>

class Notepad : public QMainWindow {
    Q_OBJECT
public:
    Notepad();

private:
    QTextEdit *textEdit;
    void openFile();
    void saveFile();
};
