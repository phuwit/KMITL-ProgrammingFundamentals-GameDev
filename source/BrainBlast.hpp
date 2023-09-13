#pragma once
#include <SFML/Graphics.hpp>

#include "Zombie/Zombie.hpp"

using namespace sf;

// prototype createBackground function, with a vertexarray reference parameter and intrect parameter
int createBackground (VertexArray& rVA, IntRect playArea);

// prototype createHorde function, returns a zombie pointer
Zombie* createHorde(int numZombies, float spriteScaling, IntRect arena);