#include <windows.h>
#include <iostream>

// ���������� ���������� ��� ���������� ��������
volatile bool run_thread_1 = true;
volatile bool run_thread_2 = true;
volatile bool run_thread_3 = true;

// ������� ��� ������� ������
DWORD WINAPI function_1(LPVOID lpParam) {
    while (run_thread_1) {
        std::cout << "\33[31m����� 1 ��������\33[0m\n";
        Sleep(1000);  // ����� �� 1 �������
    }
    return 0;
}

// ������� ��� ������� ������
DWORD WINAPI function_2(LPVOID lpParam) {
    while (run_thread_2) {
        std::cout << "\33[32m����� 2 ��������\33[0m\n";
        Sleep(3000);  // ����� �� 3 �������
    }
    return 0;
}

// ������� ��� �������� ������ (���������)
DWORD WINAPI function_3(LPVOID lpParam) {
    std::string input;
    while (run_thread_3) {
        std::cin >> input;
        if (input == "0") {
            std::cout << "\33[41m����� ��� ������� ������� ���������� ������ �������.\33[0m\n";
            Sleep(3000);  //����� ��� ���������� �������
            run_thread_1 = false;
            run_thread_2 = false;
            run_thread_3 = false;
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "");

    // �������� �������
    HANDLE hThread1 = CreateThread(NULL, 0, function_1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, function_2, NULL, 0, NULL);
    HANDLE hThread3 = CreateThread(NULL, 0, function_3, NULL, 0, NULL);

    // ������� �����
    while (run_thread_1 || run_thread_2 || run_thread_3) {
        std::cout << "������� ����� ��������\n";
        Sleep(4000);  // ����� �� 4 �������
    }

    // �������� ���������� �������
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);

    // �������� ������������ �������
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);

    Beep(1000, 500);
    std::cout << "\33[43m������ ������� ���������\33[0m";

    return 0;
}
