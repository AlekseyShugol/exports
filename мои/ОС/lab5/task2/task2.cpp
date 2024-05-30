#include <windows.h>
#include <iostream>
using namespace std;
#define N 25
int a[N];//critical
HANDLE mutex; // Мьютекс

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    WaitForSingleObject(mutex, INFINITE); // Захватываем мьютекс
    int pause = 0;
    for (int i = 0; i < N; i++)
    {
      
        // замедляем вывод для наглядности
        for (long j = 0; j < 1000000; j++) pause++;
        cout << " \33[32m" << a[i] << "\33[0m";
        
    }
    ReleaseMutex(mutex); // Освобождаем мьютекс
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
    mutex = CreateMutex(NULL, FALSE, NULL); // Создаем мьютекс
    Thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &ThreadID);
    if (Thread == NULL)
    {
        cerr << "Ошибка при создании потока" << endl;
        cin.get();
        return 0;
    }
    WaitForSingleObject(mutex, INFINITE);
    for (int i = 0; i < N; i++)
    {
       
        for (long j = 0; j < 1000000; j++) pause++;
        cout << " \33[31m" << a[i] << "\33[0m";
      ; // Освобождаем мьютекс
    }
    ReleaseMutex(mutex);
    cout << endl;
    // дожидаемся завершения работы потока
    WaitForSingleObject(Thread, INFINITE);
    CloseHandle(Thread);
    CloseHandle(mutex); // Закрываем мьютекс
    return 0;
}
