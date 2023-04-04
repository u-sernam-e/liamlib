#include "button.h"

void Button::update()
{
    Vector2 activePos{(m_anchorRight ? GetScreenWidth() - m_pos.x : m_pos.x), (m_anchorBot ? GetScreenHeight() - m_pos.y : m_pos.y)};
    
    if (CheckCollisionPointRec(GetMousePosition(), {activePos.x, activePos.y, m_size.x, m_size.y}))
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

int maxXTextSize(const std::string& txt, int xSize, int depth) // for the text when no texture
{
    int maxSize{xSize-10};
    int minSize{};
    for (int i{}; i < depth; ++i)
    {
        int guess{(maxSize + minSize) / 2};
        int guessXSize{MeasureText(txt.c_str(), guess)};
        if (guessXSize > xSize-10)
        {
            maxSize = guess;
            continue;
        }
        if (guessXSize < xSize-10)
        {
            minSize = guess;
            continue;
        }
        if (guessXSize == xSize-10)
            break;
    }
    return (maxSize + minSize) / 2;
}

void Button::draw()
{
    if (m_hidden)
        return;

    Vector2 activePos{(m_anchorRight ? GetScreenWidth() - m_pos.x : m_pos.x), (m_anchorBot ? GetScreenHeight() - m_pos.y : m_pos.y)};

    switch (m_state)
    {
        case HOVER:
            if (m_hasTxtr)
                DrawTexture(m_txtr, activePos.x, activePos.y, m_hoverTint);
            else
                DrawRectangleV(activePos, m_size, m_hoverTint);
            break;
        
        case UP:
        case RELEASED:
            if (m_hasTxtr)
                DrawTexture(m_txtr, activePos.x, activePos.y, m_upTint);
            else
                DrawRectangleV(activePos, m_size, m_upTint);
            break;
        
        case DOWN:
        case PRESSED:
            if (m_hasTxtr)
                DrawTexture(m_txtr, activePos.x, activePos.y, m_downTint);
            else
                DrawRectangleV(activePos, m_size, m_downTint);
            break;
    }
    int fsize{std::min(static_cast<int>(m_size.y) - 10, maxXTextSize(m_txt, m_size.x, 10))};
    DrawText(m_txt.c_str(), (activePos.x + m_size.x/2) - MeasureText(m_txt.c_str(), fsize)/2, (activePos.y + m_size.y/2) - fsize/2, fsize, WHITE);
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

bool Button::hover()
{
    return m_state == HOVER || m_state == RELEASED;
}