#include <windows.h>
#include <iostream>
#include <vector>

#define N 10 // Количество дикарей
#define M 5 // Количество кусков тушеного миссионера в горшке

HANDLE semaphore; // Семафор для контроля доступа к горшку
HANDLE semaphore2;
HANDLE outputSemaphore; // Семафор для синхронизации вывода
int pot = M; // Горшок с тушеным миссионером
bool coockerAwake = false;//что бы повар в начале не ушел спать

DWORD WINAPI Savage(LPVOID lpParam) {
    while (true) {
        if (!coockerAwake) {


            WaitForSingleObject(semaphore, INFINITE); // Дикарь пытается взять кусок
            WaitForSingleObject(outputSemaphore, INFINITE); // Захватываем семафор для синхронизации вывода
            pot--; // Дикарь берет кусок
            std::cout << "Дикарь " << GetCurrentThreadId() << " взял кусок. Осталось:\t" << pot << std::endl;

            Sleep(1000); // Дикарь ест
            if (pot == 0) {
                ReleaseSemaphore(semaphore2, 1, NULL); // Повар добавляет куски в горшок
                WaitForSingleObject(semaphore2, INFINITE);

            }
            ReleaseSemaphore(outputSemaphore, 1, NULL); // Освобождаем семафор
        }

    }
    return 0;
}

DWORD WINAPI Cook(LPVOID lpParam) {
    while (true) {
        if (pot == 0) { // Если горшок пуст, повар его наполняет
            WaitForSingleObject(semaphore2, INFINITE);
            coockerAwake = true;
            WaitForSingleObject(outputSemaphore, INFINITE); // Захватываем семафор для синхронизации вывода
            pot = M;
            std::cout << "\33[32mПовар проснулся. Повар наполнил горшок.\33[0m" << std::endl;
            std::cout << "\33[31mПовар устал. Повар ушел спать.\33[0m\n";
            for (int i = 0; i < M; i++) {
                ReleaseSemaphore(semaphore, 1, NULL); // Повар добавляет куски в горшок
            }
            ReleaseSemaphore(outputSemaphore, 1, NULL); // Освобождаем семафор
        }
        ReleaseSemaphore(semaphore2, 1, NULL); // Повар добавляет куски в горшок
        Sleep(1000); // Повар отдыхает

    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "");
    semaphore = CreateSemaphore(NULL, M, M, NULL); // Создаем семафор с начальным количеством кусков
    outputSemaphore = CreateSemaphore(NULL, 1, 1, NULL); // Создаем семафор для синхронизации вывода
    semaphore2= CreateSemaphore(NULL, 0, 1, NULL);
    std::vector<HANDLE> savages(N);
    for (int i = 0; i < N; i++) {
        savages[i] = CreateThread(NULL, 0, Savage, NULL, 0, NULL); // Создаем дикарей
    }
    HANDLE cook = CreateThread(NULL, 0, Cook, NULL, 0, NULL); // Создаем повара
    WaitForMultipleObjects(N, &savages[0], TRUE, INFINITE); // Ждем, пока все дикареи закончат есть
    CloseHandle(cook);
    for (int i = 0; i < N; i++) {
        CloseHandle(savages[i]);
    }
    CloseHandle(semaphore);
    CloseHandle(outputSemaphore);
    return 0;
}
