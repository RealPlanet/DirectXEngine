#pragma once
#include <wtypes.h>

class Window
{
public:
	//Initialize the window
	bool init();
	bool broadcast();

	//Release the window
	bool release();
	bool isRunning();
	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//Window EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();
	virtual void onFocus() = 0;
	virtual void onKillFocus() = 0;

protected:
	HWND m_hwnd = NULL;
	bool m_isRunning = false;
};

