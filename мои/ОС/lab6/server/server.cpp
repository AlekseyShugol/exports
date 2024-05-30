#include <windows.h>
#include <iostream>
#include <string>

int main() {
    std::cerr << "THIS IS SERVER\n";
    HANDLE hNamedPipe = CreateNamedPipe(
        L"\\\\.\\pipe\\Messenger",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024,
        1024,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL);

    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateNamedPipe failed with error " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Waiting for client connection..." << std::endl;

    if (!ConnectNamedPipe(hNamedPipe, NULL)) {
        std::cerr << "ConnectNamedPipe failed with error " << GetLastError() << std::endl;
        CloseHandle(hNamedPipe);
        return 1;
    }

    std::cout << "Client connected. Waiting for message..." << std::endl;

    char buffer[1024];
    DWORD bytesRead;

    while (true) {
        if (ReadFile(hNamedPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            Beep(400, 700);
            std::cout << "Received message: \33[33m" << buffer << std::endl<<"\33[0m";

            std::string response;
            std::cout << "Enter your message: ";
            std::getline(std::cin, response);

            DWORD bytesWritten;
            WriteFile(hNamedPipe, response.c_str(), response.size(), &bytesWritten, NULL);
        }
    }

    DisconnectNamedPipe(hNamedPipe);
    CloseHandle(hNamedPipe);

    return 0;
}
