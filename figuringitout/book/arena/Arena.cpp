#include <SFML/Graphics.hpp>

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
    // RenderWindow window(VideoMode(resolution.x, resolution.y), "Arena", Style::Fullscreen);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Arena");

    // Create a main view
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));

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
                    }
                    else if (bulletsSpare <= clipSize) {
                        // can't reload to max clip size; reload only to spare bullets
                        bulletsInClip = bulletsSpare;
                        bulletsSpare = 0;
                    }
                    else {
                        // can't reload at all
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
                    } // handle gun firing
                }
            } 
        
            // Handle State::LEVEL_UP
            if (state == State::LEVEL_UP) {
                if (event.key.code == Keyboard::Num1) {
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num2) {
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num3) {
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num4) {
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num5) {
                    state = State::IN_GAME;
                }
                if (event.key.code == Keyboard::Num6) {
                    state = State::IN_GAME;
                }

                if (state == State::IN_GAME) {
                    // Prepare level
                    arena.width = 500;
                    arena.height = 500;
                    arena.left = 0;
                    arena.top = 0;

                    // Pass vertexarray by reference to createBackground function
                    int tileSize = createBackground(background, arena);

                    player.spawn(arena, resolution, tileSize);

                    // configure pickups
                    healthPickup.setArena(arena);
                    ammoPickup.setArena(arena);

                    // set horde size
                    numZombies = 100;
                    // delete allocated memory in free store from CreateHorde function
                    delete[] zombies;
                    zombies = createHorde(numZombies, arena);
                    numZombiesAlive = numZombies;

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
                            }
                        }
                    }
                } // end zombies being shot 

                // if zombie hit player
                for (int i = 0; i < numZombies; i++) {
                    if (player.getPosition().intersects(zombies[i].getPosition())
                        && zombies[i].isAlive()) {
                        if (player.hit(gameTimeTotal)) {

                        }
                        if (player.getHealth() <= 0) {
                            state = State::GAME_OVER;
                        }
                    }
                } // end zombie hitting player

                // if player touched pickups
                if (player.getPosition().intersects(healthPickup.getPosition())
                    && healthPickup.isSpawned()) {
                        player.increaseHealthLevel(healthPickup.pickUp());
                    }
                if (player.getPosition().intersects(ammoPickup.getPosition())
                    && ammoPickup.isSpawned()) {
                        bulletsSpare += ammoPickup.pickUp();
                    } // end player touched pickups

                // update pickups
                healthPickup.update(dtAsSeconds);
                ammoPickup.update(dtAsSeconds);
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

            }
            else if (state == State::LEVEL_UP) {

            }
            else if (state == State::PAUSED) {
                
            }
            else if (state == State::GAME_OVER) {
                
            }

            window.display();
    } // End game loop

    return 0;
}