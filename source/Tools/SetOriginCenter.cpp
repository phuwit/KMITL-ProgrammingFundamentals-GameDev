#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f getFloatRectCenter (FloatRect floatrect) {
    return Vector2f(floatrect.width / 2, floatrect.height / 2);
}

void spriteSetOriginCenter (Sprite &sprite) {
    sprite.setOrigin(getFloatRectCenter(sprite.getLocalBounds()));
}

void textSetOriginCenter (Text &text) {
    text.setOrigin(getFloatRectCenter(text.getLocalBounds()));
}

void shapeSetOriginCenter (Shape &shape) {
    shape.setOrigin(getFloatRectCenter(shape.getLocalBounds()));
}