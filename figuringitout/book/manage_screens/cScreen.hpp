#pragma once

#include <SFML/Graphics.hpp>

class cScreen {
   public:
    virtual int Run(sf::RenderWindow &App) = 0;
};
