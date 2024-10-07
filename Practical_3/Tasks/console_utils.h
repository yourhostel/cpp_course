// console_utils.h
#pragma once
#include <windows.h> // Для функцій SetConsoleCP та SetConsoleOutputCP

// Функція для встановлення кодування CP1251 (кирилиця)
void setCyrillicEncoding();

// Функція для встановлення кодування UTF-8
void setUtf8Encoding();
