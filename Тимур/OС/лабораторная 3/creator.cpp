// ���������-���������
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

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // ������ ��������� ��������
    if (!CreateProcess(NULL,   // ��� ������
        "child_process.exe",   // ��������� ������
        NULL,   // �������� ��������
        NULL,   // �������� ������
        TRUE,  // ������������ ������������
        0,      // ����� ��������
        NULL,   // ����� ���������� ���������
        NULL,   // ������� �������
        &si,    // ���������� � �������
        &pi)    // ���������� � ��������
        )
    {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return 1;
    }

    std::cout << "������� ������ �������� �������\n";

    // ����� ���������� ������������� �������� �� �������
    DWORD priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "��������� ������������� �������� �� �������: " << priorityClass << "\n";
    file << "��������� ������������� �������� �� �������: " << priorityClass << "\n";

    // ������������ �������
    file << "�������� ������������� ��������\n";

    // �������� ������������ �������� � ��������� ������
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // ����� ���������� ������������� �������� ����� �������
    priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "��������� ������������� �������� ����� �������: " << priorityClass << "\n";
    file << "��������� ������������� �������� �� �������: " << priorityClass << "\n";
    return 0;
}
