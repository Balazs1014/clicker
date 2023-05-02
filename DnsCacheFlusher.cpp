#include "DnsCacheFlusher.hpp"
DnsCacheFlusher::DnsCacheFlusher() {
	HMODULE dnsAPI = LoadLibrary(L"dnsapi.dll");
	if (dnsAPI) {
		m_flushResolverCache = (DoDnsFlushResolverCache)GetProcAddress(dnsAPI, "DnsFlushResolverCache");
	}
	else {
		m_flushResolverCache = nullptr;
	}
}
bool DnsCacheFlusher::flushCache() {
	if (!m_flushResolverCache) {
		return false;
	}
	return m_flushResolverCache() == TRUE;
}