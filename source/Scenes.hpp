#pragma once

#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "SceneChange.hpp"

class Scenes {
    private:
        Texture m_ScreenShot;
    public:
        virtual SceneChange run(RenderWindow &window) = 0;
        virtual void setScreenShot(Texture screenshot);
        virtual Texture getScreenShot();
};

void Scenes::setScreenShot(Texture screenshot) {
    m_ScreenShot = screenshot;
}

Texture Scenes::getScreenShot() {
    return m_ScreenShot;
}