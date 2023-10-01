#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class FontHolder {
    private:
        // map container from STL, holds string-Font key-pair
        map<string, Font> m_Font;
        // pointer of the same type as the class - one and only instance
        static FontHolder* m_s_Instance;

    public:
        FontHolder();
        static Font& GetFont(string const& filename);
};
