// Программа-пользователь (child_process.cpp)
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

    // Вывод приоритета дочернего процесса до изменения
    DWORD priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "Приоритет дочернего процесса до изменения: " << priorityClass << "\n";
    file << "Приоритет родительского процесса до запуска: " << priorityClass << "\n";

    // Изменение приоритета дочернего процесса
    SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

    // Вывод приоритета дочернего процесса после изменения
    priorityClass = GetPriorityClass(GetCurrentProcess());
    std::cout << "Приоритет дочернего процесса после изменения: " << priorityClass << "\n";
    file << "Приоритет родительского процесса до запуска: " << priorityClass << "\n";

    // Дочерний процесс
    file << "Действия дочернего процесса\n";

    return 0;
}
