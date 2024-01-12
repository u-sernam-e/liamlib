#ifndef BUTTON
#define BUTTON
#include "uielement.h"
#include "fontstorage.h"
#include <string>
#include <algorithm>

class Button : public UiElement
{
private:
    enum State
    {
        UP,
        DOWN,
        HOVER,
        PRESSED,
        RELEASED,
        MAXBUTTONSTATE
    };
    Vector2 m_pos{};
    Vector2 m_size{};
    Color m_upTint{};
    Color m_hoverTint{};
    Color m_downTint{};
    Color m_txtColor{};
    bool m_useCustomTxtColor{};
    Texture2D m_txtr{};
    std::string m_txt{};
    FontStorage* m_fs{};
    std::string m_fontStr{};
    bool m_hasTxtr{};
    NPatchInfo m_nPatchInfo{};
    State m_state{};
    bool m_anchorRight{}; // maybe change this anchor system to an enum to allow for center alignment
    bool m_anchorBot{};
    bool m_hidden{};
public:
    Button(Vector2 pos, Vector2 size, Color upTint, Color downTint, Color hoverTint, std::string text, Color txtColor=WHITE, bool useCustomTxtColor=false, bool anchorRight=false, bool anchorBot=false, Texture2D texture={}, bool isTxtrd=false, FontStorage* fs=nullptr, std::string fontStr="", int nPatchMarginVert=8, int nPatchMarginHorz=8)
        : m_pos{pos}
        , m_size{size}
        , m_anchorRight{anchorRight}
        , m_anchorBot{anchorBot}
        , m_upTint{upTint}
        , m_downTint{downTint}
        , m_hoverTint{hoverTint}
        , m_txt{text}
        , m_txtColor{txtColor}
        , m_useCustomTxtColor{useCustomTxtColor}
        , m_hasTxtr{isTxtrd}
        , m_txtr{texture} 
        , m_state{UP}
        , m_fs{fs}
        , m_fontStr{fontStr}
        , m_nPatchInfo{{0, 0, texture.width, texture.height}, nPatchMarginHorz, nPatchMarginVert, nPatchMarginHorz, nPatchMarginVert, NPATCH_NINE_PATCH}
    {}

    Button() = default;

    void update() override;
    void draw() override;

    void setPos(Vector2 p) {m_pos = p;}
    Vector2 getPos() override {
        Vector2 FUCK{m_pos};
        if (m_anchorRight)
            FUCK.x = GetScreenWidth() - FUCK.x;
        if (m_anchorBot)
            FUCK.y = GetScreenHeight() - FUCK.y;
        return FUCK;
    }

    void setSize(Vector2 s) {m_size = s;}
    Vector2 getSize() {return m_size;}

    bool down();
    bool pressed();
    bool released();
    bool hover();

    void setHid(bool hidden) {m_hidden = hidden;}
    bool getHid() {return m_hidden;}

    std::string getElementTypeName() override {return "button";}
};

#endif