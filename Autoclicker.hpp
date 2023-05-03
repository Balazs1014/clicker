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
    float delaymin;
    float delaymax;
    float delayclick;
    float blatantdelay;

    void click();
    bool dropCps();
    float generateRandomSleep(int min, int max);
    void findWindow();
    void handleToggleKeyPress();
public:
    Autoclicker();
    ~Autoclicker();
    int getCps();
    void setCps(int value);
    void start();
    void stop();
    void setToggleKey(int toggleKey);

};

