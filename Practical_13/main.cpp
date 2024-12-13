#include <iostream>
#include <windows.h>

using namespace std;
void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main()
{
    // setlocale(LC_ALL, "uk_UA"); // for my Linux system.
    setUtf8Encoding(); // for my Windows system.

    std::cout << "Привіт, Світе!" << std::endl;
    return 0;
}
