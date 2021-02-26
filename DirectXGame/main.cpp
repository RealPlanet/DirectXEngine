#include <iostream>
#include "AppWindow.h"
#include "InputSystem.h"

void ReleaseResources();

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
	}
	catch (...) { return -1; }

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

	ReleaseResources();

	return 0;
}

void ReleaseResources()
{
	GraphicsEngine::release();
	InputSystem::release();
}