#pragma once

#include <Windows.h>

class DnsCacheFlusher
{
public:
    DnsCacheFlusher();
    bool flushCache();
private:
    typedef BOOL(WINAPI* DoDnsFlushResolverCache)();
    DoDnsFlushResolverCache m_flushResolverCache;
};

