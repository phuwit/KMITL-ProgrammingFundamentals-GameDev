#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/MusicHolder.hpp"
#include "../Tools/SetOriginCenter.hpp"
#include "../Tools/SetRectangleShapeOnMouseHover.hpp"
#include "../Tools/OpenURL.hpp"

using namespace sf;

class How : public Scenes {
public:
    virtual SceneChange run(RenderWindow &window);
};
