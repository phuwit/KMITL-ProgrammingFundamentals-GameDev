#include "SetRectangleShapeOnMouseHover.hpp"

void setRectangleShapeColorOnMouseHover (RectangleShape &rectangleShape, Vector2f &mousePos, Color hoverColor, Color baseColor) {
    if (rectangleShape.getGlobalBounds().contains(Vector2f(mousePos))) {
        rectangleShape.setFillColor(hoverColor);
    }
    else {
        rectangleShape.setFillColor(baseColor);
    }
}