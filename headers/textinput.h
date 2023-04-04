#ifndef TEXTINPUT
#define TEXTINPUT
#include "ob.h"
#include "rayextended.h"
#include "fontstorage.h"
#include <string>

class TextInput : public Ob
{
private:
    // technically any of these could be public vars
    Vector2 m_pos{100, 100};
    Vector2 m_size{500, 300};
    bool m_isResizeable{true};
    int m_typeMode{0}; // 0 for text, 1 for numbers
    std::string m_font{"fonts/KingthingsExeter.ttf"};
    int m_fontSize{20};
    int m_fontSpacing{2};
    Color m_bkgrndCol{GRAY};
    Color m_txtCol{BLACK};
    Color m_selectedTxtCol{MAROON};
    Color m_resizeCrclCol{DARKGRAY};
    Color m_resizeCrclSelectedCol{LIGHTGRAY};
    int m_resizeCrclRadius{10};
    float m_selectionFlashRate{.25};
    bool m_hidden{false};
    
    std::string m_txt{};
    bool m_isSelected{};
    float m_selectionTimer{};
    bool m_justSubmitted{};
    bool m_currentlyRepositioning{};
    bool m_currentlyResizing{};
    int m_capsLockOn{};

public:
    TextInput(Vector2 pos={100, 100},
            Vector2 size={500, 300},
            bool isResizeable=true,
            int typeMode=0, // 0 for text, 1 for numbers
            std::string font="fonts/KingthingsExeter.ttf",
            int fontSize=20,
            int fontSpacing=2,
            Color bkgrndCol=GRAY,
            Color txtCol=BLACK,
            Color selectedTxtCol=MAROON,
            Color resizeCrclCol=DARKGRAY,
            Color resizeCrclSelectedCol=LIGHTGRAY,
            int resizeCrclRadius=10,
            float selectionFlashRate=.25)
        : m_pos{pos}
        , m_size{size}
        , m_isResizeable{isResizeable}
        , m_typeMode{typeMode}
        , m_font{font}
        , m_fontSize{fontSize}
        , m_fontSpacing{fontSpacing}
        , m_bkgrndCol{bkgrndCol}
        , m_txtCol{txtCol}
        , m_selectedTxtCol{selectedTxtCol}
        , m_resizeCrclCol{resizeCrclCol}
        , m_resizeCrclSelectedCol{resizeCrclSelectedCol}
        , m_resizeCrclRadius{resizeCrclRadius}
        , m_selectionFlashRate{selectionFlashRate}
    {}

    void update() override;
    void draw() override;

    // output
    const std::string& getInputTxt() { return m_txt; }
    int getInputInt() { return atoi(m_txt.c_str()); }
    float getInputFloat() { return atof(m_txt.c_str()); }
    bool justSubmitted() { return m_justSubmitted; }
    // input
    void submit() { m_txt = ""; m_justSubmitted = true; }
    void setResizeable(bool isResizeable) { m_isResizeable = isResizeable; }
    void setTypeMode(int mode) { submit(); m_typeMode = mode; }

    void setHid(bool hidden) {m_hidden = hidden;}
    bool getHid() {return m_hidden;}
};  

#endif