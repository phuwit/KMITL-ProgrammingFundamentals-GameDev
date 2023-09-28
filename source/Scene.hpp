#pragma once

#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "SceneChange.hpp"

class Scenes {
   public:
        virtual SceneChange run(RenderWindow &window) = 0;
};
