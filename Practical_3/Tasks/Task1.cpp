#include <iostream>
#include "console_utils.h" // ϳ�������� ���� ������� ���������

using namespace std;

// ������� ��� ������� �������� ����� �� ��������� �� ����
void processSum() {
    // ������������ ��������� ��� ��������
    setCyrillicEncoding();

    int num1, num2, num3;
    int sum;

    cout << "������ ����� �����: ";
    cin >> num1;

    cout << "������ ����� �����: ";
    cin >> num2;

    cout << "������ ���� �����: ";
    cin >> num3;

    sum = num1 + num2 + num3;

    cout << "���� �����: " << sum << endl;


    // ��������� ��������� �� UTF-8
    setUtf8Encoding();

}

int main() {
    // ��������� ������� �������
    processSum();

    return 0;

}

