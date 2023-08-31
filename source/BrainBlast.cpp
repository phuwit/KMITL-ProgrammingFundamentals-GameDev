#include <sstream>
#include <SFML/Graphics.hpp>

#include "BrainBlast.hpp"
#include "CommonEnum.hpp"
#include "CreateBackground.cpp"
#include "TextureHolder.cpp"
#include "Player/Player.cpp"
#include "Bullet/Bullet.cpp"

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

    View gameView;
    gameView.setSize(Vector2f(backgroundSize.width, backgroundSize.height));
    View hudView;
    hudView.setSize(screenResolution);

    Player player;
    player.spawn(playArea, screenResolution);

    Bullet bullet;

    bool movementKeyPressed[sizeof(MovementKey)];
    bool mouseKeyPressed[sizeof(MouseButton)];

    enum class GameState {MENU, PLAYING, PAUSED, GAME_OVER};
    int stage = 0;
    GameState currentGameState = GameState::MENU;

    RectangleShape whiteBackground(screenResolution);

    CircleShape armJoint(5);
    armJoint.setOrigin(armJoint.getRadius(), armJoint.getRadius());
    // armJoint.setFillColor(Color(0, 255, 0, 50));
    armJoint.setFillColor(Color::Green);
    armJoint.setPosition(player.getArmPosition());

    CircleShape playerPosition(5);
    playerPosition.setOrigin(armJoint.getRadius(), armJoint.getRadius());
    // armJoint.setFillColor(Color(0, 255, 0, 50));
    playerPosition.setFillColor(Color::Magenta);

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

            movementKeyPressed[MovementKey::MOVEMENT_UP] = Keyboard::isKeyPressed(Keyboard::W);
            movementKeyPressed[MovementKey::MOVEMENT_DOWN] = Keyboard::isKeyPressed(Keyboard::S);
            movementKeyPressed[MovementKey::MOVEMENT_LEFT] = Keyboard::isKeyPressed(Keyboard::A);
            movementKeyPressed[MovementKey::MOVEMENT_RIGHT] = Keyboard::isKeyPressed(Keyboard::D);

            mouseKeyPressed[MouseButton::MOUSE_LEFT] = Mouse::isButtonPressed(Mouse::Left);

            if (mouseKeyPressed[MouseButton::MOUSE_LEFT]) {
                bullet.shoot(player.getArmPosition(), Vector2f(Mouse::getPosition()), playArea);
            }

            for (int i = 0; i < sizeof(MovementKey); i++) {
                player.setMovementKeyPressed(i, movementKeyPressed[i]);
            }

        // UPDATE FRAME
            Time frameTime = frameTimeClock.restart();
            // get mouse coords
            Vector2i mouseScreenPosition = Mouse::getPosition(window);
            // convert mouse coords to world coords
            // mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
            player.update(mouseScreenPosition, frameTime);

            float angle = (atan2(mouseScreenPosition.y - ((player.getArmPosition().y)),
                         mouseScreenPosition.x - ((player.getArmPosition().x) - (15)))
                   * 180 / M_PI);
            armRay.setRotation(angle);
            armRay.setPosition(player.getArmPosition());

            cursor.setPosition(Vector2f(mouseScreenPosition.x, mouseScreenPosition.y));

            barrel.setPosition(player.getArmPosition() + Vector2f(23 * 5 * cos(player.getArmAngle() * (M_PI / 180)), 23 * 5 * sin(player.getArmAngle() * (M_PI / 180))));

            armJoint.setPosition(player.getArmPosition());
            playerPosition.setPosition(player.getPosition());
            bullet.update(frameTime);
            
        // DRAW SCENE
            window.clear();
            
            window.draw(whiteBackground);
            window.draw(background, &textureBackground);
            window.draw(player.getSpriteBase());
            window.draw(player.getSpriteGun());
            window.draw(player.getSpriteArm());
            window.draw(bullet.getShape());

            // window.draw(armJoint);
            // window.draw(playerPosition);
            // window.draw(armRay);
            window.draw(cursor);
            // window.draw(barrel);

            window.display();
    }
}