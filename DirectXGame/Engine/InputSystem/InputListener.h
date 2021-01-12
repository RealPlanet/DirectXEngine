#pragma once
//#include "Point.h"
class Point;
class InputListener
{
public:
	
	InputListener()
	{
			
	}

	~InputListener()
	{

	}

	//Virtual interface for keyboard

	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//Virtual interface for mouse

	virtual void onMouseMove(const Point& delta_pos) = 0;
	virtual void onLeftMouseDown(const Point& delta_pos) = 0;
	virtual void onRightMouseDown(const Point& delta_pos) = 0;
	virtual void onLeftMouseUp(const Point& delta_pos) = 0;
	virtual void onRightMouseUp(const Point& delta_pos) = 0;
};