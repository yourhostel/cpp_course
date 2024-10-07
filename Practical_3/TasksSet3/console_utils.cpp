// console_utils.cpp
#include "console_utils.h"

// ���������� ��������� CP1251 (��������)
void setCyrillicEncoding() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// ���������� ��������� UTF-8
void setUtf8Encoding() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}