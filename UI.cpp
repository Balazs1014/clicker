#include "UI.hpp"
#include <Windows.h>
#include <iostream>
#include <random>

UI::UI() {
    srand(time(nullptr));
    SetConsoleTitle((LPCWSTR)generateRandomTitle().c_str());
}

int UI::askForNumberInRange(int min, int max) const {
    int num;
    do {
        std::string inputStr;
        print("Enter a CPS between " + std::to_string(min) + " and " + std::to_string(max) + ": ");
        std::getline(std::cin, inputStr);
        try {
            num = std::stoi(inputStr);
            if (num < min || num > max) {
                showMessageBox("Number must be between " + std::to_string(min) + " and " + std::to_string(max) + ".");
            }
        }
        catch (...) {
            showMessageBox("Invalid input. Please enter a number.");
            num = min - 1; // Set num to a value outside the valid range to force the loop to continue.
        }
    } while (num < min || num > max);

    return num;
}

int UI::input() const {
    int result;
    std::cin >> result;
    return result;
}

void UI::printLogo() {
    setConsoleColor(14);
    std::cout << "  _________      ____        __      __ " << '\n';
    std::cout << " /   _____/     /  _ \\      /  \\    /  \\ " << '\n';
    std::cout << " \\_____  \\      >  _ </\\    \\   \\/\\/   / " << '\n';
    std::cout << " /        \\    /  <_\\ \\/     \\        /  " << '\n';
    std::cout << "/_______  /    \\_____\\ \\      \\__/\\  /   " << '\n';
    std::cout << "        \\/            \\/           \\/    " << '\n';
}

void UI::print(const std::string& text) const {
    std::cout << text;
}

void UI::showMessageBox(const std::string& text) const {
    MessageBox(NULL, (LPCWSTR)text.c_str(), L"[SW] Client", MB_OK);
}

void UI::clearConsole() const {
    system("cls");
}

void UI::setConsoleTextColor(int colorCode) const {
    setConsoleColor(colorCode);
}

void UI::setConsoleColor(int colorCode) const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

std::wstring UI::generateRandomTitle() const{
    std::string title = "";
    const int len = 10;
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<int> dist(0, chars.size() - 1);
    for (int i = 0; i < len; i++) {
        title += chars[dist(gen)];
    }
    // Convert the narrow character string to a wide character string
    int size = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, nullptr, 0);
    std::wstring wtitle(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, &wtitle[0], size);
    return wtitle;
}