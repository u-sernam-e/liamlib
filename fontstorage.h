#ifndef FONTSTORAGE
#define FONTSTORAGE
#include "rayextended.h"
#include <string>
#include <vector>
#include <array>

class FontStorage
{
private:
    std::vector<std::pair<Font, std::string>> m_fonts;
public:
    void init(const std::vector<std::string>& fontStrs) // call this AFTER you call InitWindow()
    {
        for (int i{}; i < fontStrs.size(); ++i)
        {
            m_fonts.push_back({LoadFontEx(fontStrs[i].c_str(), 64, 0, 250), fontStrs[i]});
        }
    }

    ~FontStorage()
    {
        for (auto& f : m_fonts)
        {
            UnloadFont(f.first);
        }
    }

    const Font& get(std::string s) const
    {
        for (auto& t : m_fonts)
        {
            if (t.second == s)
                return t.first;
        }
        return m_fonts[0].first;
    }
};

FontStorage& fontStrg(); // im a sneaky snitch, i use a function instead of a pure global variable to get past c++ being stupid asf
                            // also you probably shouldn't make a local FontStorage, i think it would just waste memory

#endif