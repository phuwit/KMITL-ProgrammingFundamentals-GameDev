#pragma once
#include <SFML/Graphics.hpp>

#include "Zombie.hpp"

using namespace sf;

// prototype createBackground function, with a vertexarray reference parameter and intrect parameter
int createBackground (VertexArray& rVA, IntRect arena);

// prototype createHorde function, returns a zombie pointer
Zombie* createHorde(int numZombies, IntRect arena);