#include <sstream>
#include "Bat.h"
#include "Bat.cpp"

#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main () {
    // Create a window
    VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderWindow window(vm, "Pong");

    int score = 0;
    int lives = 3;

    // Create a bat at center bottom
    Bat bat(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20);
    // TODO: Add a ball

    // Load a font
    Font font;
    font.loadFromFile("fonts/BebasNeue-Regular.otf");
    // Create a hud
    Text hud;
    hud.setFont(font);
    hud.setCharacterSize(60);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    // controlling time itself
    Clock clock;

    // Game loop
    while (window.isOpen())
    {
        // Handle input
            Event event;

            // Handle quitting
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
            }

            // Handle pressing and releasing arrow keys
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                bat.moveLeft();
            }
            else {
                bat.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                bat.moveRight();
            }
            else {
                bat.stopRight();
            }

        
        // Update elements
            // Get delta time
            Time dt = clock.restart();
            
            bat.update(dt);

            // Update hud
            std::stringstream ss;
            ss << "Score : " << score << " Lives : " << lives;
            hud.setString(ss.str());

        // Draw elements
            window.clear();

            window.draw(hud);
            window.draw(bat.getShape());

            window.display();
    }
    
}