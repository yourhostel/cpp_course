/*
    �������� 1:
    ������ � ��������� ��� ��� ����� � ������� �� ����� �������� �� ����.
*/

#include <iostream> // ϳ�������� �������� ��� ��������-���������
#include "console_utils.h" // ϳ�������� ���� ������� ���������

using namespace std;

int main() {
    int num1, num2, num3; // ��������� ��� ����� ��� ���������� �������� �����
    int sum; // ����� ��� ���������� ���� �����

    // ������������ ��������� ��� ��������
    setCyrillicEncoding();

    // ������� ����������� ������ ��� ��� �����
    cout << "������ ����� �����: ";
    cin >> num1; // ������� ����� �����

    cout << "������ ����� �����: ";
    cin >> num2; // ������� ����� �����

    cout << "������ ���� �����: ";
    cin >> num3; // ������� ���� �����

    // ���������� ���� ����� �����
    sum = num1 + num2 + num3;

    // �������� �� ����� ���� �����
    cout << "���� �����: " << sum << endl;

    setUtf8Encoding();

    return 0; // ��������� 0 ��� ���������� �������� ���������� ��������
}
