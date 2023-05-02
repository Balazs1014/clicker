#pragma once
#include <Windows.h>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <iostream>

class Autoclicker
{
private:
    std::wstring m_windowTitle;
    HWND m_windowHandle;
    bool m_isRunning;
    int m_cps;
    int m_toggleKey;
    std::mt19937 m_randomGenerator;

    void click();
    void findWindow();
    void handleToggleKeyPress();
public:
    Autoclicker();
    ~Autoclicker();

    void start();
    void stop();
    void setToggleKey(int toggleKey);

};
