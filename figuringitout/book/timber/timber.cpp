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

    // Variable to control time
    Clock clock;

    // Main game loop
    while (window.isOpen()) {
        // Handle input
            if (Keyboard::isKeyPressed(Keyboard::Escape) || (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C))) {
                window.close();
            }

        // Update scene
            Time dt = clock.restart();
            
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

        // Draw scene

        // Clear everything from last frame
            window.clear();

        // Draw new scene
            window.draw(spriteBackground);

            window.draw(spriteCloud1);
            window.draw(spriteCloud2);
            window.draw(spriteCloud3);

            window.draw(spriteTree);
            
            window.draw(spriteBee);

        // Show what we just drew
            window.display();
    }
    

    return 0;
}