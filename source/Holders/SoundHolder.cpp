#include <cassert>
#include "SoundHolder.hpp"

SoundHolder* SoundHolder::m_s_Instance = nullptr;

SoundHolder::SoundHolder() {
    // if m_s_Instance != nullptr; game will exit
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

SoundBuffer& SoundHolder::GetSound(const std::string &filename) {
    // get a reference to m_Font via m_s_instance
    auto& m = m_s_Instance -> m_Sounds;
    // auto equivalent to map<string, Font>
    // create an iterator to hold a key-value pair (kvp) and search for a required kvp using the passed in filename
    auto keyValuePair = m.find(filename);
    // auto equivalent to map<string, Font>::iterator

    // match?
    if (keyValuePair != m.end()) {
        // match.
        // return the font; second part of kvp
        return keyValuePair -> second;
    }
    else {
        // no match.
        // create a new key value pair using the filename
        auto& soundBuffer = m[filename];
        // load texture from a file
        soundBuffer.loadFromFile(filename);
        return soundBuffer;
    }
}
