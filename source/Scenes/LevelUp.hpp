#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scenes.hpp"
#include "Game.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/SoundHolder.hpp"
#include "../Holders/MusicHolder.hpp"
#include "../Tools/SetOriginCenter.hpp"
#include "../Tools/SetRectangleShapeOnMouseHover.hpp"

class LevelUp : public Scenes {
public:
    virtual SceneChange run(RenderWindow &window);
};
