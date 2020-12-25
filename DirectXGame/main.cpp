#include <iostream>
#include "AppWindow.h"


int main()
{
	AppWindow application;
	if (application.init())
	{
		//If window init successful do game loop
		while (application.isRunning())
		{
			application.broadcast();
		}
	}

	std::cout << "Hello world";
	return 0;
}