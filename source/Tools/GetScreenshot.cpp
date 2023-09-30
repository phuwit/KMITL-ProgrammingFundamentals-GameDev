#include <SFML/Graphics.hpp>

using namespace sf;

Texture getScreenshot (RenderWindow &window) {
    Texture screenshot;
    screenshot.create(window.getSize().x, window.getSize().y);
    screenshot.update(window);

    return screenshot;
}