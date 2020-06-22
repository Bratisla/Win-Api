#pragma once
#include <unordered_map>
#include <Windows.h>

class WindowsMessageMap
{
public:
	WindowsMessageMap();
	std::string operator()(DWORD msg, LPARAM lParam, WPARAM wParam) const noexcept;
private:
	std::unordered_map<DWORD, std::string> map;
};

