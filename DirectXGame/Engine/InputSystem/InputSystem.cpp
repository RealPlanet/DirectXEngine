#include "InputSystem.h"

InputSystem* InputSystem::m_system = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
    InputSystem::m_system = nullptr;
}

void InputSystem::create()
{
    if (InputSystem::m_system) throw std::exception("InputSystem already created");
    InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
    if (!InputSystem::m_system) return;
    delete InputSystem::m_system;
}

InputSystem* InputSystem::get()
{
    return m_system;
}

void InputSystem::addListener(InputListener* listener)
{
    m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
    m_set_listeners.erase(listener);
}

void InputSystem::setCursorPosition(const Point& pos)
{
    SetCursorPos(pos.x, pos.y);
}

void InputSystem::showCursor(bool show)
{
    ShowCursor(show);
}

void InputSystem::update()
{
    POINT current_mouse_pos = {};
    GetCursorPos(&current_mouse_pos);

    if (m_first_time)
    {
        m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
        m_first_time = false;
    }

    if (current_mouse_pos.y != m_old_mouse_pos.y || current_mouse_pos.x != m_old_mouse_pos.x)
    {
        auto iterator = m_set_listeners.begin();
        while (iterator != m_set_listeners.end())
        {
            Point temp = Point(current_mouse_pos.x, current_mouse_pos.y);
            (*iterator++)->onMouseMove(temp);
        }
        m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
    }
 
    unsigned char m_keys_state[256] = {};
    if (GetKeyboardState(m_keys_state))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            auto iterator = m_set_listeners.begin();
            if (m_keys_state[i] & 0x80)// Key is down
            { 
                while (iterator != m_set_listeners.end())
                {
                    if (i == VK_LBUTTON && m_keys_state[i] != m_old_keys_state[i])
                    {
                        (*iterator++)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else if (i == VK_RBUTTON && m_keys_state[i] != m_old_keys_state[i])
                    {
                        (*iterator++)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else
                    {
                        (*iterator++)->onKeyDown(i);
                    }      
                }
            }
            else // key is up
            {
                if (m_keys_state[i] != m_old_keys_state[i])
                {
                    while (iterator != m_set_listeners.end())
                    {
                        if (i == VK_LBUTTON)
                        {
                            (*iterator++)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                        }
                        else if (i == VK_RBUTTON)
                        {
                            (*iterator++)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                        }
                        else
                        {
                            (*iterator++)->onKeyUp(i);
                        } 
                    }
                }  
            }
        }
        memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
    }

}