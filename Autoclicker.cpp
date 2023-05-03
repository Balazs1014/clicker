#include "Autoclicker.hpp"

Autoclicker::Autoclicker() : m_windowHandle(nullptr), m_cps(5), m_toggleKey(VK_INSERT) {
    // Find the window with class name "LWJGL" (Minecraft always has one)
    m_windowHandle = FindWindowA("LWJGL", nullptr);
    if (m_windowHandle == nullptr) {
        std::cout << "Error: Could not find window with class name \"LWJGL\"" << std::endl;
    }
}
Autoclicker::~Autoclicker() {
    stop();
}

int Autoclicker::getCps() {
    return m_cps;
}
void Autoclicker::setCps(int value) {
    m_cps = value;
}

bool Autoclicker::dropCps(){
    return false;
}

float Autoclicker::generateRandomSleep(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    float random_number = dist(gen);
    return random_number;
}
void Autoclicker::start() {
    if (!m_isRunning) {
        m_isRunning = true;
        std::cout << "Clicker started.\n";
        delaymin = ((1000 / m_cps + 2) / 2) - 1.f;
        delaymax = ((1000 / m_cps - 2) / 2) - 1.f;
        while (m_isRunning) {
            if (GetAsyncKeyState(VK_LBUTTON)) {
                click();
                handleToggleKeyPress();
                delayclick = generateRandomSleep(delaymin - 0.6f, delaymax + 1.f);
                std::this_thread::sleep_for(std::chrono::milliseconds((int)delayclick + 10));
            }
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