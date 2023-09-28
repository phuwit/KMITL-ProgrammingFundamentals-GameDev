#pragma once

#include <SFML/Graphics.hpp>
#include "CommonEnum.hpp"
#include "TextureHolder.hpp"

using namespace sf;

class SceneChange {
    private:
        Texture m_Screenshot;
        ScenesList m_nextScreen;
    public:
        SceneChange(ScenesList nextScreen, Texture screenshot);
        SceneChange(ScenesList nextScreen);
        Texture getScreenShot();
        ScenesList getNextScreen();
};

SceneChange::SceneChange(ScenesList nextScreen, Texture screenshot) {
    m_Screenshot = screenshot;
    m_nextScreen = nextScreen;
}

SceneChange::SceneChange(ScenesList nextScreen) {
    // if (TextureHolder) {
    //     m_Screenshot = TextureHolder::GetTexture("assets/notexture.png");
    // }
    m_Screenshot.loadFromFile("assets/notexture.png");
    m_nextScreen = nextScreen;
}

Texture SceneChange::getScreenShot() {
    return m_Screenshot;
}

ScenesList SceneChange::getNextScreen() {
    return m_nextScreen;
}