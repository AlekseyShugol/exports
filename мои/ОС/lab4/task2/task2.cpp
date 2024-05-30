#include <windows.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Структура для передачи данных в поток
struct ThreadData {
    const std::vector<std::vector<int>>* arr;
    int start;
    int end;
    int target;
    int* counter;
};

// Функция потока для подсчета вхождений
DWORD WINAPI count_occurrences(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    std::cout << "Поток " << GetCurrentThreadId() << " обрабатывает строки с " << data->start << " по " << data->end << std::endl;
    for (int i = data->start; i < data->end; ++i) {
        for (int j = 0; j < data->arr->at(i).size(); ++j) {
            if (data->arr->at(i)[j] == data->target) {
                InterlockedIncrement((LONG*)data->counter); // Безопасное увеличение счетчика из разных потоков
            }
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    int M, N, K, target;
    std::cout << "Введите M, N, K и целевой элемент: ";
    std::cin >> M >> N >> K >> target;

    if (M < 0 || M > 10000 || N < 0 || N > 10000) {
        std::cout << "Недопустимое значение";
        return 1;
    }

    std::vector<std::vector<int>> arr(M, std::vector<int>(N, target));
    int counter = 0;

    std::vector<HANDLE> threads;
    int chunk_size = M / K;

    for (int i = 0; i < K; ++i) {
        int start = i * chunk_size;
        int end = (i == K - 1) ? M : start + chunk_size;

        ThreadData* data = new ThreadData{ &arr, start, end, target, &counter };
        DWORD threadID;
        HANDLE hThread = CreateThread(NULL, 0, count_occurrences, data, 0, &threadID); // Создание потока
        threads.push_back(hThread);
    }

    WaitForMultipleObjects(threads.size(), &threads[0], TRUE, INFINITE); // Ожидание завершения всех потоков

    for (HANDLE hThread : threads) {
        CloseHandle(hThread); // Закрытие дескрипторов потоков
    }

    std::cout << "Количество вхождений элемента " << target << ": " << counter << std::endl;

    return 0;
}
