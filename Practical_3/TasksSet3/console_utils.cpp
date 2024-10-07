// console_utils.cpp
#include "console_utils.h"

// Встановлює кодування CP1251 (кирилиця)
void setCyrillicEncoding() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// Встановлює кодування UTF-8
void setUtf8Encoding() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}