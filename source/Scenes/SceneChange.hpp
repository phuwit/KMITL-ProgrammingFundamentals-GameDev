#pragma once

#include <SFML/Graphics.hpp>
#include "../Holders/TextureHolder.hpp"
#include "../CommonEnum.hpp"

using namespace sf;

class SceneChange {
    private:
        Image m_Screenshot;
        ScenesList m_NextScreen;
    public:
        SceneChange(ScenesList nextScreen, Image screenshot);
        SceneChange(ScenesList nextScreen);
        Image getScreenShot();
        ScenesList getNextScreen();
};

SceneChange::SceneChange(ScenesList nextScreen, Image screenshot) {
    m_Screenshot = screenshot;
    m_NextScreen = nextScreen;
}

SceneChange::SceneChange(ScenesList nextScreen) {
    // if (TextureHolder) {
    //     m_Screenshot = TextureHolder::GetTexture("assets/notexture.png");
    // }
    m_Screenshot.loadFromFile("assets/notexture.png");
    m_NextScreen = nextScreen;
}

Image SceneChange::getScreenShot() {
    return m_Screenshot;
}

ScenesList SceneChange::getNextScreen() {
    return m_NextScreen;
}