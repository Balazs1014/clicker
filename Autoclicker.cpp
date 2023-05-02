#include "Autoclicker.hpp"

Autoclicker::Autoclicker() : m_windowHandle(nullptr), m_cps(0), m_toggleKey(VK_INSERT), m_isRunning(false) {
    // Find the window with class name "LWJGL" (Minecraft always has one)
    m_windowHandle = FindWindowA("LWJGL", nullptr);
    if (m_windowHandle == nullptr) {
        std::cout << "Error: Could not find window with class name \"LWJGL\"" << std::endl;
    }
}
Autoclicker::~Autoclicker() {
    stop();
}

void Autoclicker::start() {
    if (!m_isRunning) {
        m_isRunning = true;
        std::cout << "Clicker started.\n";
        while (m_isRunning) {
            click();
            handleToggleKeyPress();
            int sleepTimeMs = 1000 / m_cps + m_randomGenerator() % 3 - 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
        }
    }
}
void Autoclicker::stop() {
    if (m_isRunning) {
        m_isRunning = false;
        std::cout << "Clicker stopped.\n";
    }
}
void Autoclicker::setToggleKey(int toggleKey) {
    m_toggleKey = toggleKey;
}

void Autoclicker::click() {
    if (m_windowHandle != nullptr) {
        SendMessageW(m_windowHandle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
        SendMessageW(m_windowHandle, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
    }
}
void Autoclicker::findWindow() {
    m_windowHandle = FindWindowW(nullptr, m_windowTitle.c_str());
    if (m_windowHandle == nullptr) {
        std::wcerr << L"Could not find window with title \"" << m_windowTitle << "\".\n";
    }
}
void Autoclicker::handleToggleKeyPress() {
    if (GetAsyncKeyState(m_toggleKey) & 1) {
        m_isRunning = !m_isRunning;
        std::cout << "Clicker " << (m_isRunning ? "resumed." : "paused.") << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}