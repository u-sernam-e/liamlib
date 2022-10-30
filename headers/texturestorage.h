#ifndef TEXTURESTORAGE
#define TEXTURESTORAGE
#include "rayextended.h"
#include <string>
#include <vector>
#include <array>

class TextureStorage
{
public:
    enum TextureNames {
        CAR_T,
        BACKGROUND_TEMP_T,
        MAXTEXTURENAMES_T
    };
private:
    std::array<std::string, MAXTEXTURENAMES_T> m_txtrStrs{
        "res/car.png",
        "res/Jermaidiot.png"
    };
    std::array<Texture2D, MAXTEXTURENAMES_T> m_txtrs;
public:
    void init() // call this AFTER you call InitWindow()
    {
        for (int i{}; i < MAXTEXTURENAMES_T; ++i)
        {
            m_txtrs[i] = LoadTexture(m_txtrStrs[i].c_str());
        }
    }

    ~TextureStorage()
    {
        for (auto& t : m_txtrs)
        {
            UnloadTexture(t);
        }
    }

    const Texture2D& get(TextureNames t) const { return m_txtrs[t]; }
};

using TxtrNam = TextureStorage::TextureNames;

TextureStorage& txtrStrg(); // im a sneaky snitch, i use a function instead of a pure global variable to get past c++ being stupid asf
                            // also you probably shouldn't make a local TextureStorage, i think it would just waste memory

#endif