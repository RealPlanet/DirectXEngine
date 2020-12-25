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
	

	//Window EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

protected:
	HWND m_hwnd = NULL;
	bool m_isRunning = false;;
};

