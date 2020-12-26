#include "Window.h"
#include "Windows.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			//Event fired on window creation
			Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			window->setHWND(hwnd);
			window->onCreate();
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

bool Window::init()
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

	if (!RegisterClassEx(&wc)) //If the registration of the window fails returns false
	{
		return false;
	}

	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application",
							WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!m_hwnd)
	{
		//If window creation fails return false
		return false;
	}

	//Show window on screen
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	m_isRunning = true; //Flag which indicates if the game is running
	return true;
}

bool Window::broadcast()
{
	MSG message;
	this->onUpdate();

	while ( PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0 )
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	
	Sleep(1);

	return true;
}

bool Window::release()
{
	if (!DestroyWindow(m_hwnd))
	{
		return false;
	}

	return true;
}

bool Window::isRunning()
{
	return m_isRunning;
}

RECT Window::getClientWindowRect()
{
	RECT rect;
	GetClientRect(this->m_hwnd, &rect);
	return rect;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onDestroy()
{
	m_isRunning = false;
}
