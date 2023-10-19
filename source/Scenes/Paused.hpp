#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/TextureHolder.hpp"
#include "../Holders/SoundHolder.hpp"
#include "../Holders/MusicHolder.hpp"
#include "../Tools/SetOriginCenter.hpp"
#include "../Tools/SetRectangleShapeOnMouseHover.hpp"

class Paused : public Scenes {
    public:
        SceneChange run(RenderWindow &window) override;
};
