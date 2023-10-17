#include <sstream>
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.cpp"
#include "../Holders/FontHolder.cpp"
#include "../Holders/SoundHolder.cpp"
#include "../Zombie/Zombie.cpp"
#include "../Zombie/ZombieHorde.cpp"
#include "../Tools/CreateBackground.cpp"
#include "../Tools/GetScreenshot.cpp"
#include "../Tools/SetOriginCenter.cpp"
#include "../Collision/Collision.hpp"

using namespace sf;

Game::Game(Vector2f screenResolution, Vector2f levelSize) {
    m_ScreenResolution = screenResolution;
    m_BackgroundSize = IntRect(0, 0, levelSize.x, levelSize.y);

    m_GameView.setSize(Vector2f(m_BackgroundSize.width, m_BackgroundSize.height));
    // m_GameView.setCenter(m_Player.getPosition());
    m_HudView.setSize(Vector2f(m_ScreenResolution.x, m_ScreenResolution.y));
    m_HudView.setCenter(Vector2f(m_ScreenResolution.x / 2, m_ScreenResolution.y / 2));

    std::stringstream textureBackgroundFilename;
    textureBackgroundFilename << "./assets/sprites/dungeon/pixel-poem/Dungeon_Tileset-x" << M_BACKGROUND_SCALE << ".png";
    m_TextureBackground = TextureHolder::GetTexture(textureBackgroundFilename.str());
    m_TileSize = createBackground(m_Background, m_BackgroundSize, M_BACKGROUND_SCALE);
    m_PlayArea = IntRect(
            m_BackgroundSize.top + m_TileSize, m_BackgroundSize.left + m_TileSize,
            m_BackgroundSize.width - m_TileSize, m_BackgroundSize.height - (2 * m_TileSize));

    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_HEALTH, true, m_PlayArea));
    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_AMMO,   true, m_PlayArea));
    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_SPEED, false, m_PlayArea));
    m_PickUpsList.push_back(PickUps(PickupsType::PICKUPS_SCORE, false, m_PlayArea));

    m_FontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    m_HudBackground.setSize(Vector2f(600, 150));
    shapeSetOriginCenter(m_HudBackground);
    m_HudBackground.setPosition(screenResolution.x / 2, screenResolution.y - m_HudBackground.getSize().y / 2);
    m_HudBackground.setFillColor(Color(0, 0, 0, 128));

    m_HealthLabel.setFont(m_FontBebas);
    m_HealthLabel.setCharacterSize(32);
    m_HealthLabel.setFillColor(Color::White);
    m_HealthLabel.setString("Health");
    m_HealthLabel.setPosition(m_HudBackground.getPosition().x - m_HudBackground.getSize().x / 2 + m_HudBackgroundPadding,
                              m_HudBackground.getPosition().y + m_HudBackground.getSize().y / 2 - m_HudBackgroundPadding * 2 - m_HealthLabel.getLocalBounds().height);

    m_HealthBar.setSize(Vector2f(m_HudBackground.getSize().x - m_HudBackgroundPadding * 3 - m_HealthLabel.getLocalBounds().width,
                                 m_HealthLabel.getLocalBounds().height));
    m_HealthBar.setPosition(m_HealthLabel.getPosition() + Vector2f(m_HudBackgroundPadding + m_HealthLabel.getLocalBounds().width, m_HudBackgroundPadding));
    m_HealthBar.setFillColor(Color(244, 67, 54));
    m_HealthBarSegmentSize = m_HealthBar.getSize().x / M_PLAYER_BASE_HEALTH;

    m_WaveText.setFont(m_FontBebas);
    m_WaveText.setCharacterSize(40);
    m_WaveText.setFillColor(Color(3, 169, 244));
    stringstream waveStringStream;
    waveStringStream << "Wave  : " << currentLevel;
    m_WaveText.setString(waveStringStream.str());
    m_WaveText.setPosition(m_HudBackground.getPosition().x - m_HudBackground.getSize().x / 2 + m_HudBackgroundPadding,
                           m_HudBackground.getPosition().y - m_HudBackground.getSize().y / 2 + m_HudBackgroundPadding);

    m_ScoreText.setFont(m_FontBebas);
    m_ScoreText.setCharacterSize(40);
    m_ScoreText.setFillColor(Color(38, 166, 154));
    stringstream scoreStringStream;
    scoreStringStream << "Score : " << m_Score;
    m_ScoreText.setString(scoreStringStream.str());
    m_ScoreText.setPosition(m_WaveText.getPosition() + Vector2f(0, m_WaveText.getLocalBounds().height + m_HudBackgroundPadding));

    m_SpareAmmoText.setFont(m_FontBebas);
    m_SpareAmmoText.setCharacterSize(52);
    m_SpareAmmoText.setFillColor(Color(255, 152, 0));
    m_SpareAmmoText.setString(to_string(m_SpareAmmo));
    m_SpareAmmoText.setOrigin(0, m_SpareAmmoText.getLocalBounds().height);
