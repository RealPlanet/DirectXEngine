#include "Window.h"
#include <exception>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			//Event fired on window creation
			break;
		}

		case WM_SETFOCUS:
		{
			//Event fired on window enter focus
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if(window) window->onFocus();
			break;
		}

		case WM_KILLFOCUS:
		{
			//Event fired on window exit focus
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
			break;
		}

		case WM_DESTROY:
		{
			//Event fired when window needs to be destroyed
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			//window->release();
			PostQuitMessage(0);
			break;
		}

		default:
		{
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

	return NULL;
}

Window::Window()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!RegisterClassEx(&wc)) //If the registration of the window fails
	{
		throw std::exception("Could not register new window");
	}

	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application",
							WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);

	if (!m_hwnd)
	{
		//If window creation fails return false
		throw std::exception("Failed to create Window");
	}

	//Show window on screen
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	m_isRunning = true; //Flag which indicates if the game is running
}

Window::~Window()
{

}

bool Window::broadcast()
{
	if (!this->m_isInit)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();

		this->m_isInit = true;
	}

	MSG message;
	this->onUpdate();

	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}


	Sleep(1);

	return true;
}

bool Window::isRunning()
{
	if(m_isRunning) broadcast();
	return m_isRunning;
}

RECT Window::getClientWindowRect()
{
	RECT rect;
	GetClientRect(this->m_hwnd, &rect);
	return rect;
}

void Window::onDestroy()
{
	m_isRunning = false;
}
