#include <Windows.h>
#include "WindowsMessageMap.h"
#include <sstream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap messageMap;
	OutputDebugString(messageMap(msg, lParam, wParam).c_str());
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_CHAR:
	{
		static std::string title;
		if (wParam != 0x00000008)
		{
			title.push_back((char)wParam);
		}
		else
		{
			if (title.size() > 0)
			{
				title.pop_back();
			}
		}
		SetWindowText(hWnd, title.c_str());
	}
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	const auto pClassName = "dx11 window";
	// register window class
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = nullptr;
	windowClass.hCursor = nullptr;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = pClassName;
	windowClass.hIconSm = nullptr;
	RegisterClassEx(&windowClass);
	// create window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		"Happy Hard Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);
	ShowWindow(hWnd, SW_SHOW);
	// message loop (events)
	MSG msg;
	BOOL getResult;
	while (getResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (getResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
	return 0;
}