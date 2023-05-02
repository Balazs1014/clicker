#pragma once

#include <string>

class UI
{
public:
    UI();
    void printLogo();
    void print(const std::string& text) const;
    void showMessageBox(const std::string& text) const;
    void clearConsole() const;
    void setConsoleTextColor(int colorCode) const;
    int input() const;
    int askForNumberInRange(int min, int max) const;
private:
    void setConsoleColor(int colorCode) const;
    std::wstring generateRandomTitle() const;
};

