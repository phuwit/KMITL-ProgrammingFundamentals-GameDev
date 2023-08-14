#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Arena.hpp"
#include "TextureHolder.cpp"
#include "CreateBackground.cpp"
#include "Player.cpp"
#include "Pickups.cpp"
#include "Bullet.cpp"
#include "Zombie.cpp"
#include "CreateHorde.cpp"

using namespace sf;

int main () {
    // The game will be in one of 4 states
    enum class State {PAUSED, LEVEL_UP, GAME_OVER, IN_GAME};
    // Starting in game over state
    State state = State::GAME_OVER;
    
    // Get screen resolution and create a window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    resolution.x = 1920;
    resolution.y = 1080;

    // RenderWindow window(VideoMode(resolution.x, resolution.y), "Arena", Style::Fullscreen);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Arena");

    // Create a main view
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    // Create a HUD view
    View hudView(FloatRect(0, 0, resolution.x, resolution.y));

    // controlling time
    Clock clock;

    // How long have it been in IN_GAME state
    Time gameTimeTotal;
    // mouse position relative to world coords
    Vector2f mouseWorldPosition;
    // mouse position relative to screen
    Vector2i mouseScreenPosition;

    // instance THE singleton instance of texture holder
    TextureHolder holder;

    // Create an instance of Player
    Player player;

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

    // hide pointers and replace it with crosshairs
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);

    // arena boundaries
    IntRect arena;

    // Create the background
    VertexArray background;
    Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

    // Prepare zombie horde
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    // create pickups
    Pickups healthPickup(Pickups::PickupTypes::health);
    Pickups ammoPickup(Pickups::PickupTypes::ammo);

    // storing scores
    int score = 0;
    int hiScore = 0;
    const int scorePerZombieKilled = 10;

    // load up hiscore from a text file
    ifstream inputFile("gamedata/scores.txt");
    if (inputFile.is_open()) {
        // reads data and put into hiScore var
        inputFile >> hiScore;
        inputFile.close();
    }

    // home-gameover screen
    Sprite spriteGameOver;
    spriteGameOver.setTexture(TextureHolder::GetTexture("graphics/background.png"));
    spriteGameOver.setPosition(0, 0);

    // create a sprite for ammo icon
    Sprite spriteAmmoIcon;
    spriteAmmoIcon.setTexture(TextureHolder::GetTexture("graphics/ammo_icon.png"));
    spriteAmmoIcon.setPosition(20, 980);

    // load font
    Font font;
    font.loadFromFile("fonts/BebasNeue-Regular.otf");

    // Texts for hud
        // Paused
        Text pausedText;
        pausedText.setFont(font);
        pausedText.setCharacterSize(155);
        pausedText.setFillColor(Color::White);
        pausedText.setPosition(400, 400);
        pausedText.setString("Press Enter \nto continue");

        // Game Over
        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(125);
        gameOverText.setFillColor(Color::White);
        gameOverText.setPosition(250, 850);
        gameOverText.setString("Press Enter to play");

        // Levelling up
        Text levelUpText;
        levelUpText.setFont(font);
        levelUpText.setCharacterSize(80);
        levelUpText.setFillColor(Color::White);
        levelUpText.setPosition(150, 250);
        std::stringstream levelUpStream;
        levelUpStream <<
            "1- Increased rate of fire" <<
            "\n2- Increased clip size(next reload)" <<
            "\n3- Increased max health" <<
            "\n4- Increased run speed" <<
            "\n5- More and better health pickups" <<
            "\n6- More and better ammo pickups";
        levelUpText.setString(levelUpStream.str());

        // Ammo
        Text ammoText;
        ammoText.setFont(font);
        ammoText.setCharacterSize(55);
        ammoText.setFillColor(Color::White);
        ammoText.setPosition(200, 980);

        // Score
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(55);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(20, 0);

        // Hi Score
        Text hiScoreText;
        hiScoreText.setFont(font);
        hiScoreText.setCharacterSize(55);
        hiScoreText.setFillColor(Color::White);
        hiScoreText.setPosition(1400, 0);
        std::stringstream hiScoreStream;
        hiScoreStream << "Hi Score:" << hiScore;
        hiScoreText.setString(hiScoreStream.str());

        // Zombies remaining
        Text zombiesRemainingText;
        zombiesRemainingText.setFont(font);
        zombiesRemainingText.setCharacterSize(55);
        zombiesRemainingText.setFillColor(Color::White);
        zombiesRemainingText.setPosition(1500, 980);
        zombiesRemainingText.setString("Zombies: 100");

        // Wave number
        int wave = 0;
        Text waveNumberText;
        waveNumberText.setFont(font);
        waveNumberText.setCharacterSize(55);
        waveNumberText.setFillColor(Color::White);
        waveNumberText.setPosition(1250, 980);
        waveNumberText.setString("Wave: 0");

    // Health bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(450, 980);

    // no need to update hud every single frame
    // how oftern shoud the HUD updates (in frames) 
    const int HUD_UPDATE_INTERVAL = 200;
    int framesSinceLastHudUpdate = 0;

    // Prepare sounds stuffs
        // Prepare the hit sound
        SoundBuffer hitBuffer;
        hitBuffer.loadFromFile("sound/hit.wav");
        Sound soundHit;
        soundHit.setBuffer(hitBuffer);

        // Prepare the splat sound
        SoundBuffer splatBuffer;
        splatBuffer.loadFromFile("sound/splat.wav");
        Sound soundSplat;
        soundSplat.setBuffer(splatBuffer);

        // Prepare the shoot sound
        SoundBuffer shootBuffer;
        shootBuffer.loadFromFile("sound/shoot.wav");
        Sound soundShoot;
        soundShoot.setBuffer(shootBuffer);

        // Prepare the reload sound
        SoundBuffer reloadBuffer;
        reloadBuffer.loadFromFile("sound/reload.wav");
        Sound soundReload;
        soundReload.setBuffer(reloadBuffer);

        // Prepare the failed sound
        SoundBuffer reloadFailedBuffer;
        reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
        Sound soundReloadFailed;
        soundReloadFailed.setBuffer(reloadFailedBuffer);

        // Prepare the levelup sound
        SoundBuffer levelUpBuffer;
        levelUpBuffer.loadFromFile("sound/powerup.wav");
        Sound soundLevelUp;
        soundLevelUp.setBuffer(levelUpBuffer);

        // Prepare the pickup sound
        SoundBuffer pickupBuffer;
        pickupBuffer.loadFromFile("sound/pickup.wav");
        Sound soundPickup;
        soundPickup.setBuffer(pickupBuffer);

    // game loop
    while (window.isOpen()) {
        // HANDLE INPUT
        // Handle events by polling
            Event event;
            while (window.pollEvent(event)) {
                // handle quitting
                if (Keyboard::isKeyPressed(Keyboard::Escape) ||
                (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C)) ||
                event.type == Event::Closed) {
                    window.close();
                }

                // changing states 
                if (event.type == Event::KeyPressed) {
                    // pause game when playing
                    if (event.key.code == Keyboard::Return && state == State::IN_GAME) {
                        state = State::PAUSED;
                    }
                    // restart game when paused
                    else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
                        state = State::IN_GAME;
                        // restart clock so there are no frame jumps (objects updating after a long long clock cycle)
                        clock.restart();
                    }
                    // new game when game over
                    else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                        state = State::LEVEL_UP;
                        // restart clock so there are no frame jumps
                        clock.restart();

                        // prepare for next game
                        wave = 0;
                        currentBullet = 0;
                        bulletsInClip = 6;
                        clipSize = 6;
                        fireRate = 1;
                        player.resetPlayerStats();
                    }
                    if (state == State::IN_GAME) {
                        // do something
                    }
                }
            } // End event polling
            
            // Handle events while in game
            // Handle movement keys
            if (state == State::IN_GAME) {
                if (Keyboard::isKeyPressed(Keyboard::W)) {
                    player.moveUp();
                }
                else {
                    player.stopUp();
                }
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    player.moveDown();
                }
                else {
                    player.stopDown();
                }
                if (Keyboard::isKeyPressed(Keyboard::D)) {
                    player.moveRight();
                }
                else {
                    player.stopRight();
                }
                if (Keyboard::isKeyPressed(Keyboard::A)) {
                    player.moveLeft();
                }
                else {
                    player.stopLeft();
                }
                // End handle movement keys

                // Handle reloads
                if (Keyboard::isKeyPressed(Keyboard::R)) {
                        if (bulletsSpare >= clipSize) {
                        // can reload to max clip size
                        int bulletsDelta = clipSize - bulletsInClip;
                        bulletsInClip += bulletsDelta;
                        bulletsSpare -= bulletsDelta;

                        soundReload.play();
                    }
                    else if (bulletsSpare <= clipSize) {
                        // can't reload to max clip size; reload only to spare bullets
                        bulletsInClip = bulletsSpare;
                        bulletsSpare = 0;

                        soundReload.play();
                    }
                    else {
                        // can't reload at all
                        soundReloadFailed.play();
                    }
                }

                // handle gun firing
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if  (gameTimeTotal.asMilliseconds() - lastShot.asMilliseconds() >
                        1000 / fireRate && bulletsInClip > 0)
                        {
                        // spawn a bullet with a tragectory from player centre to crosshair pos
                        bullets[currentBullet].shoot(player.getCenter(), mouseWorldPosition);
                        currentBullet++;
                        // loop back
                        if (currentBullet >= MAX_BULLETS - 1) {
                            currentBullet = 0;
                        }
                        lastShot = gameTimeTotal;
                        bulletsInClip--;

                        soundShoot.play();
                    } // handle gun firing
                }
            } 
        
            // Handle State::LEVEL_UP
            if (state == State::LEVEL_UP) {
                // upgrades
                if (event.key.code == Keyboard::Num1) {
                    fireRate++;
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num2) {
                    clipSize += clipSize;
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num3) {
                    player.upgradeHealth();
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num4) {
                    player.upgradeSpeed();
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num5) {
                    healthPickup.upgrade();
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num6) {
                    ammoPickup.upgrade();
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num0) {
                    // skip upgrade lmao
                    state = State::IN_GAME;
                }

                if (state == State::IN_GAME) {
                    // increment wave
                    wave++;

                    // Prepare level
                    arena.width = 500 * wave;
                    arena.height = 500 * wave;
                    arena.left = 0;
                    arena.top = 0;

                    // Pass vertexarray by reference to createBackground function
                    int tileSize = createBackground(background, arena);

                    player.spawn(arena, resolution, tileSize);

                    // configure pickups
                    healthPickup.setArena(arena);
                    ammoPickup.setArena(arena);

                    // set horde size
                    numZombies = 5 * wave;
                    // delete allocated memory in free store from CreateHorde function
                    delete[] zombies;
                    zombies = createHorde(numZombies, arena);
                    numZombiesAlive = numZombies;
                    
                    // play levelup sound
                    soundLevelUp.play();

                    // prevent frame jumps
                    clock.restart();
                }
            } // end handle State::LEVEL_UP
            
        // UPDATE FRAME
            if (state == State::IN_GAME) {
                // get dt
                Time dt = clock.restart();
                // update total game time
                gameTimeTotal += dt;
                // store dt second in a var
                const float dtAsSeconds = dt.asSeconds();

                // get mouse coords
                mouseScreenPosition = Mouse::getPosition();
                // convert mouse coords to world coords
                mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
                // move crosshair to invisible mouse
                spriteCrosshair.setPosition(mouseWorldPosition);

                // update player
                player.update(dtAsSeconds, mouseScreenPosition);
                // get new player position
                Vector2f playerPosition(player.getCenter());

                mainView.setCenter(playerPosition);

                // update every zombie by looping
                for (int i = 0; i < numZombies; i++) {
                    if (zombies[i].isAlive()) {
                        zombies[i].update(dtAsSeconds, playerPosition);
                    }
                }

                // update every bullets
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (bullets[i].isInFlight()) {
                        bullets[i].update(dtAsSeconds);
                    }
                }

                // detect collisions
                // if zombies being shot
                for (int i = 0; i < 100; i++) {
                    for (int j = 0; j < numZombies; j++) {
                        if (bullets[i].isInFlight() && zombies[j].isAlive()) {
                            if (bullets[i].getPosition().intersects(zombies[j].getPosition())) {
                                // stop bullet
                                bullets[i].stop();
                                // register hit and check if killed
                                if (zombies[j].hit()) {
                                    // is a kill
                                    score += scorePerZombieKilled;
                                    // check if highscore
                                    if (score >= hiScore) {
                                        hiScore = score;
                                    }
                                    numZombiesAlive--;

                                    // when all zombies died
                                    if (numZombiesAlive == 0) {
                                        state = State::LEVEL_UP;
                                    }
                                }
                                soundSplat.play();
                            }
                        }
                    }
                } // end zombies being shot 

                // if zombie hit player
                for (int i = 0; i < numZombies; i++) {
                    if (player.getPosition().intersects(zombies[i].getPosition())
                        && zombies[i].isAlive()) {
                        if (player.hit(gameTimeTotal)) {
                            soundHit.play();
                        }
                        if (player.getHealth() <= 0) {
                            state = State::GAME_OVER;
                            
                            // record scores
                            ofstream outputFile("gamedata/scores.txt");
                            outputFile << hiScore;
                            outputFile.close();
                        }
                    }
                } // end zombie hitting player

                // if player touched pickups
                if (player.getPosition().intersects(healthPickup.getPosition())
                    && healthPickup.isSpawned()) {
                        player.increaseHealthLevel(healthPickup.pickUp());
                        soundPickup.play();
                    }
                if (player.getPosition().intersects(ammoPickup.getPosition())
                    && ammoPickup.isSpawned()) {
                        bulletsSpare += ammoPickup.pickUp();
                        soundPickup.play();
                    } // end player touched pickups

                // update pickups
                healthPickup.update(dtAsSeconds);
                ammoPickup.update(dtAsSeconds);


                // update HUD elements
                // increment frames since last update
                framesSinceLastHudUpdate++;
                // resize health bar every frame
                healthBar.setSize(Vector2f(player.getHealth() * 3, 50));
                // recalculate everything else too if time passed the threshold
                if (framesSinceLastHudUpdate > HUD_UPDATE_INTERVAL) {
                    // update hud texts
                    stringstream ssAmmo;
                    stringstream ssScore;
                    stringstream ssHiScore;
                    stringstream ssWave;
                    stringstream ssZombiesAlive;

                    ssAmmo << bulletsInClip << "/" << bulletsSpare;
                    ammoText.setString(ssAmmo.str());

                    ssScore << "Score : " << score;
                    scoreText.setString(ssScore.str());

                    ssHiScore << "Hi Score : " << hiScore;
                    scoreText.setString(ssHiScore.str());

                    ssWave << "Wave : " << wave;
                    waveNumberText.setString(ssWave.str());

                    ssZombiesAlive << "Zombies : " << numZombiesAlive;
                    zombiesRemainingText.setString(ssZombiesAlive.str());

                    framesSinceLastHudUpdate = 0;
                }
            } //End updating frame

        // DRAW SCENE
            if (state == State::IN_GAME) {
                window.clear();
                // set mainView to be displayed then draw everying related
                window.setView(mainView);
                    window.draw(background, &textureBackground);
                    
                    // draw zombies
                    for (int i = 0; i < numZombies; i++) {
                        window.draw(zombies[i].getSprite());
                    }

                    window.draw(player.getSprite());

                    // draw pickups if it supposed to be spawned
                    if (ammoPickup.isSpawned())     window.draw(ammoPickup.getSprite());
                    if (healthPickup.isSpawned())   window.draw(healthPickup.getSprite());
                    
                    // draw bullets
                    for (int i = 0; i < MAX_BULLETS; i++) {
                        if (bullets[i].isInFlight()) {
                            window.draw(bullets[i].getShape());
                        }
                    }

                    window.draw(spriteCrosshair);
                
                // Switch to hudView
                window.setView(hudView);
                    window.draw(spriteAmmoIcon);
                    window.draw(ammoText);
                    window.draw(scoreText);
                    window.draw(hiScoreText);
                    window.draw(healthBar);
                    window.draw(waveNumberText);
                    window.draw(zombiesRemainingText);
            }
            else if (state == State::LEVEL_UP) {
                window.draw(spriteGameOver);
                window.draw(levelUpText);
            }
            else if (state == State::PAUSED) {
                window.draw(pausedText);
                
            }
            else if (state == State::GAME_OVER) {
                window.draw(spriteGameOver);
                window.draw(gameOverText);
                window.draw(scoreText);
                window.draw(hiScoreText);
            }

            window.display();
    } // End game loop

    return 0;
}