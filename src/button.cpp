#include "button.h"

void Button::update()
{
    Vector2 activePos{(m_anchorRight ? GetScreenWidth() - m_pos.x : m_pos.x), (m_anchorBot ? GetScreenHeight() - m_pos.y : m_pos.y)}; // area where you can click on button
    
    if (CheckCollisionPointRec(GetMousePosition(), {activePos.x, activePos.y, m_size.x, m_size.y})) // if the mouse is over the button, change the state
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
    else // else keep the state as up
    {
        m_state = UP;
    }
}

Color getClashingColor(Color c) // returns a color that will go well with the input color (right now it just outputs black or white)
{
    Color output{WHITE};

    const float rLum{0.2126}; // these are the luminence values of each color (people are most sensitive to green, then red, then blue)
    const float gLum{0.7152};
    const float bLum{0.0722};

    if ((rLum*c.r + gLum*c.g + bLum*c.b) > (rLum*255 + gLum*255 + bLum*255)/2) // see if the luminence values of the color are brighter than the midpoint of brightness
        output = BLACK;
    
    return output;
}

int maxXTextSize(const std::string& txt, Font font, int xSize, int depth) // changes the size of the text based on the buttonsize
{
    int maxSize{xSize-10};
    int minSize{};
    for (int i{}; i < depth; ++i)
    {
        int guess{(maxSize + minSize) / 2};
        int guessXSize{MeasureTextEx(font, txt.c_str(), guess, 2).x};
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

    Vector2 activePos{(m_anchorRight ? GetScreenWidth() - m_pos.x : m_pos.x), (m_anchorBot ? GetScreenHeight() - m_pos.y : m_pos.y)}; // same equation as in update

    Color col{}; // setting the button color
    switch (m_state)
    {
        case HOVER:
        case RELEASED:
            col = m_hoverTint;
            break;
        case UP:
            col = m_upTint;
            break;
        case DOWN:
        case PRESSED:
            col = m_downTint;
            break;
    }

    if (!m_useCustomTxtColor)
        m_txtColor = getClashingColor(col);

    if (m_hasTxtr) // if it has a texture, then it draws it as a ninepatch
        DrawTextureNPatch(m_txtr, m_nPatchInfo, {activePos.x, activePos.y, m_size.x, m_size.y}, {0, 0}, 0, col);
    else
        DrawRectangleV(activePos, m_size, col);

    Font txtFont{GetFontDefault()};

    if (m_fs)
        txtFont=m_fs->get(m_fontStr, 50);

    int fsize{std::min(static_cast<int>(m_size.y) - 10, maxXTextSize(m_txt, txtFont, m_size.x, 10))};

    if (m_fs)
        txtFont=m_fs->get(m_fontStr, fsize);

    DrawTextEx(txtFont, m_txt.c_str(), Vector2{(activePos.x + m_size.x/2) - MeasureTextEx(txtFont, m_txt.c_str(), fsize, 2).x/2, (activePos.y + m_size.y/2) - fsize/2}, fsize, 2, m_txtColor);
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