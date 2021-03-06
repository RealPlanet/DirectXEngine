#include <iostream>
#include "AppWindow.h"
#include "InputSystem.h"

void ReleaseResources()
{
	GraphicsEngine::release();
	InputSystem::release();
}

int main()
{
	// Allocate resources for base systems and catch any exceptions!
	{
		try
		{
			GraphicsEngine::create();
			InputSystem::create();
		}
		catch (...) { return -1; }
	}
	
	// Try running the application, if any errors happen, free memory and close program
	{
		try
		{
			AppWindow application;
			while (application.isRunning()); //isRunning automatically broadcasts events to the application
		}
		catch (...)
		{
			ReleaseResources();
			return -1;
		}
	}
	
	ReleaseResources();
	return 0;
}

