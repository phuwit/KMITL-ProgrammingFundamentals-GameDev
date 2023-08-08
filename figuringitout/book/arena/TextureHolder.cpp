#pragma once

#include <assert.h>
#include "TextureHolder.hpp"

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
    // if m_s_Instance != nullptr; game will exit
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {
    // get a reference to m_Textures via m_s_instance
    auto& m = m_s_Instance -> m_Texture;
    // auto equivalent to map<string, texture>
    // create an iterator to hold a key-value pair (kvp) and search for a required kvp using the passed in filename
    auto keyValuePair = m.find(filename);
    // auto equivalent to map<string, texture>::iterator

    // match?
    if (keyValuePair != m.end()) {
        // match.
        // return the texture; second part of kvp
        return keyValuePair -> second;
    }
    else {
        // no match.
        // create a new key value pair using the filename
        auto& texture = m[filename];
        // load texture from a file
        texture.loadFromFile(filename);
        return texture;
    }
}