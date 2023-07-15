#include <SFML/Graphics.hpp>

using namespace sf;

int main () {
    // Create a videomode object
    VideoMode vm(1920, 1080);
    // Create and open window for the game
    RenderWindow window(vm, "Timber!!!", Style::None);

    // Create a texture to hold a graphic on GPU memory
    Texture textureBackground;
    // Load a png into textureBackground
    textureBackground.loadFromFile("graphics/background.png");
    // Create a sprite
    Sprite spriteBackground;
    // Make spriteBackground have the texture from textureBackground
    spriteBackground.setTexture(textureBackground);
    // Move sprite to 0,0
    spriteBackground.setPosition(0,0);

    // Main game loop
    while (window.isOpen()) {
        // Handle input
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Update scene

        // Draw scene

        // Clear everything from last frame
        window.clear();

        // Draw new scene
        window.draw(spriteBackground);

        // Show what we just drew
        window.display();
    }
    

    return 0;
}