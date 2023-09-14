#include <sstream>
#include <array>
#include <SFML/Graphics.hpp>

#include "BrainBlast.hpp"
#include "CommonEnum.hpp"
#include "CreateBackground.cpp"
#include "TextureHolder.cpp"
#include "Player/Player.cpp"
#include "Bullet/Bullet.cpp"
#include "Zombie/Zombie.cpp"
#include "Zombie/ZombieHorde.cpp"

using namespace sf;

int main() {
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;

    screenResolution.x = 1280;
    screenResolution.y = 720;
    
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

    float SPRITE_SCALING = 4;

    Player player(SPRITE_SCALING);
    player.spawn(FloatRect(playArea), screenResolution);

    // Bullets stuffs
    const int MAX_BULLETS = 100;
    Bullet bullets[MAX_BULLETS];
    // current bullet index in array
    int currentBullet = 0;
    int bulletsSpare = 24;
    int clipSize = 6;
    int bulletsInClip = clipSize;
    float fireRate = 1;
    // last shot timestamp
    Time lastShot;
    Time BULLET_COOLDOWN = milliseconds(100);

    bool movementKeyPressed[sizeof(MovementKey)];
    bool mouseKeyPressed[sizeof(MouseButton)];

    enum class GameState {MENU, PLAYING, PAUSED, GAME_OVER};
    int stage = 0;

    // Zombie zombie;
    // zombie.spawn(Vector2f(200, 200), SPRITE_SCALING - 2, ZombieType::ZOMBIE_NORMAL, 1);

    int numZombies = 20;
    int numZombiesAlive;
    Zombie* zombies = nullptr;
    
    delete[] zombies;
    zombies = createHorde(numZombies, (SPRITE_SCALING - 2), playArea);
    numZombiesAlive = numZombies;

    // DEBUG STUFFS

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

    Text textArmAngle;
    Font fontBebas;
    fontBebas.loadFromFile("assets/fonts/BebasNeue-Regular.otf");
    textArmAngle.setFont(fontBebas);
    textArmAngle.setFillColor(Color::White);
    textArmAngle.setCharacterSize(48);
    textArmAngle.setPosition(Vector2f(0, 0));

    // END DEBUG STUFFS

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

        // UPDATE FRAME
            Time frameTime = frameTimeClock.restart();
            lastShot += frameTime;
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

            barrel.setPosition(player.getBarrelPosition());

            armJoint.setPosition(player.getArmPosition());
            playerPosition.setPosition(player.getPosition());

            for(int i = 0; i < numZombies; i++) {
                zombies[i].update(frameTime, player.getPosition());
            }

            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    bullets[i].update(frameTime);

                    // check for collision of hitbox between each bullets and each zombies
                    // TODO: FIX THIS, THIS IS HORRIBLE
                    for (int j = 0; j < numZombies; j++) {
                        if (bullets[i].getShape().getGlobalBounds().intersects(zombies[j].getPosition())) {
                            // is zombie die after bullet hit
                            if (zombies[j].hit()) {
                                numZombiesAlive--;
                            }
                        }
                    }


                }
            }

            std::stringstream streamTextArmAngle;
            streamTextArmAngle << "armAngle : " << player.getArmAngle();
            textArmAngle.setString(streamTextArmAngle.str());

            if (mouseKeyPressed[MouseButton::MOUSE_LEFT] && (lastShot > BULLET_COOLDOWN)) {
                bullets[currentBullet].shoot(player.getBarrelPosition(), Vector2f(mouseScreenPosition), playArea, SPRITE_SCALING - 1);
                currentBullet++;
                if (currentBullet >= MAX_BULLETS - 1) {
                    currentBullet = 0;
                }
                lastShot = seconds(0);
            }

            for (int i = 0; i < sizeof(MovementKey); i++) {
                player.setMovementKeyPressed(i, movementKeyPressed[i]);
            }
            
        // DRAW SCENE
            window.clear();
            
            window.draw(whiteBackground);
            window.draw(background, &textureBackground);
            window.draw(player.getSpriteBase());
            window.draw(player.getSpriteGun());
            window.draw(player.getSpriteArm());

            for(int i = 0; i < numZombies; i++) {
                window.draw(zombies[i].getSprite());
                window.draw(zombies[i].getDrawableHitbox());
            }

            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    window.draw(bullets[i].getShape());
                    FloatRect bounds = bullets[i].getShape().getGlobalBounds();
                    RectangleShape drawableBounds(Vector2f(bounds.width, bounds.height));
                    drawableBounds.setPosition(Vector2f(bounds.left, bounds.top));
                    drawableBounds.setOutlineColor(Color::Green);
                    drawableBounds.setOutlineThickness(2);
                    drawableBounds.setFillColor(Color::Transparent);
                    window.draw(drawableBounds);
                }
            }


            // window.draw(armJoint);
            // window.draw(playerPosition);
            // window.draw(armRay);
            window.draw(cursor);
            window.draw(barrel);
            window.draw(textArmAngle);

            window.display();
    }

    return 0;
}