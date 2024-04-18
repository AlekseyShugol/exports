// Программа-создатель
#include <windows.h>
#include <iostream>
#include <fstream>

int main() {
    setlocale(LC_ALL, "");
    std::ofstream file("log.txt", std::ios_base::app);
    if (!file) {
        std::cerr << "Не удалось открыть файл\n";
        return 1;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Запуск дочернего процесса
    if (!CreateProcess(NULL,   // имя модуля
        "child_process.exe",   // командная строка
        NULL,   // атрибуты процесса
        NULL,   // атрибуты потока
        TRUE,  // наследование дескрипторов
        0,      // флаги создания
        NULL,   // новые переменные окружения
        NULL,   // текущий каталог
        &si,    // информация о запуске
        &pi)    // информация о процессе
        )
    {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return 1;
    }

    std::cout << "Успешно создан дочерний процесс\n";

    // Вывод приоритета родительского процесса до запуска
    DWORD priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "Приоритет родительского процесса до запуска: " << priorityClass << "\n";
    file << "Приоритет родительского процесса до запуска: " << priorityClass << "\n";

    // Родительский процесс
    file << "Действия родительского процесса\n";

    // Закрытие дескрипторов процесса и основного потока
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Вывод приоритета родительского процесса после запуска
    priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "Приоритет родительского процесса после запуска: " << priorityClass << "\n";
    file << "Приоритет родительского процесса до запуска: " << priorityClass << "\n";
    return 0;
}
