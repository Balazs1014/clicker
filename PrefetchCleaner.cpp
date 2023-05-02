#include "PrefetchCleaner.hpp"

PrefetchCleaner::PrefetchCleaner(const std::string& folderPath) : m_folderPath(folderPath) {}

bool PrefetchCleaner::clean() {
    std::string command = "del /Q ";
    command.append(m_folderPath).append("\\SW.*.pf");
    return std::system(command.c_str()) == 0;
}