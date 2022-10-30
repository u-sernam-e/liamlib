#include "button.h"
#include "rayextended.h"
#include <string>

void Button::update()
{
    if (CheckCollisionPointRec(GetMousePosition(), {m_pos.x, m_pos.y, m_size.x, m_size.y}))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            m_state = PRESSED;
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            m_state = RELEASED;
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            m_state = DOWN;
        else
            m_state = HOVER;
    }
    else
    {
        m_state = UP;
    }
}

void Button::draw()
{
    switch (m_state)
    {
        case HOVER:
            if (m_hasTxtr)
                DrawTexture(m_txtr, m_pos.x, m_pos.y, m_hoverTint);
            else
                DrawRectangleV(m_pos, m_size, m_hoverTint);
            break;
        
        case UP:
        case RELEASED:
            if (m_hasTxtr)
                DrawTexture(m_txtr, m_pos.x, m_pos.y, m_upTint);
            else
                DrawRectangleV(m_pos, m_size, m_upTint);
            break;
        
        case DOWN:
        case PRESSED:
            if (m_hasTxtr)
                DrawTexture(m_txtr, m_pos.x, m_pos.y, m_downTint);
            else
                DrawRectangleV(m_pos, m_size, m_downTint);
            break;
    }
    DrawText(m_txt.c_str(), m_pos.x + 5, m_pos.y + 5, m_size.y - 10, WHITE);
}


bool Button::pressed()
{
    return m_state == PRESSED;
}

bool Button::down()
{
    return m_state == DOWN || m_state == PRESSED;
}

bool Button::released()
{
    return m_state == RELEASED;
}