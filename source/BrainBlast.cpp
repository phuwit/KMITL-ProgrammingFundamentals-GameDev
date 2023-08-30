#include <sstream>
#include <SFML/Graphics.hpp>

#include "BrainBlast.hpp"
#include "CreateBackground.cpp"
#include "TextureHolder.cpp"
#include "Player/Player.cpp"

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

    // instance THE singleton instance of texture holder
    TextureHolder holder;

    Clock frameTimeClock;

    const int BACKGROUND_SCALE = 4;
    IntRect backgroundSize = IntRect(0, 0, screenResolution.x, screenResolution.y);
    Texture textureBackground;
    std::stringstream textureBackgroundFilename;
    textureBackgroundFilename << "assets/sprites/dungeon/pixel-poem/Dungeon_Tileset-x" << BACKGROUND_SCALE << ".png";
    textureBackground = TextureHolder::GetTexture(textureBackgroundFilename.str());
    VertexArray background;
    int tileSize = createBackground(background, backgroundSize, BACKGROUND_SCALE);
    IntRect playArea = IntRect(
        backgroundSize.top + tileSize, backgroundSize.left + tileSize,
        backgroundSize.width - tileSize, backgroundSize.height - tileSize);

    Player player;
    player.spawn(playArea, screenResolution);

    RectangleShape whiteBackground(screenResolution);
    CircleShape armJoint(5);
    armJoint.setOrigin(armJoint.getRadius(), armJoint.getRadius());
    // armJoint.setFillColor(Color(0, 255, 0, 50));
    armJoint.setFillColor(Color::Green);
    armJoint.setPosition(player.getArmPosition());

    CircleShape cursor(7);
    cursor.setFillColor(Color::Green);
    
    RectangleShape armRay(Vector2f(300, 4));
    armRay.setPosition(player.getArmPosition());
    armRay.setOrigin(Vector2f(0, 2));
    armRay.setFillColor(Color::Magenta);

    CircleShape barrel(5);
    barrel.setFillColor(Color::Red);
    barrel.setOrigin(barrel.getRadius(), barrel.getRadius());

    while (window.isOpen()) {
        // HANDLE INPUTS
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }
            }

        // UPDATE FRAME
            Time frameTime = frameTimeClock.restart();
            // get mouse coords
            Vector2i mouseScreenPosition = Mouse::getPosition(window);
            // convert mouse coords to world coords
            // mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
            player.update(mouseScreenPosition, frameTime);

            float angle = (atan2(mouseScreenPosition.y - ((screenResolution.y / 2)),
                         mouseScreenPosition.x - ((screenResolution.x / 2) - (15)))
                   * 180 / M_PI);
            armRay.setRotation(angle);

            cursor.setPosition(Vector2f(mouseScreenPosition.x, mouseScreenPosition.y));

            barrel.setPosition(player.getArmPosition() + Vector2f(23 * 5 * cos(player.getArmAngle() * (M_PI / 180)), 23 * 5 * sin(player.getArmAngle() * (M_PI / 180))));

            
        // DRAW SCENE
            window.clear();
            
            window.draw(whiteBackground);
            window.draw(background, &textureBackground);
            window.draw(player.getSpriteBase());
            window.draw(player.getSpriteGun());
            window.draw(player.getSpriteArm());

            // window.draw(armJoint);
            // window.draw(armRay);
            window.draw(cursor);
            // window.draw(barrel);

            window.display();
    }
}