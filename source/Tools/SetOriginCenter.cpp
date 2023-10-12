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

void textSetOriginYCenter (Text &text) {
    text.setOrigin(Vector2f(text.getOrigin().x, text.getLocalBounds().height / 2));
}

void textSetOriginXCenter (Text &text) {
    text.setOrigin(Vector2f(text.getLocalBounds().width / 2, text.getOrigin().y));
}

void shapeSetOriginCenter (Shape &shape) {
    shape.setOrigin(getFloatRectCenter(shape.getLocalBounds()));
}