#pragma once

#include <SFML/Graphics.hpp>

#include "SceneChange.hpp"
#include "../CommonEnum.hpp"

class Scenes {
    private:
        Image m_ScreenShot;
        Scenes* m_GameScene;
    public:
        virtual SceneChange run(RenderWindow &window) = 0;
        virtual void setScreenShot(Image screenshot);
        virtual void setGamePtr(Scenes* gameScene);
        virtual Image getScreenShot();
        virtual Scenes* getGamePtr();
};

void Scenes::setScreenShot(Image screenshot) {
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