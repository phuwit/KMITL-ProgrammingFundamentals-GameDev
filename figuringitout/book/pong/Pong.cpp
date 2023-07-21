#include <sstream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Bat.h"
#include "Bat.cpp"
#include "Ball.h"
#include "Ball.cpp"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main () {
    // Create a window
    VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderWindow window(vm, "Pong");

    int score = 0;
    int lives = 3;

    // Create a bat at center bottom
    Bat bat(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 40);
    // Create a ball
    Ball ball(1920 / 2, 0);

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

    bool acceptScore = true;

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
            ball.update(dt);

            // bottom collision detection
            if (ball.getPosition().top > window.getSize().y) {
                acceptScore = false;
                ball.reboundBottom();
                lives--;

                if (lives <= 0) {
                    score = 0;
                    lives = 3;
                }
            }

            // top collision
            if (ball.getPosition().top < 0) {
                ball.reboundBatOrTop();
                if (acceptScore) {
                    score++;
                }
            }

            // side collision
            if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
                ball.reboundSides();
            }

            // ball and bat collision
            if (ball.getPosition().intersects(bat.getPosition())) {
                acceptScore = true;
                ball.reboundBatOrTop();
            }

            // Update hud
            std::stringstream ss;
            ss << "Score : " << score << " Lives : " << lives;
            hud.setString(ss.str());

        // Draw elements
            window.clear();

            window.draw(hud);
            window.draw(bat.getShape());
            window.draw(ball.getShape());

            window.display();
    }
    
}