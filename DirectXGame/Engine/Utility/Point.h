#pragma once

class Point
{
public:
	Point() : Point(0, 0) {}
	Point(int x, int y) : x{ x }, y{ y }{}
	int x = 0, y = 0;
};
