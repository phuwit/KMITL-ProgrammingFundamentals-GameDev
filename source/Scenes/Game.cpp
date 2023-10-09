#include <sstream>
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.cpp"
#include "../Holders/FontHolder.cpp"
#include "../Zombie/Zombie.cpp"
#include "../Zombie/ZombieHorde.cpp"
#include "../Tools/CreateBackground.cpp"
#include "../Tools/GetScreenshot.cpp"

using namespace sf;

Game::Game(Vector2f screenResolution, Vector2f levelSize) {
    m_BackgroundSize = IntRect(0, 0, levelSize.x, levelSize.y);
    std::stringstream textureBackgroundFilename;
    textureBackgroundFilename << "./assets/sprites/dungeon/pixel-poem/Dungeon_Tileset-x" << M_BACKGROUND_SCALE << ".png";
    m_TextureBackground = TextureHolder::GetTexture(textureBackgroundFilename.str());
    m_TileSize = createBackground(m_Background, m_BackgroundSize, M_BACKGROUND_SCALE);
    m_PlayArea = IntRect(
        m_BackgroundSize.top + m_TileSize, m_BackgroundSize.left + m_TileSize,
        m_BackgroundSize.width - m_TileSize, m_BackgroundSize.height - (2 * m_TileSize));

    m_Player.spawn(FloatRect(m_PlayArea), screenResolution);

    m_GameView.setSize(Vector2f(m_BackgroundSize.width, m_BackgroundSize.height));
    // m_GameView.setCenter(m_Player.getPosition());
    m_HudView.setSize(Vector2f(screenResolution.x, screenResolution.y));
    m_HudView.setCenter(Vector2f(screenResolution.x / 2, screenResolution.y / 2));

    // Zombie zombie;
    // zombie.spawn(Vector2f(200, 200), M_SPRITE_SCALING - 2, ZombieType::ZOMBIE_NORMAL, 1);

    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_HEALTH, true, m_PlayArea));
    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_AMMO,   true, m_PlayArea));
    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_SPEED, false, m_PlayArea));
    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_SCORE, false, m_PlayArea));

    delete[] m_Zombies;
    m_Zombies = createHorde(m_NumZombies, (M_SPRITE_SCALING - 2), m_PlayArea);
}