//    m_SpareAmmoText.setPosition(m_HudBackground.getPosition().x + m_HudBackground.getSize().x / 2 - m_HudBackgroundPadding - m_SpareAmmoText.getLocalBounds().width,
//                                m_HudBackground.getPosition().y - m_HudBackground.getSize().y / 2 + m_HudBackgroundPadding + m_HudBackground.getSize().y * 0.2);
    m_SpareAmmoText.setPosition(m_HudBackground.getPosition().x + m_HudBackground.getSize().x / 2 - m_HudBackgroundPadding - m_SpareAmmoText.getLocalBounds().width,
                                m_HudBackground.getPosition().y - m_HudBackground.getSize().y / 2 + m_HudBackgroundPadding + m_HudBackground.getSize().y * 0.1 + m_SpareAmmoText.getLocalBounds().height);

    m_CurrentAmmoText.setFont(m_FontBebas);
    m_CurrentAmmoText.setCharacterSize(96);
    m_CurrentAmmoText.setFillColor(Color(255, 193, 7));
    m_CurrentAmmoText.setString(to_string(m_BulletsInClip));
    m_CurrentAmmoText.setOrigin(0, m_CurrentAmmoText.getLocalBounds().height);
    m_CurrentAmmoText.setPosition(m_SpareAmmoText.getPosition() - Vector2f(m_SpareAmmoText.getLocalBounds().width + m_HudBackgroundPadding, 0));

    m_AmmoLabel.setFont(m_FontBebas);
    m_AmmoLabel.setCharacterSize(32);
    m_AmmoLabel.setFillColor(Color::White);
    m_AmmoLabel.setString("Ammo");
    m_AmmoLabel.setPosition(m_CurrentAmmoText.getPosition() - Vector2f(m_CurrentAmmoText.getLocalBounds().width + m_AmmoLabel.getLocalBounds().width - m_HudBackgroundPadding * 2, m_CurrentAmmoText.getLocalBounds().height - m_HudBackgroundPadding * 2));

    m_SoundLoaded.setBuffer(SoundHolder::GetSound("assets/sfx/synth.ogg"));
    m_SoundHit.setBuffer(SoundHolder::GetSound("assets/sfx/hit.ogg"));
    m_SoundKilled.setBuffer(SoundHolder::GetSound("assets/sfx/killed.ogg"));
    m_SoundShoot.setBuffer(SoundHolder::GetSound("assets/sfx/shoot.ogg"));
    m_SoundPickupLow.setBuffer(SoundHolder::GetSound("assets/sfx/pickup1.ogg"));
    m_SoundPickupHigh.setBuffer(SoundHolder::GetSound("assets/sfx/pickup2.ogg"));

    regenerate();
}

void Game::regenerate() {
    m_Player.spawn(FloatRect(m_PlayArea), m_ScreenResolution);

    for (int i = 0; i < M_MAX_BULLETS; i++) {
        m_Bullets[i].stop();
    }
    m_CurrentBulletIndex = 0;
    m_BulletsInClip = m_ClipSize;
    m_SpareAmmo = 24;

    m_NumZombies = 2 + (3 * currentLevel);
    m_NumZombiesAlive = m_NumZombies;
    delete[] m_Zombies;
    m_Zombies = createHorde(m_NumZombies, (M_SPRITE_SCALING - 1), m_PlayArea);
}

void Game::newGame() {
    currentLevel = 1;
    m_Score = 0;

    regenerate();
}

