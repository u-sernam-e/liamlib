#include "texturestorage.h"
#include "fontstorage.h"

TextureStorage& txtrStrg()
{
    static TextureStorage t{};
    return t;
}

FontStorage& fontStrg()
{
    static FontStorage f{};
    return f;
}