SceneChange Game::run(RenderWindow &window) {
    Vector2f screenResolution = Vector2f(window.getSize());

    srand((unsigned int)time(0));

    // DEBUG STUFFS

    RectangleShape whiteBackground(screenResolution);

    CircleShape armJoint(5);
    armJoint.setOrigin(armJoint.getRadius(), armJoint.getRadius());
    // armJoint.setFillColor(Color(0, 255, 0, 50));
    armJoint.setFillColor(Color::Green);
    armJoint.setPosition(m_Player.getArmPosition());

    CircleShape playerPosition(5);
    playerPosition.setOrigin(armJoint.getRadius(), armJoint.getRadius());
    // armJoint.setFillColor(Color(0, 255, 0, 50));
    playerPosition.setFillColor(Color::Magenta);

    CircleShape cursor(7);
    cursor.setFillColor(Color::Green);
    
    RectangleShape armRay(Vector2f(300, 4));
    armRay.setPosition(m_Player.getArmPosition());
    armRay.setOrigin(Vector2f(0, 2));
    armRay.setFillColor(Color::Magenta);

    CircleShape barrel(5);
    barrel.setFillColor(Color::Red);
    barrel.setOrigin(barrel.getRadius(), barrel.getRadius());

    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");
    
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

    while (!paused) {
        // HANDLE INPUTS
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::LostFocus) {
                    // return SceneChange(ScenesList::SCENE_PAUSED);
                }
            }

            m_MovementKeyPressed[MovementKey::MOVEMENT_UP] = Keyboard::isKeyPressed(Keyboard::W);
            m_MovementKeyPressed[MovementKey::MOVEMENT_DOWN] = Keyboard::isKeyPressed(Keyboard::S);
            m_MovementKeyPressed[MovementKey::MOVEMENT_LEFT] = Keyboard::isKeyPressed(Keyboard::A);
            m_MovementKeyPressed[MovementKey::MOVEMENT_RIGHT] = Keyboard::isKeyPressed(Keyboard::D);

            m_MouseKeyPressed[MouseButton::MOUSE_LEFT] = Mouse::isButtonPressed(Mouse::Left);
            
            if(Keyboard::isKeyPressed(Keyboard::F2)) {
                std::stringstream screenshotFilename;
                screenshotFilename << "screenshot_" << time(0) << ".png";
                if (getScreenshot(window).copyToImage().saveToFile(screenshotFilename.str())) {
                    std::cout << "screenshot saved to " << screenshotFilename.str() << std::endl;
                }
            }

        // UPDATE FRAME
            Time frameTime = m_FrameTimeClock.restart();
            m_LastShot += frameTime;
            m_LastHit += frameTime;
            // get mouse coords
            // Vector2i mouseScreenPosition = Mouse::getPosition(window);
            Vector2i mouseScreenPosition = Mouse::getPosition(window);
            // convert mouse coords to world coords
            Vector2f mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, m_GameView);
            m_Player.update((mouseWorldPosition), frameTime);
            float angle = (atan2(mouseWorldPosition.y - ((m_Player.getArmPosition().y)),
                         mouseWorldPosition.x - ((m_Player.getArmPosition().x) - (15)))
                   * 180 / M_PI);
            armRay.setRotation(angle);
            armRay.setPosition(m_Player.getArmPosition());

            cursor.setPosition(Vector2f(mouseWorldPosition.x, mouseWorldPosition.y));

            barrel.setPosition(m_Player.getBarrelPosition());

            armJoint.setPosition(m_Player.getArmPosition());
            playerPosition.setPosition(m_Player.getPosition());
            // std::cout << m_Player.getPosition().x << ", " << m_Player.getPosition().y << std::endl;
            // std::cout << m_PlayArea.top << ", " << m_PlayArea.left << ", " << m_PlayArea.width << ", " << m_PlayArea.height << std::endl;
            m_GameView.setCenter(m_Player.getPosition());

            for(int i = 0; i < m_NumZombies; i++) {
                m_Zombies[i].update(frameTime, m_Player.getPosition());
            }

            for(int i = 0; i < m_NumZombies; i++) {
                if (m_Zombies[i].isAlive() && (m_LastHit > M_LAST_HIT_COOLDOWN)) {
                    if (m_Zombies[i].getHitBox().intersects(m_Player.getHitbox())) {
                        m_PlayerHealth--;
                        m_LastHit = seconds(0);
                        if (m_PlayerHealth <= 0) {
                            // game over idk
                            // return SceneChange(ScenesList::SCENE_GAMEOVER);
                        }
                    }
                }
            }

            for (int i = 0; i < M_MAX_BULLETS; i++) {
                if (m_Bullets[i].isInFlight()) {
                    m_Bullets[i].update(frameTime);

                    // check for collision of hitbox between each bullets and each zombies
                    // TODO: FIX THIS, THIS IS HORRIBLE
                    for (int j = 0; j < m_NumZombies; j++) {
                        if (m_Zombies[j].getHitBox().contains(m_Bullets[i].getPosition())) {
                            // is zombie die after bullet hit
                            if (m_Bullets[i].isInFlight() && m_Zombies[j].isAlive()) {
                                if (m_Zombies[j].hit()) {
                                    m_Score++;
                                    m_NumZombiesAlive--;
                                    if (m_NumZombiesAlive <= 0) {
                                        return SceneChange(ScenesList::SCENE_LEVELUP, getScreenshot(window).copyToImage());
                                    }

                                    int randomNumber = (rand() % 5);
                                    if (randomNumber == 0) {
                                        m_PickUpsList[PickupsType::PICKUPS_SCORE].spawnAt(m_Zombies[j].getPosition());
                                    } else if (randomNumber == 1) {
                                        m_PickUpsList[PickupsType::PICKUPS_SPEED].spawnAt(m_Zombies[j].getPosition());
                                    }
                                }
                                m_Bullets[i].stop();
                            }
                        }
                    }
                }
            }

            unsigned int pickuplistsize = sizeof(m_PickUpsList);

            for (int i = 0; i < sizeof(PickupsType); i++) {
                if (m_PickUpsList[i].isSpawned()) {
                    if (m_Player.getHitbox().intersects(m_PickUpsList[i].getPosition())) {
                        // do something
                    }
                }

                m_PickUpsList[i].update(frameTime);
            }

            if (m_MouseKeyPressed[MouseButton::MOUSE_LEFT] && (m_LastShot > M_BULLET_COOLDOWN)) {
                m_Bullets[m_CurrentBullet].shoot(m_Player.getArmPosition(), mouseWorldPosition, m_Player.getBarrelPosition(), m_PlayArea, M_SPRITE_SCALING - 1);
                m_CurrentBullet++;
                if (m_CurrentBullet >= M_MAX_BULLETS - 1) {
                    m_CurrentBullet = 0;
                }
                m_LastShot = seconds(0);
            }

            for (int i = 0; i < sizeof(MovementKey); i++) {
                m_Player.setMovementKeyPressed(i, m_MovementKeyPressed[i]);
            }

            std::stringstream streamTextArmAngle;
            streamTextArmAngle << "armAngle : " << m_Player.getArmAngle();
            textArmAngle.setString(streamTextArmAngle.str());
            
            std::stringstream streamTextHealth;
            streamTextHealth << "health : " << m_PlayerHealth;
            textHealth.setString(streamTextHealth.str());

            std::stringstream streamTextScore;
            streamTextScore << "score : " << m_Score;
            textScore.setString(streamTextScore.str());

        // DRAW SCENE
            window.clear(COLOR_BACKGROUND);

            window.setView(m_GameView);
            
                // window.draw(whiteBackground);
                window.draw(m_Background, &m_TextureBackground);

                for(int i = 0; i < m_NumZombies; i++) {
                    window.draw(m_Zombies[i].getSprite());
                    // window.draw(m_Zombies[i].getDrawableHitbox());
                }

                for (int i = 0; i < sizeof(PickupsType); i++) {
                    if (m_PickUpsList[i].isSpawned()) {
                        window.draw(m_PickUpsList[i].getSprite());
                    }
                }

                for (int i = 0; i < M_MAX_BULLETS; i++) {
                    if (m_Bullets[i].isInFlight()) {
                        window.draw(m_Bullets[i].getSprite());
                        // FloatRect bounds = bullets[i].getSprite().getGlobalBounds();
                        // RectangleShape drawableBounds(Vector2f(bounds.width, bounds.height));
                        // drawableBounds.setPosition(Vector2f(bounds.left, bounds.top));
                        // drawableBounds.setOutlineColor(Color::Green);
                        // drawableBounds.setOutlineThickness(2);
                        // drawableBounds.setFillColor(Color::Transparent);
                        // window.draw(drawableBounds);
                    }
                }
                
                window.draw(m_Player.getSpriteBase());
                window.draw(m_Player.getSpriteGun());
                window.draw(m_Player.getSpriteArm());

                // window.draw(armJoint);
                window.draw(playerPosition);
                // window.draw(armRay);
                window.draw(cursor);
                // window.draw(barrel);
            
            window.setView(m_HudView);
                // window.draw(textArmAngle);
                window.draw(textArmAngle);
                window.draw(textHealth);
                window.draw(textScore);
                // window.draw(centerHud);

            window.display();
    }

    return SceneChange(EXIT);
}

void Game::setPaused() {

}

void Game::setPerks() {

}