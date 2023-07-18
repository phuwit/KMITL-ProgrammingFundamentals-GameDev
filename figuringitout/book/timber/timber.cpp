#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

// Function prototype
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// Where is the player/branch
enum class side {NONE, LEFT, RIGHT};
side branchPositions[NUM_BRANCHES];

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
    spriteBee.setPosition(-200, 800);
    // Make be not moving
    bool beeActive = false;
    // Set bee speed
    float beeSpeed = 0.0f;

    // Load up cloud texture
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    int cloudCount = 3;
    Sprite spriteCloud[cloudCount];
    bool cloudActive[cloudCount];
    float cloudSpeed[cloudCount];
    for (int i = 0; i < cloudCount; i++) {
        // Make 3 cloud sprites from the same texture
        // Sprite spriteCloud[i];
        spriteCloud[i].setTexture(textureCloud);
        // Set cloud position to be different heights
        spriteCloud[i].setPosition(0, 250 * i);
        // Make cloud inactive
        cloudActive[i] = false;
        // Set cloud speed    
        cloudSpeed[i] = 0.0f;
    }

    // Prepare branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set origin to center, so we can rotate without changing position
        branches[i].setOrigin(220, 20);
    }

    // Prepare player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    // Make player starts from the left
    side playerSide = side::LEFT;
    // Prepare gravestone 
    Texture textureGrave;
    textureGrave.loadFromFile("graphics/rip.png");
    Sprite spriteGrave;
    spriteGrave.setTexture(textureGrave);
    spriteGrave.setPosition(600, 860);
    // Prepare axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
    // Set axe pos to use later
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    // Prepare Flying logs
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

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

    // turn on and off player input to prevent repeated actions
    bool acceptInput = false;

    // Prepare sounds
    // Wood chopping sound
    // SoundBuffer chopBuffer;
    // chopBuffer.loadFromFile("sound/minecraft_wood_dig.ogg");
    // Sound chop;
    // chop.setBuffer(chopBuffer);
    const int CHOP_SOUND_NUM = 4;
    SoundBuffer chopBuffer[CHOP_SOUND_NUM];
    Sound chop[CHOP_SOUND_NUM];
    for (int i = 0; i < CHOP_SOUND_NUM; i++) {
        std::stringstream chopSoundFileName;
        chopSoundFileName << "sound/minecraft_wood_dig" << (i + 1) << ".ogg";
        chopBuffer[i].loadFromFile(chopSoundFileName.str());
        chop[i].setBuffer(chopBuffer[i]);
    }
    // player suqished
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/minecraft_villager_death.ogg");
    Sound death;
    death.setBuffer(deathBuffer);
    // out of time
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

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

                if (event.type == Event::KeyReleased && !paused) {
                    // listen to inputs again
                    acceptInput = true;
                    // hide axe
                    spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
                }
            }
            
            // Start game
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                paused = false;
                // Reset time and score
                score = 0;
                timeRemaining = 6;
                // make branch 2 and over disappear
                for (int i = 1; i < NUM_BRANCHES; i++) {
                    branchPositions[i] = side::NONE;
                }
                // Hide gravestone
                spriteGrave.setPosition(675, 2000);
                // Move player into position
                spritePlayer.setPosition(580, 720);
                acceptInput = false;
            }

            if (acceptInput) {
                // Handle right cursor pressed
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    // make sure that player will be on the right
                    playerSide = side::RIGHT;
                    
                    score++;

                    // Add time to time remaining
                    // more score = less time added
                    timeRemaining += (2 / score) + .15;
                    spriteAxe.setPosition(AXE_POSITION_RIGHT,
                                          spriteAxe.getPosition().y);
                    spritePlayer.setPosition(1200, 720);
                    
                    updateBranches(score);
                    
                    // Make log fly left
                    spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;
                    acceptInput = false;

                    // play chop sound
                    srand(score);
                    chop[rand() % 3].play();
                }
                // Handle left cursor pressed
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    // make sure that player will be on the right
                    playerSide = side::LEFT;
                    
                    score++;

                    // Add time to time remaining
                    // more score = less time added
                    timeRemaining += (2 / score) + .15;
                    spriteAxe.setPosition(AXE_POSITION_LEFT,
                                          spriteAxe.getPosition().y);
                    spritePlayer.setPosition(580, 720);
                    
                    updateBranches(score);

                    // Make log fly left
                    spriteLog.setPosition(810, 720);
                    logSpeedX = 5000;
                    logActive = true;
                    acceptInput = false;

                    // play chop sound
                    srand(score);
                    chop[rand() % 3].play();
                }
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
                    // play out of time sound
                    outOfTime.play();
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
                for (int i = 0; i < cloudCount; i++) {
                    if (!cloudActive[i]) {
                        // How fast is the cloud
                        srand((int)time(0) * (10 * (i + 1)));
                        cloudSpeed[i] = (rand() % 200);
                        // How high is the cloud
                        srand((int)time(0) * (10 * (i + 1)));
                        float(height) = (rand() % (150 * (i + 1))) - (150 * i);
                        spriteCloud[i].setPosition(-300, height);
                        cloudActive[i] = true;
                    }
                    else {
                        spriteCloud[i].setPosition(
                            spriteCloud[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()),
                            spriteCloud[i].getPosition().y
                        );
                        // Is cloud exited screen
                        if (spriteCloud[i].getPosition().x > 2220) {
                            cloudActive[i] = false;
                        }
                    }
                }

                // Update branches
                for (int i = 0; i < NUM_BRANCHES; i++) {
                    float height = i * 150;
                    if (branchPositions[i] == side::LEFT) {
                        // Position branch on the left
                        branches[i].setPosition(610, height);
                        branches[i].setRotation(180);
                        }
                    else if (branchPositions[i] == side::RIGHT) {
                        // Position branch on the right
                        branches[i].setPosition(1330, height);
                        branches[i].setRotation(0);
                    }
                    else {
                        // Hide branch
                        branches[i].setPosition(3000, height);
                    }
                }

                // Handle flying logs
                if (logActive) {
                    spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                                          spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()) );
                    // reset log if it exited screen
                    if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000 ) {
                        logActive = false;
                        spriteLog.setPosition(810, 720);
                    }

                    // check if player been squished by a branch
                    if (branchPositions[5] == playerSide) {
                        // death
                        paused = true;
                        acceptInput = false;
                        // draw grave
                        spriteGrave.setPosition(525, 760);
                        // hide player
                        spritePlayer.setPosition(2000, 660);
                        // change message text
                        messageText.setString("Squished!");
                        // Recalculate positioning
                        FloatRect textRect = messageText.getLocalBounds();
                        messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                            textRect.top + textRect.height / 2.0f);
                        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                        // play death sound
                        death.play();
                    }
                    else {
                        // remove last branch because confusing
                        branchPositions[5] = side::NONE;
                    }
                }

                // Update score text
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
            for (int i = 0; i < cloudCount; i++) {
                window.draw(spriteCloud[i]);
            }
            for (int i = 0; i < NUM_BRANCHES; i++) {
                window.draw(branches[i]);
            }
            window.draw(spriteLog);
            window.draw(spriteTree);
            window.draw(spritePlayer);
            window.draw(spriteAxe);
            window.draw(spriteGrave);
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

void updateBranches (int seed) {
    // Move all branches down one
    for (int i = NUM_BRANCHES - 1; i > 0; i--) {
        branchPositions[i] = branchPositions[i - 1];
    }

    // Spawn new branch 0
    // None, Left, or Right (None has more weight)
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}