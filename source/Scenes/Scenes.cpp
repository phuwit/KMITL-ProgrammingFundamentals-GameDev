#include "Scenes.hpp"

void Scenes::setScreenShot(const Image& screenshot) {
    m_ScreenShot = screenshot;
}

void Scenes::setGamePtr(Scenes* gameScene) {
    m_GameScene = gameScene;
}

Image Scenes::getScreenShot() {
    return m_ScreenShot;
}

Scenes* Scenes::getGamePtr() {
    return m_GameScene;
}