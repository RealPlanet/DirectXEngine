#pragma once

class Point
{
public:
	Point() : Point(0, 0) {}
	Point(int x, int y) : m_x{ x }, m_y{ y }{}
	int m_x = 0, m_y = 0;
};
