#ifndef FONTSTORAGE
#define FONTSTORAGE
#include "rayextended.h"
#include <string>
#include <vector>
#include <array>
#include <iostream>

class FontStorage
{
private:
    std::vector<std::pair<std::vector<std::pair<Font, int>>, std::string>> m_fonts; // this is the most incredible type i've ever seen... the int represents font size and the string represents the file name
public:
    void init(const std::vector<std::string>& fontStrs) // call this AFTER you call InitWindow()
    {
        for (int i{}; i < fontStrs.size(); ++i)
        {
            m_fonts.push_back({{}, fontStrs[i]});
        }
    }

    ~FontStorage()
    {
        clearFonts();
    }

    const Font& get(std::string name, int fontsize) // gwvoil;ujkres;hvdjnhv;ioelldsrdfhnjgrbfhnjgoboeldldsrkhjnfrgbkhjngb;;oeirghjvnhjvno;lhjrngrgi
    {
        for (auto& font : m_fonts)
        {
            if (font.second == name)
            {
                for (auto& fpair : font.first)
                {
                    if (fpair.second == fontsize)
                    {
                        return fpair.first;
                    }
                }
                font.first.push_back({LoadFontEx(name.c_str(), fontsize, 0, 0), fontsize});
                return font.first[font.first.size()-1].first;
            }
        }
        return GetFontDefault();
    }

    void clearFonts()
    {
        for (auto& font : m_fonts)
        {
            for (int i{font.first.size()-1}; i >= 0; --i)
            {
                UnloadFont(font.first[i].first);
                font.first.pop_back();
            }
        }
    }
};

FontStorage& fontStrg(); // im a sneaky snitch, i use a function instead of a pure global variable to get past c++ being stupid asf
                            // also you probably shouldn't make a local FontStorage, i think it would just waste memory

#endif