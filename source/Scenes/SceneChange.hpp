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