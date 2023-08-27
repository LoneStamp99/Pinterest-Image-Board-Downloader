#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <cstdlib>

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void setConsoleIcon(const std::string& iconPath) {
    const char* path = iconPath.c_str();
    SendMessage(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL), path));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register a window class
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hIcon = (HICON)LoadImage(hInstance, "pinterest.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    // ... Rest of your code ...

    // Set console color
    setConsoleColor(FOREGROUND_RED);

    // Set console icon
    std::string iconPath = "pinterest.ico";
    setConsoleIcon(iconPath);

    std::string prompt = "Pinterest>> ";
    std::string command;

    while (true) {
        // Set console color for prompt
        setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN);

        std::cout << prompt;

        // Reset console color for user input
        setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

        std::getline(std::cin, command);

        // Exit if user enters "exit" command
        if (command == "exit") {
            break;
        }

        // Reset console color for command output
        setConsoleColor(FOREGROUND_GREEN);

        // Execute the command (you can replace this with your interaction with pinterest_downloader.py)
        std::string fullCommand = "python pinterest_downloader.py " + command;
        system(fullCommand.c_str());
    }

    return 0;
}
