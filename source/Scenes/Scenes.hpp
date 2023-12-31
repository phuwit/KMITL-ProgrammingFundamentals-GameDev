#pragma once

#include <SFML/Graphics.hpp>

#include "SceneChange.hpp"
#include "../CommonEnum.hpp"

using namespace sf;

class Scenes {
    private:
        Image m_ScreenShot;
        Scenes* m_GameScene;
    public:
        virtual ~Scenes() = default;
        virtual SceneChange run(RenderWindow &window) = 0;
        virtual void setScreenShot(const Image& screenshot);
        virtual void setGamePtr(Scenes* gameScene);
        virtual Image getScreenShot();
        virtual Scenes* getGamePtr();
};
