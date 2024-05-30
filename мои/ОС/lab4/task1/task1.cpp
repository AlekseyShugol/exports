#include <windows.h>
#include <iostream>

// Глобальные переменные для управления потоками
volatile bool run_thread_1 = true;
volatile bool run_thread_2 = true;
volatile bool run_thread_3 = true;

// Функция для первого потока
DWORD WINAPI function_1(LPVOID lpParam) {
    while (run_thread_1) {
        std::cout << "\33[31mПоток 1 работает\33[0m\n";
        Sleep(1000);  // Пауза на 1 секунду
    }
    return 0;
}

// Функция для второго потока
DWORD WINAPI function_2(LPVOID lpParam) {
    while (run_thread_2) {
        std::cout << "\33[32mПоток 2 работает\33[0m\n";
        Sleep(3000);  // Пауза на 3 секунды
    }
    return 0;
}

// Функция для третьего потока (остановка)
DWORD WINAPI function_3(LPVOID lpParam) {
    std::string input;
    while (run_thread_3) {
        std::cin >> input;
        if (input == "0") {
            std::cout << "\33[41mПоток три получил команду завершения работы потоков.\33[0m\n";
            Sleep(3000);  //время для завершения потоков
            run_thread_1 = false;
            run_thread_2 = false;
            run_thread_3 = false;
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "");

    // Создание потоков
    HANDLE hThread1 = CreateThread(NULL, 0, function_1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, function_2, NULL, 0, NULL);
    HANDLE hThread3 = CreateThread(NULL, 0, function_3, NULL, 0, NULL);

    // Главный поток
    while (run_thread_1 || run_thread_2 || run_thread_3) {
        std::cout << "Главный поток работает\n";
        Sleep(4000);  // Пауза на 4 секунды
    }

    // Ожидание завершения потоков
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);

    // Закрытие дескрипторов потоков
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);

    Beep(1000, 500);
    std::cout << "\33[43mРабота потоков завершена\33[0m";

    return 0;
}
