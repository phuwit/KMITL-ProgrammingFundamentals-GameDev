#include <SFML/Graphics.hpp>

#include "BrainBlast.hpp"
#include "Player/Player.cpp"
#include "TextureHolder.cpp"

using namespace sf;

int main() {
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;

    screenResolution.x = 1920;
    screenResolution.y = 1080;
    
    // Create a window with the same pixel depth as the desktop
    VideoMode desktop = VideoMode::getDesktopMode();
    // RenderWindow window(VideoMode(screenResolution.y, screenResolution.x), "Brain Blast!", Style::Fullscreen);
    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Brain Blast!");

    Player player(screenResolution);

    RectangleShape whiteBackground(screenResolution);
    CircleShape armJoint(5);
    armJoint.setFillColor(Color::Green);
    armJoint.setPosition(Vector2f(screenResolution.x / 2 - 20, screenResolution.y / 2 - 5));

    CircleShape cursor(5);
    cursor.setFillColor(Color::Green);
    
    RectangleShape armRay(Vector2f(300, 4));
    armRay.setPosition(Vector2f(screenResolution.x / 2 - 20, screenResolution.y / 2 - 5));
    armRay.setOrigin(Vector2f(0, 2));
    armRay.setFillColor(Color::Magenta);

    while (window.isOpen()) {
        // HANDLE INPUTS
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }
            }

        // UPDATE FRAME
            // get mouse coords
            Vector2i mouseScreenPosition = Mouse::getPosition(window);
            // convert mouse coords to world coords
            // mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
            player.update(mouseScreenPosition);

            float angle = (atan2(mouseScreenPosition.y - ((screenResolution.y / 2) - (1 * 5)),
                         mouseScreenPosition.x - ((screenResolution.x / 2) - (4 * 5)))
                   * 180 / M_PI);
            armRay.setRotation(angle);

            cursor.setPosition(Vector2f(mouseScreenPosition.x, mouseScreenPosition.y));

        // DRAW SCENE
            window.clear();
            
            window.draw(whiteBackground);
            window.draw(player.getSpriteBase());
            window.draw(player.getSpriteGun());
            window.draw(player.getSpriteArm());

            window.draw(armJoint);
            window.draw(armRay);
            window.draw(cursor);

            window.display();
    }
}