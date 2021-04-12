#pragma once
#include <wtypes.h>

class Window
{
public:
	Window();//Initialize the window
	~Window();//Release the window
	
	bool isRunning();
	RECT getClientWindowRect();
	RECT getScreenSize();

	//Window EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onFocus() = 0;
	virtual void onKillFocus() = 0;
	virtual void onSize() = 0;

	virtual void onDestroy();
protected:
	HWND m_hwnd = NULL;
	bool m_isRunning = false;
	bool m_isInit = false;
private:
	bool broadcast();
};

