#include <windows.h>
#include <iostream>
using namespace std;
#define N 25
int a[N];//critical
HANDLE semaphore; // Семафор

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    int pause = 0;
    WaitForSingleObject(semaphore, INFINITE); // Захватываем семафор
    for (int i = 0; i < N; i++)
    {
        
        // замедляем вывод для наглядности
        for (long j = 0; j < 10000000; j++) pause++;
        cout << " \33[32m" << a[i] << "\33[0m";
        
    }
    ReleaseSemaphore(semaphore, 1, NULL); // Освобождаем семафор
    cout << endl;
    return 0;
}

int main(void)
{
    HANDLE Thread;
    DWORD ThreadID;
    int pause = 0;
    // заполняем глобальный массив
    for (int i = 0; i < N; i++) a[i] = i;
    semaphore = CreateSemaphore(NULL, 1, 1, NULL); // Создаем семафор
    Thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &ThreadID);
    if (Thread == NULL)
    {
        cerr << "Ошибка при создании потока" << endl;
        cin.get();
        return 0;
    }
    WaitForSingleObject(semaphore, INFINITE); // Захватываем семафор
    for (int i = 0; i < N; i++)
    {
        
        for (long j = 0; j < 10000000; j++) pause++;
        cout << " \33[31m" << a[i] << "\33[0m";
        
    }
    ReleaseSemaphore(semaphore, 1, NULL); // Освобождаем семафор
    cout << endl;
    // дожидаемся завершения работы потока
    WaitForSingleObject(Thread, INFINITE);
    CloseHandle(Thread);
    CloseHandle(semaphore); // Закрываем семафор
    return 0;
}
