#pragma once

#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder {
    private:
        // map container from STL, holds string-Texture key-pair
        map<string, Texture> m_Texture;
        // pointer of the same type as the class - one and only instance
        static TextureHolder* m_s_Instance;

    public:
        TextureHolder();
        static Texture& GetTexture(string const& filename);
};

#endif