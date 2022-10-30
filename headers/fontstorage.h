#ifndef FONTSTORAGE
#define FONTSTORAGE
#include "rayextended.h"
#include <string>
#include <vector>
#include <array>

class FontStorage
{
public:
    enum FontNames {
        KINGTHINGSEXETER_T,
        KINGTHINGSFACETYPE_T,
        MAXFONTNAMES_T
    };
private:
    std::array<std::string, MAXFONTNAMES_T> m_fontStrs{
        "fonts/KingthingsExeter.ttf",
        "fonts/KingthingsFacetype.ttf"
    };
    std::array<Font, MAXFONTNAMES_T> m_fonts;
public:
    void init() // call this AFTER you call InitWindow()
    {
        for (int i{}; i < MAXFONTNAMES_T; ++i)
        {
            m_fonts[i] = LoadFontEx(m_fontStrs[i].c_str(), 64, 0, 250);
        }
    }

    ~FontStorage()
    {
        for (auto& f : m_fonts)
        {
            UnloadFont(f);
        }
    }

    const Font& get(FontNames f) const { return m_fonts[f]; }
};

using FontNam = FontStorage::FontNames;

FontStorage& fontStrg(); // im a sneaky snitch, i use a function instead of a pure global variable to get past c++ being stupid asf
                            // also you probably shouldn't make a local FontStorage, i think it would just waste memory

#endif