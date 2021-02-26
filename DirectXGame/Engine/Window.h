#pragma once
#include <wtypes.h>

class Window
{
public:
	Window();//Initialize the window
	~Window();//Release the window
	
	bool isRunning();
	RECT getClientWindowRect();

	//Window EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();
	virtual void onFocus() = 0;
	virtual void onKillFocus() = 0;

protected:
	HWND m_hwnd = NULL;
	bool m_isRunning = false;
	bool m_isInit = false;
private:
	bool broadcast();
};

