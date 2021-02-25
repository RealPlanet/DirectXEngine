#include "InputSystem.h"

InputSystem* InputSystem::get()
{
    static InputSystem system;
    return &system;
}

void InputSystem::addListener(InputListener* listener)
{
    m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
    m_set_listeners.erase(listener);
}

void InputSystem::update()
{
    POINT current_delta = {};
    GetCursorPos(&current_delta);

    if (m_first_time)
    {
        m_old_mouse_pos = Point(current_delta.x, current_delta.y);
        m_first_time = false;
    }

    if (current_delta.y != m_old_mouse_pos.m_y || current_delta.x != m_old_mouse_pos.m_x)
    {
        auto iterator = m_set_listeners.begin();
        while (iterator != m_set_listeners.end())
        {
            Point temp = Point(current_delta.x - m_old_mouse_pos.m_x, current_delta.y - m_old_mouse_pos.m_y);
            (*iterator++)->onMouseMove(temp);
        }
        m_old_mouse_pos = Point(current_delta.x, current_delta.y);
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
                        (*iterator++)->onLeftMouseDown(Point(current_delta.x, current_delta.y));
                    }
                    else if (i == VK_RBUTTON && m_keys_state[i] != m_old_keys_state[i])
                    {
                        (*iterator++)->onRightMouseDown(Point(current_delta.x, current_delta.y));
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
                            (*iterator++)->onLeftMouseDown(Point(current_delta.x, current_delta.y));
                        }
                        else if (i == VK_RBUTTON)
                        {
                            (*iterator++)->onRightMouseDown(Point(current_delta.x, current_delta.y));
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
