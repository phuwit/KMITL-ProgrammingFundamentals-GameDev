#include <SFML/Graphics.hpp>

#include "Player.cpp"
#include "CreateBackground.cpp"

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
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Arena", Style::Fullscreen);

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

    // Create an instance of Player
    Player player;

    // arena boundaries
    IntRect arena;

    // Create the background
    VertexArray background;
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background_sheet.png");

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
            } // End handle movement keys
        
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
                float dtAsSeconds = dt.asSeconds();

                // get mouse coords
                mouseScreenPosition = Mouse::getPosition();
                // convert mouse coords to world coords
                mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);

                // update player
                player.update(dtAsSeconds, mouseScreenPosition);
                // get new player position
                Vector2f playerPosition(player.getCenter());

                mainView.setCenter(playerPosition);
            } //End updating frame

        // DRAW SCENE
            if (state == State::IN_GAME) {
                window.clear();
                // set mainView to be displayed then draw everying related
                window.setView(mainView);
                window.draw(background, &textureBackground);
                window.draw(player.getSprite());
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