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

    std::vector<sf::VideoMode> allVideoModes = VideoMode::getFullscreenModes();
    VideoMode videoMode = VideoMode((int)allVideoModes[0].width, (int)allVideoModes[0].height, allVideoModes[0].bitsPerPixel);
    
    // screenResolution.x = videoMode.width;
    // screenResolution.y = videoMode.height;

    screenResolution.x = 1920;
    screenResolution.y = 1080;
    
    // RenderWindow window(videoMode, "Brain Blast!", Style::Fullscreen);
    // RenderWindow window(videoMode, "Brain Blast!");
    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Brain Blast!");

    // window.setMouseCursorVisible(false);

    // instance THE singleton instance of texture holder
    TextureHolder holder;

    Clock frameTimeClock;

    const int BACKGROUND_SCALE = 4;
    // IntRect backgroundSize = IntRect(0, 0, screenResolution.x, screenResolution.y);
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

    float SPRITE_SCALING = 4;

    Player player(SPRITE_SCALING);
    player.spawn(FloatRect(playArea), screenResolution);

    View gameView;
    gameView.setSize(Vector2f(backgroundSize.width, backgroundSize.height));
    gameView.setCenter(player.getPosition());
    View hudView;
    hudView.setSize(Vector2f(screenResolution.x, screenResolution.y));
    hudView.setCenter(Vector2f((int)(screenResolution.x / 2), (int)(screenResolution.y / 2)));

    // CircleShape centerHud(500);
    // centerHud.setPosition(Vector2f(0, 0));

    const Time LAST_HIT_COOLDOWN = milliseconds(300);
    Time lastHit = seconds(0);

    const int PLAYER_BASE_HEALTH = 5;
    int playerHealth = PLAYER_BASE_HEALTH;

    int score = 0;

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
    Time BULLET_COOLDOWN = milliseconds(200);

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

    Font fontBebas;
    fontBebas.loadFromFile("assets/fonts/BebasNeue-Regular.otf");
    // fontBebas.setSmooth(false);
    
    Text textArmAngle;
    textArmAngle.setFont(fontBebas);
    textArmAngle.setCharacterSize(48);
    textArmAngle.setFillColor(Color::White);
    textArmAngle.setPosition(Vector2f(0, 0));

    Text textHealth;
    textHealth.setFont(fontBebas);
    textHealth.setCharacterSize(32);
    textHealth.setFillColor(Color::White);
    textHealth.setPosition(0, 48);

    Text textScore;
    textScore.setFont(fontBebas);
    textScore.setCharacterSize(32);
    textScore.setFillColor(Color::White);
    textScore.setPosition(0, 80);

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
            lastHit += frameTime;
            // get mouse coords
            // Vector2i mouseScreenPosition = Mouse::getPosition(window);
            Vector2i mouseScreenPosition = Mouse::getPosition();
            // convert mouse coords to world coords
            Vector2f mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, gameView);
            player.update((mouseWorldPosition), frameTime);

            float angle = (atan2(mouseWorldPosition.y - ((player.getArmPosition().y)),
                         mouseWorldPosition.x - ((player.getArmPosition().x) - (15)))
                   * 180 / M_PI);
            armRay.setRotation(angle);
            armRay.setPosition(player.getArmPosition());

            cursor.setPosition(Vector2f(mouseWorldPosition.x, mouseWorldPosition.y));

            barrel.setPosition(player.getBarrelPosition());

            armJoint.setPosition(player.getArmPosition());
            playerPosition.setPosition(player.getPosition());
            gameView.setCenter(player.getPosition());

            for(int i = 0; i < numZombies; i++) {
                zombies[i].update(frameTime, player.getPosition());
            }

            for(int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive() && (lastHit > LAST_HIT_COOLDOWN)) {
                    if (zombies[i].getHitBox().intersects(player.getSpriteBase().getGlobalBounds())) {
                        playerHealth--;
                        lastHit = seconds(0);
                        if (playerHealth <= 0) {
                            // game over idk
                        }
                    }
                }
            }

            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    bullets[i].update(frameTime);

                    // check for collision of hitbox between each bullets and each zombies
                    // TODO: FIX THIS, THIS IS HORRIBLE
                    for (int j = 0; j < numZombies; j++) {
                        if (zombies[j].getHitBox().contains(bullets[i].getPosition())) {
                            // is zombie die after bullet hit
                            if (bullets[i].isInFlight() && zombies[j].isAlive()) {
                                // numZombiesAlive--;

                                if (zombies[j].hit()) {
                                    score++;
                                }

                                bullets[i].stop();
                            }
                        }
                    }
                }
            }

            if (mouseKeyPressed[MouseButton::MOUSE_LEFT] && (lastShot > BULLET_COOLDOWN)) {
                bullets[currentBullet].shoot(player.getBarrelPosition(), mouseWorldPosition, playArea, SPRITE_SCALING - 1);
                currentBullet++;
                if (currentBullet >= MAX_BULLETS - 1) {
                    currentBullet = 0;
                }
                lastShot = seconds(0);
            }

            for (int i = 0; i < sizeof(MovementKey); i++) {
                player.setMovementKeyPressed(i, movementKeyPressed[i]);
            }

            std::stringstream streamTextArmAngle;
            streamTextArmAngle << "armAngle : " << player.getArmAngle();
            textArmAngle.setString(streamTextArmAngle.str());
            
            std::stringstream streamTextHealth;
            streamTextHealth << "health : " << playerHealth;
            textHealth.setString(streamTextHealth.str());

            std::stringstream streamTextScore;
            streamTextScore << "score : " << score;
            textScore.setString(streamTextScore.str());

        // DRAW SCENE
            window.clear(Color(37, 19, 26));

            window.draw(textArmAngle);
            window.draw(textHealth);
            window.draw(textScore);

            window.setView(gameView);
            
                // window.draw(whiteBackground);
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
                        window.draw(bullets[i].getSprite());
                        FloatRect bounds = bullets[i].getSprite().getGlobalBounds();
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
                // window.draw(barrel);
            
            window.setView(hudView);
                // window.draw(textArmAngle);
                window.draw(textArmAngle);
                window.draw(textHealth);
                window.draw(textScore);
                // window.draw(centerHud);

            window.display();
    }

    return 0;
}