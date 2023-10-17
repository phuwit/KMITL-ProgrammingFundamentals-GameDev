#pragma once

#include <SFML/Audio.hpp>
#include <map>

using namespace sf;

class SoundHolder {
    private:
        // map container from STL, holds string-Font key-pair
        std::map<std::string, SoundBuffer> m_Sounds;
        // pointer of the same type as the class - one and only instance
        static SoundHolder* m_s_Instance;

    public:
        SoundHolder();
        static SoundBuffer& GetSound(std::string const& filename);
};
