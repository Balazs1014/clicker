#pragma once

#include <string>
#include <cstdlib>

class PrefetchCleaner
{
public:
    PrefetchCleaner(const std::string& folderPath);
    bool clean();
private:
    std::string m_folderPath;
};

