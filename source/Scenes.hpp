#pragma once

#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "SceneChange.hpp"

class Scenes {
    private:
        Image m_ScreenShot;
    public:
        virtual SceneChange run(RenderWindow &window) = 0;
        virtual void setScreenShot(Image screenshot);
        virtual Image getScreenShot();
};

void Scenes::setScreenShot(Image screenshot) {
    m_ScreenShot = screenshot;
}

Image Scenes::getScreenShot() {
    return m_ScreenShot;
}