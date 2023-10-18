#pragma once
#include <cassert>
#include "MusicHolder.hpp"

MusicHolder* MusicHolder::m_s_Instance = nullptr;

MusicHolder::MusicHolder() {
    // if m_s_Instance != nullptr; game will exit
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

Music& MusicHolder::GetMusic(const std::string &filename) {
    // get a reference to m_Font via m_s_instance
    auto& m = m_s_Instance -> m_Music;
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
        auto& music = m[filename];
        // load texture from a file
        music.openFromFile(filename);
        return music;
    }
}

void MusicHolder::StopAll() {
    for (auto &itr : m_s_Instance -> m_Music) {
        itr.second.stop();
    }
}

void MusicHolder::PauseAll() {
    for (auto &itr : m_s_Instance -> m_Music) {
        itr.second.pause();
    }
}