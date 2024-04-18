// ���������-������������ (child_process.cpp)
#include <windows.h>
#include <iostream>
#include <fstream>

int main() {
    setlocale(LC_ALL, "");
    std::ofstream file("log.txt", std::ios_base::app);
    if (!file) {
        std::cerr << "�� ������� ������� ����\n";
        return 1;
    }

    // ����� ���������� ��������� �������� �� ���������
    DWORD priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "��������� ��������� �������� �� ���������: " << priorityClass << "\n";
    file << "��������� ������������� �������� �� �������: " << priorityClass << "\n";

    // ��������� ���������� ��������� ��������
    SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

    // ����� ���������� ��������� �������� ����� ���������
    priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "��������� ��������� �������� ����� ���������: " << priorityClass << "\n";
    file << "��������� ������������� �������� �� �������: " << priorityClass << "\n";

    // �������� �������
    file << "�������� ��������� ��������\n";

    return 0;
}
