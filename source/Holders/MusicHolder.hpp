#pragma once

#include <SFML/Audio.hpp>
#include <map>

using namespace sf;

class MusicHolder {
private:
    // map container from STL, holds string-Font key-pair
    std::map<std::string, Music> m_Music;
    // pointer of the same type as the class - one and only instance
    static MusicHolder* m_s_Instance;

public:
    MusicHolder();
    static Music& GetMusic(std::string const& filename);
    static void StopAll();
    static void PauseAll();
};
