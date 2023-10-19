#include "SceneChange.hpp"

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