SceneChange Game::run(RenderWindow &window) {
    srand((unsigned int)time(0));

    m_BuffVisualizerOutline.setRadius(25);
    m_BuffVisualizerOutline.setOrigin(m_BuffVisualizerOutline.getRadius(), m_BuffVisualizerOutline.getRadius());
    m_BuffVisualizerOutline.setFillColor(Color::Transparent);
    m_BuffVisualizerOutline.setOutlineColor(Color::White);
    m_BuffVisualizerOutline.setOutlineThickness(2);
    m_BuffVisualizerOutline.setPosition(100, 100);

    m_BuffVisualizerWiper.setSize(Vector2f(2, 20));
    m_BuffVisualizerWiper.setOrigin(m_BuffVisualizerWiper.getLocalBounds().width / 2, m_BuffVisualizerWiper.getLocalBounds().height);
    m_BuffVisualizerWiper.setPosition(m_BuffVisualizerOutline.getPosition());

    stringstream waveStringStream;
    waveStringStream << "Wave  : " << currentLevel;
    m_WaveText.setString(waveStringStream.str());
    stringstream scoreStringStream;
    scoreStringStream << "Score : " << m_Score;
    m_ScoreText.setString(scoreStringStream.str());
    m_SpareAmmoText.setString(to_string(m_SpareAmmo));
    m_CurrentAmmoText.setString(to_string(m_BulletsInClip));

    m_SoundLoaded.play();

    while (!paused) {
        // HANDLE INPUTS
            Event event;
            while (window.pollEvent(event)) {
                // if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::LostFocus) {
                if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                    return {ScenesList::SCENE_PAUSED, getScreenshot(window).copyToImage()};
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
            m_AnimationTimer += frameTime;

            if (frameTime > seconds(2)) {
                continue;
            }

            m_LastShot += frameTime;
            m_LastHit += frameTime;
            // get mouse coords
            // Vector2i mouseScreenPosition = Mouse::getPosition(window);
            Vector2i mouseScreenPosition = Mouse::getPosition(window);
            // convert mouse coords to world coords
            Vector2f mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, m_GameView);
            m_Player.update((mouseWorldPosition), frameTime);

            // std::cout << m_Player.getPosition().x << ", " << m_Player.getPosition().y << std::endl;
            // std::cout << m_PlayArea.top << ", " << m_PlayArea.left << ", " << m_PlayArea.width << ", " << m_PlayArea.height << std::endl;
            m_GameView.setCenter(m_Player.getPosition());

            for(int i = 0; i < m_NumZombies; i++) {
                m_Zombies[i].update(frameTime, m_Player.getPosition());
            }

            for(int i = 0; i < m_NumZombies; i++) {
                if (m_Zombies[i].isAlive() && (m_LastHit > M_LAST_HIT_COOLDOWN)) {
                    if (m_Zombies[i].getHitBox().intersects(m_Player.getHitbox())) {
                        if(Collision::pixelPerfectTest(m_Zombies[i].getSprite(), m_Player.getSpriteBase())) {
                            m_PlayerHealth--;
                            m_LastHit = seconds(0);
                            m_SoundHit.play();

                            m_HealthBar.setSize(
                                    Vector2f(m_HealthBarSegmentSize * m_PlayerHealth, m_HealthBar.getSize().y));
                            if (m_PlayerHealth <= 0) {
                                // game over idk
                                return {ScenesList::SCENE_GAMEOVER};
                            }
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
                            if (Collision::pixelPerfectTest(m_Zombies[j].getSprite(), m_Bullets[i].getSprite())) {
                                // is zombie die after bullet hit
                                if (m_Bullets[i].isInFlight() && m_Zombies[j].isAlive()) {
                                    if (m_Zombies[j].hit()) {
                                        m_SoundKilled.play();

                                        m_Score += (100 * m_ScoreMultiplier);
                                        if (m_Zombies[j].getTimeSinceSpawned() < M_SCORE_BONUS_MAX_TIME) {
                                            float timeToKill = M_SCORE_BONUS_MAX_TIME.asSeconds() -
                                                               m_Zombies[j].getTimeSinceSpawned().asSeconds();
                                            m_Score += ceil(timeToKill * 10);
                                        }

                                        m_NumZombiesAlive--;
                                        if (m_NumZombiesAlive <= 0) {
                                            return SceneChange(ScenesList::SCENE_LEVELUP,
                                                               getScreenshot(window).copyToImage());
                                        }

                                        int randomNumber = (rand() % 8);
                                        if (randomNumber == 0) {
                                            m_PickUpsList[PickupsType::PICKUPS_SCORE].spawnAt(
                                                    m_Zombies[j].getPosition());
                                            m_PickupsSprite = m_PickUpsList[PickupsType::PICKUPS_SCORE].getSprite();
                                        } else if (randomNumber == 1) {
                                            m_PickUpsList[PickupsType::PICKUPS_SPEED].spawnAt(
                                                    m_Zombies[j].getPosition());
                                            m_PickupsSprite = m_PickUpsList[PickupsType::PICKUPS_SPEED].getSprite();
                                        }

                                        scoreStringStream.str("");
                                        scoreStringStream << "Score  : " << m_Score;
                                        m_ScoreText.setString(scoreStringStream.str());
                                    }
                                    m_Bullets[i].stop();

                                    m_SoundHit.play();
                                }
                            }
                        }
                    }
                }
            }

            unsigned int pickuplistsize = m_PickUpsList.size();
            for (unsigned int i = 0; i < pickuplistsize; i++) {
                if (m_PickUpsList[i].isSpawned()) {
                    if (m_Player.getHitbox().intersects(m_PickUpsList[i].getPosition())) {
                        m_BuffType = (PickupsType)i;
                        handlePickUps_((PickupsType)i, m_PickUpsList[i].take(), m_PickUpsList[i].getBuffDuration());
                    }
                }

                m_PickUpsList[i].update(frameTime);
            }

            if (m_BuffTimer > seconds(0)) {
                m_BuffTimer -= frameTime;
                m_BuffVisualizerWiper.rotate(m_BuffVisualizerAnglePerSecond * frameTime.asSeconds());
                if (m_BuffTimer <= seconds(0)) {
                    removeBuff_(m_BuffType);
                }
            }

            if (m_MouseKeyPressed[MouseButton::MOUSE_LEFT] && (m_LastShot > m_BulletCooldown)) {
                if (m_BulletsInClip > 0) {
                    m_Bullets[m_CurrentBulletIndex].shoot(m_Player.getArmPosition(), mouseWorldPosition,
                                                          m_Player.getBarrelPosition(), m_PlayArea,
                                                          M_SPRITE_SCALING);
                    m_BulletsInClip -= 1;
                    m_CurrentBulletIndex++;
                    if (m_CurrentBulletIndex >= M_MAX_BULLETS - 1) {
                        m_CurrentBulletIndex = 0;
                    }
                    m_LastShot = seconds(0);

                    m_SoundShoot.play();
                }

                m_CurrentAmmoText.setString(to_string(m_BulletsInClip));
            }

            if (Keyboard::isKeyPressed(Keyboard::R) && (m_BulletsInClip < m_ClipSize)) {
                // can reload to max clip size
                int bulletsDelta = m_ClipSize - m_BulletsInClip;
                if (bulletsDelta > m_SpareAmmo) {
                    bulletsDelta = m_SpareAmmo;
                }
                m_BulletsInClip += bulletsDelta;
                m_SpareAmmo -= bulletsDelta;

                m_CurrentAmmoText.setString(to_string(m_BulletsInClip));
                m_SpareAmmoText.setString(to_string(m_SpareAmmo));
            }

            for (unsigned int i = 0; i < (unsigned int)sizeof(MovementKey); i++) {
                m_Player.setMovementKeyPressed(i, m_MovementKeyPressed[i]);
            }

            if (m_AnimationTimer > M_TIME_BETWEEN_ANIMATION) {
                m_Player.animate();
                for (int i = 0; i < m_NumZombies; i++) {
                    m_Zombies[i].animate();
                }
                m_AnimationTimer = seconds(0);
            }

        // DRAW SCENE
            window.clear(COLOR_BACKGROUND);

            window.setView(m_GameView);
            
                // window.draw(whiteBackground);
                window.draw(m_Background, &m_TextureBackground);

                for(int i = 0; i < m_NumZombies; i++) {
                    window.draw(m_Zombies[i].getSprite());
//                     window.draw(m_Zombies[i].getDrawableHitbox());
                }

                for (unsigned int i = 0; i < (unsigned int)sizeof(PickupsType); i++) {
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
            
            window.setView(m_HudView);
                window.draw(m_HudBackground);
                window.draw(m_HealthBar);
                window.draw(m_HealthLabel);
                window.draw(m_ScoreText);
                window.draw(m_AmmoLabel);
                window.draw(m_CurrentAmmoText);
                window.draw(m_SpareAmmoText);
                window.draw(m_WaveText);

                if (m_BuffTimer > seconds(0)) {
                    window.draw(m_BuffSprite);
                    window.draw(m_BuffVisualizerOutline);
                    window.draw(m_BuffVisualizerWiper);
                }

            window.display();
    }

    return {EXIT};
}

void Game::setPaused() {

}

void Game::setPerks(int perks) {
//    const std::string UPGRADE_TEXT[NUM_UPGRADES] = {
//            "Increased rate of fire",
//            "Increased clip size (next reload)",
//            "Increased max health",
//            "More and better health pickups",
//            "More and better ammo pickups"
//    };
    if (perks == 0) {
        m_BulletCooldown -= milliseconds(m_BASE_BULLET_COOLDOWN.asMilliseconds() / 10);
    } else if (perks == 1) {
        m_ClipSize += 2;
    } else if (perks == 2) {
        m_PlayerHealth = m_PlayerMaxHealth + 1;
        m_HealthBarSegmentSize = m_HealthBar.getSize().x / m_PlayerMaxHealth;
        m_HealthBar.setSize(Vector2f(m_HealthBarSegmentSize * m_PlayerHealth, m_HealthBar.getSize().y));
    } else if (perks == 3) {
        m_PickUpsList[PickupsType::PICKUPS_HEALTH].upgrade();
    } else if (perks == 4) {
        m_PickUpsList[PickupsType::PICKUPS_AMMO].upgrade();
    }
}

unsigned int Game::getScore() {
    return m_Score;
}

void Game::handlePickUps_(PickupsType pickUpsType, int pickupValue, Time buffDuration) {
    if (pickUpsType == PickupsType::PICKUPS_HEALTH) {
        m_PlayerHealth += pickupValue;
        if (m_PlayerHealth > m_PlayerMaxHealth) {
            m_PlayerHealth = m_PlayerMaxHealth;
        }
        m_HealthBar.setSize(Vector2f(m_HealthBarSegmentSize * m_PlayerHealth, m_HealthBar.getSize().y));
        m_SoundPickupLow.play();
    } else if (pickUpsType == PickupsType::PICKUPS_AMMO) {
        m_SpareAmmo += pickupValue;
        m_SpareAmmoText.setString(to_string(m_SpareAmmo));
        m_SoundPickupLow.play();
    } else if (pickUpsType == PickupsType::PICKUPS_SPEED) {
        m_Player.setSpeedWithMultiplier(pickupValue);
        m_BuffTimer = buffDuration;
        m_BuffVisualizerAnglePerSecond = 360 / buffDuration.asSeconds();
        m_BuffSprite = m_PickupsSprite;
        m_BuffSprite.setScale(0.75, 0.75);
        m_BuffSprite.setPosition(m_ScreenResolution.x - m_BuffSprite.getLocalBounds().width - 10, m_BuffSprite.getLocalBounds().height - 10);
        m_BuffVisualizerOutline.setPosition(m_BuffSprite.getPosition() - Vector2f(m_BuffSprite.getLocalBounds().width + 10, 0));
        m_BuffVisualizerWiper.setPosition(m_BuffVisualizerOutline.getPosition());
        m_SoundPickupHigh.play();
    } else if (pickUpsType == PickupsType::PICKUPS_SCORE) {
        m_ScoreMultiplier = pickupValue;
        m_BuffTimer = buffDuration;
        m_BuffVisualizerAnglePerSecond = 360 / buffDuration.asSeconds();
        m_BuffSprite = m_PickupsSprite;
        m_BuffSprite.setScale(0.75, 0.75);
        m_BuffSprite.setPosition(m_ScreenResolution.x - m_BuffSprite.getLocalBounds().width - 10, m_BuffSprite.getLocalBounds().height - 10);
        m_BuffVisualizerOutline.setPosition(m_BuffSprite.getPosition() - Vector2f(m_BuffSprite.getLocalBounds().width + 10, 0));
        m_BuffVisualizerWiper.setPosition(m_BuffVisualizerOutline.getPosition());
        m_SoundPickupHigh.play();
    }
}

void Game::removeBuff_(PickupsType pickUpsType) {
    if (pickUpsType == PickupsType::PICKUPS_SPEED) {
        m_Player.setSpeedReset();
    } else if (pickUpsType == PickupsType::PICKUPS_SCORE) {
        m_ScoreMultiplier = 1;
    }
}
