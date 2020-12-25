#include "AppWindow.h"

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
}

void AppWindow::onUpdate()
{
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::get()->release();
}