#pragma once
#include <Windows.h>
#include <unordered_set>
#include "InputListener.h"
#include "Point.h"

class InputSystem
{
public:
	static InputSystem* get();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void update();
private:
	std::unordered_set<InputListener*> m_set_listeners;

	
	unsigned char m_old_keys_state[256] = {};

	Point m_old_mouse_pos = {};
	bool m_first_time = true;
};

