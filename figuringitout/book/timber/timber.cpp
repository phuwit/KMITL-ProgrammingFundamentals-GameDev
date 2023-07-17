#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main () {
    // Create a videomode object
    VideoMode vm(1920, 1080);
    // Create and open window for the game
    RenderWindow window(vm, "Timber!!!");

    // Create a texture to hold a graphic on GPU memory
    Texture textureBackground;
    // Load a png into textureBackground
    textureBackground.loadFromFile("graphics/background.png");
    // Create a sprite
    Sprite spriteBackground;
    // Make spriteBackground have the texture from textureBackground
    spriteBackground.setTexture(textureBackground);
    // Move sprite to 0,0
    spriteBackground.setPosition(0, 0);

    // Making a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Prepare a bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    // Make be not moving
    bool beeActive = false;
    // Set bee speed
    float beeSpeed = 0.0f;

    // Load up cloud texture
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    // Make 3 cloud sprites from the same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    // Set cloud position to be different heights
    spriteCloud1.setPosition(0,0);
    spriteCloud2.setPosition(0,250);
    spriteCloud3.setPosition(0,500);
    // Make cloud inactive
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    // Set cloud speed
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    // Controling time itself
    Clock clock;

    // TIme bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarStartHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarStartHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2,
                        980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track if the game is paused
    bool paused = true;

    // Draw some text
    int score = 0;
    Text messageText;
    Text scoreText;
    // Load a font
    Font font;
    font.loadFromFile("fonts/FiraCodeNerdFont-Retina.ttf");
    // Make message use the font
    messageText.setFont(font);
    scoreText.setFont(font);
    // Assign message to object
    messageText.setString("Press enter to start!");
    scoreText.setString("Score = 0");
    // Set text size
    messageText.setCharacterSize(60);
    scoreText.setCharacterSize(80);
    // Set fill color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    // Position texts
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(40, 30);

    Text fpsCounter;
    fpsCounter.setFont(font);
    fpsCounter.setCharacterSize(40);
    fpsCounter.setOutlineThickness(5);
    fpsCounter.setFillColor(Color::White);
    fpsCounter.setOutlineColor(Color::Black);
    fpsCounter.setPosition(0, 10);
    RectangleShape fpsCounterBackground;
    fpsCounterBackground.setPosition(0, 20);

    // Main game loop
    while (window.isOpen()) {
        // Handle input
            Event event;
            while (window.pollEvent(event)) {
                if (Keyboard::isKeyPressed(Keyboard::Escape) ||
                (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C)) ||
                event.type == Event::Closed) {
                    window.close();
                }
            }
            
            // Start game
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                paused = !paused;
                // Reset time and score
                score = 0;
                timeRemaining = 6;
            }

        // Update scene
            if (!paused) {
                // Measure time between frame
                Time dt = clock.restart();
                float fps = 1.f / dt.asSeconds();

                // Showing fps on screen
                std::stringstream ssfps;
                ssfps << "FPS: " << fps;
                fpsCounter.setString(ssfps.str());
                // FloatRect fpsCounterRect = fpsCounter.getLocalBounds();
                // fpsCounterBackground.setSize(Vector2f(fpsCounterRect.width + 5, fpsCounterRect.height + 5));
                // fpsCounterBackground.setFillColor(Color::Black);

                // Subtract delta time from time remaining
                timeRemaining -= dt.asSeconds();
                // Update time bar size
                timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining,
                                         timeBarStartHeight));
                if (timeRemaining <= 0.0f) {
                    paused = !paused;
                    // Change pause text
                    messageText.setString("You ran out of time!");
                    // Recalculate positioning
                    FloatRect textRect = messageText.getLocalBounds();
                    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                          textRect.top + textRect.height / 2.0f);
                    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                }
                
                // Setup bee
                if (!beeActive) {
                    // How fast is the bee
                    srand((int)time(0));
                    beeSpeed  = (rand() % 200) + 200;
                    // How high is the bee
                    srand((int)time(0) * 10);
                    float height = (rand() % 500) + 500;
                    spriteBee.setPosition(2000, height);
                    beeActive = true;
                }
                else {
                    // Move the bee
                    spriteBee.setPosition(
                        spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                        spriteBee.getPosition().y
                    );
                    // Check if bee exit the screen
                    if (spriteBee.getPosition().x < -100) {
                        // Deactivate the bee and set up new bee next frame
                        beeActive = false;
                    }
                }

                // Setup clouds
                    // Cloud 1
                    if (!cloud1Active) {
                        // How fast is the cloud
                        srand((int)time(0) * 10);
                        cloud1Speed = (rand() % 200);
                        // How high is the cloud
                        srand((int)time(0) * 10);
                        float(height) = (rand() % 150);
                        spriteCloud1.setPosition(-300, height);
                        cloud1Active = true;
                    }
                    else {
                        spriteCloud1.setPosition(
                            spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                            spriteCloud1.getPosition().y
                        );
                        // Is cloud exited screen
                        if (spriteCloud1.getPosition().x > 2220) {
                            cloud1Active = false;
                        }
                    }
                    // Cloud 2
                    if (!cloud2Active) {
                        // How fast is the cloud
                        srand((int)time(0) * 20);
                        cloud2Speed = (rand() % 200);
                        // How high is the cloud
                        srand((int)time(0) * 20);
                        float(height) = (rand() % 300) - 150;
                        spriteCloud2.setPosition(-300, height);
                        cloud2Active = true;
                    }
                    else {
                        spriteCloud2.setPosition(
                            spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                            spriteCloud2.getPosition().y
                        );
                        // Is cloud exited screen
                        if (spriteCloud2.getPosition().x > 2220) {
                            cloud2Active = false;
                        }
                    }
                    // Cloud 3
                    if (!cloud3Active) {
                        // How fast is the cloud
                        srand((int)time(0) * 30);
                        cloud3Speed = (rand() % 200);
                        // How high is the cloud
                        srand((int)time(0) * 30);
                        float(height) = (rand() % 450) - 150;
                        spriteCloud3.setPosition(-300, height);
                        cloud3Active = true;
                    }
                    else {
                        spriteCloud3.setPosition(
                            spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                            spriteCloud3.getPosition().y
                        );
                        // Is cloud exited screen
                        if (spriteCloud3.getPosition().x > 2220) {
                            cloud3Active = false;
                        }
                    }

                // Update score text
                score++;
                std::stringstream ss;
                ss << "Score = " << score;
                scoreText.setString(ss.str());
            } // End if not paused

        // Draw scene

        // Clear everything from last frame
            window.clear();

        // Draw new scene
            // Game Elements
            window.draw(spriteBackground);
            window.draw(spriteCloud1);
            window.draw(spriteCloud2);
            window.draw(spriteCloud3);
            window.draw(spriteTree);
            window.draw(spriteBee);

            // HUD

            window.draw(scoreText);
            window.draw(timeBar);
            window.draw(fpsCounterBackground);
            window.draw(fpsCounter);
            if (paused) {
                window.draw(messageText);
            }

        // Show what we just drew
            window.display();
    }
    

    return 0;
}