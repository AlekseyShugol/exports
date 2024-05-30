#include <windows.h>
#include <iostream>
#include <string>

int main() {
    HANDLE hNamedPipe = CreateFile(
        L"\\\\.\\pipe\\Messenger",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateFile failed with error " << GetLastError() << std::endl;
        return 1;
    }

    char buffer[1024];
    DWORD bytesRead;

    while (true) {
        std::string message;
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);

        DWORD bytesWritten;

        if (!WriteFile(hNamedPipe, message.c_str(), message.size(), &bytesWritten, NULL)) {
            std::cerr << "WriteFile failed with error " << GetLastError() << std::endl;
            CloseHandle(hNamedPipe);
            return 1;
        }

        if (ReadFile(hNamedPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            Beep(1000, 800);
            std::cout << "Received message: \33[33m" << buffer << std::endl << "\33[0m";
        }
    }

    CloseHandle(hNamedPipe);

    return 0;
}
