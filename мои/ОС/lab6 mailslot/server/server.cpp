#include <windows.h>
#include <iostream>
#include <string>

int main() {
    std::cerr << "SERVER WINDOW\n_________________________________\n\n";
    HANDLE hMailslotReceive = CreateMailslot(
        L"\\\\.\\mailslot\\MailClient",
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL);
    std::cerr << "Waiting to connecting with Client Mail...\n";
    Sleep(500);
    std::cerr << "\33[32mCONNECTON WITH CLIENT WAS SUCCESSFULL\33[0m\n";
    Beep(800, 2000);
   //system("pause");
    HANDLE hMailslotSend = CreateFile(
        L"\\\\.\\mailslot\\MailServer",
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

    if (hMailslotSend == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateFile failed with error Sender Handle " << GetLastError() << std::endl;
        return 1;
    }

    while (true) {
        
        std::cout << "Waiting for client message..." << std::endl;

        char buffer[1024];
        DWORD bytesRead;

        if (ReadFile(hMailslotReceive, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            std::cout << "Received message: " << buffer << std::endl;
        }
        std::string message;
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);

        DWORD bytesWritten;
        if (!WriteFile(hMailslotSend, message.c_str(), message.size(), &bytesWritten, NULL)) {
            std::cerr << "WriteFile failed with error " << GetLastError() << std::endl;
            CloseHandle(hMailslotSend);
            return 1;
        }
    }

    return 0;
}
