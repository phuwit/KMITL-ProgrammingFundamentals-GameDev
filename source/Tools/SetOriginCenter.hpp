#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f getFloatRectCenter (FloatRect floatrect);
void spriteSetOriginCenter (Sprite &sprite);
void textSetOriginCenter (Text &text);
void textSetOriginYCenter (Text &text);
void textSetOriginXCenter (Text &text);
void shapeSetOriginCenter (Shape &shape);