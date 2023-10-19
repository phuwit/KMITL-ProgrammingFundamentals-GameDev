#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/MusicHolder.hpp"
#include "../Tools/SetOriginCenter.hpp"
#include "../Tools/SetRectangleShapeOnMouseHover.hpp"
#include "../Scores/Score.hpp"
#include "../Scores/ReadScores.hpp"
#include "../Scores/SaveScores.hpp"
#include "../Scores/SortScores.hpp"


class Leaderboard : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};
