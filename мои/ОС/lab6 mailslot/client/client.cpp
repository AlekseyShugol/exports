#include <windows.h>
#include <iostream>
#include <string>

int main() {
    std::cerr << "CLIENT WINDOW\n_________________________________\n\n";
    HANDLE hMailslotReceive = CreateMailslot(
        L"\\\\.\\mailslot\\MailServer",
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL);

    HANDLE hMailslotSend = CreateFile(
        L"\\\\.\\mailslot\\MailClient",
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hMailslotReceive == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateMailslot failed with error with Reciever Handle " << GetLastError() << std::endl;
        return 1;
    }
    std::cerr << "\33[32mCONNECTION WITH SERVER WAS SUCSCESFULL\33[0m\n";

    if (hMailslotSend == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateFile failed with error with Sender Handle " << GetLastError() << std::endl;
        return 1;
    }

    while (true) {
        std::string message;
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);

        DWORD bytesWritten;
        if (!WriteFile(hMailslotSend, message.c_str(), message.size(), &bytesWritten, NULL)) {
            std::cerr << "WriteFile failed with error " << GetLastError() << std::endl;
            CloseHandle(hMailslotSend);
            return 1;
        }

        std::cout << "Message sent to server: " << message << std::endl;
       // std::cout << "Waiting for client message..." << std::endl;

        char buffer[1024];
        DWORD bytesRead;

        if (ReadFile(hMailslotReceive, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            std::cout << "Received message: " << buffer << std::endl;
        }
        
    }
    CloseHandle(hMailslotSend);
    return 0;
}
