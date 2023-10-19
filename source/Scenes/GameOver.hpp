#pragma once

#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "Game.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/MusicHolder.hpp"
#include "../Scores/Score.hpp"
#include "../Scores/ReadScores.hpp"
#include "../Scores/SaveScores.hpp"
#include "../Scores/SortScores.hpp"
#include "../Tools/SetOriginCenter.hpp"
#include "../Tools/SetRectangleShapeOnMouseHover.hpp"

class GameOver : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};