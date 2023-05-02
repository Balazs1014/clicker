#include "Autoclicker.hpp"

Autoclicker::Autoclicker() : m_windowHandle(nullptr), m_cps(0), m_toggleKey(VK_INSERT) {
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

bool Autoclicker::dropCps() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count(); // use current time as seed
    std::mt19937 gen(seed); // seed the generator
    std::uniform_int_distribution<> distrib(1, 5); // define the range
    int random_number = distrib(gen); // generate the random number
    std::cout << "Random number between 1 and 5: " << random_number << std::endl;
    return random_number == 1;
}

void Autoclicker::start() {
    if (!m_isRunning) {
        m_isRunning = true;
        std::cout << "Clicker started.\n";
        int count = 0;
        while (m_isRunning) {
            if (GetAsyncKeyState(VK_LBUTTON)) {
                click();
                handleToggleKeyPress();
                int randomNumber = m_randomGenerator();
                int sleepTimeMs;
                if (dropCps()) {
                    sleepTimeMs = 1000 / (m_cps - m_cps / 2) + m_randomGenerator() % 3 - 1;
                }
                else {
                    sleepTimeMs = 1000 / m_cps + m_randomGenerator() % 3 - 1;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
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
        if (!dropCps()) {
            SendMessageW(m_windowHandle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            SendMessageW(m_windowHandle, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }
        else {
            SendMessageW(m_windowHandle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            SendMessageW(m_windowHandle, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }
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