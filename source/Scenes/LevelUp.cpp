#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "Game.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.cpp"
#include "../Tools/SetOriginCenter.cpp"
#include "../Tools/SetRectangleShapeOnMouseHover.cpp"

class LevelUp : public Scenes {
public:
    virtual SceneChange run(RenderWindow &window);
};

void setRectangleShapeColorWhenMouseHover(sf::RectangleShape &rectangleShape, sf::Vector2f &mousePos);

SceneChange LevelUp::run(RenderWindow &window) {
    const int TEXT_BOX_PADDING = 50;
    const int BUTTON_PADDING = 30;

    Texture textureScreenshot;
    textureScreenshot.loadFromImage(getScreenShot());
    Sprite screenshot(textureScreenshot);
    spriteSetOriginCenter(screenshot);
    screenshot.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    screenshot.setScale(Vector2f(0.8, 0.8));

    RectangleShape darkOverlay(Vector2f(window.getSize()));
    darkOverlay.setFillColor(Color(0, 0, 0, 128));

    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    Text textLevelUp("Level Up!", fontBebas, 80);
    textSetOriginCenter(textLevelUp);
    textLevelUp.setOrigin(Vector2f(0, textLevelUp.getOrigin().y));
    textLevelUp.setPosition(Vector2f(200, 100));

    RectangleShape boxLevelUp(Vector2f(textLevelUp.getLocalBounds().width + TEXT_BOX_PADDING,
                                       textLevelUp.getLocalBounds().height + TEXT_BOX_PADDING));
    shapeSetOriginCenter(boxLevelUp);
    boxLevelUp.setOrigin(Vector2f(0, boxLevelUp.getOrigin().y));
    boxLevelUp.setFillColor(Color::Black);
    boxLevelUp.setPosition(textLevelUp.getPosition() + Vector2f(-TEXT_BOX_PADDING / 2, TEXT_BOX_PADDING / 2));

    Text nextLevelText("Next Level!", fontBebas);
    nextLevelText.setFillColor(Color::Black);
    nextLevelText.setCharacterSize(48);
    RectangleShape nextLevelButton(Vector2f(nextLevelText.getLocalBounds().width + BUTTON_PADDING,
                                            nextLevelText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(nextLevelText);
    shapeSetOriginCenter(nextLevelButton);
    nextLevelText.setOrigin(Vector2f(0, nextLevelText.getOrigin().y));
    nextLevelButton.setOrigin(Vector2f(0, nextLevelButton.getOrigin().y));
    nextLevelText.setPosition(Vector2f(200, window.getSize().y * 0.7));
    nextLevelButton.setPosition(nextLevelText.getPosition() + Vector2f(-BUTTON_PADDING / 2, BUTTON_PADDING / 2));

    Text exitText("Exit and save", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(48);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + BUTTON_PADDING,
                                       exitText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setOrigin(Vector2f(0, exitText.getOrigin().y));
    exitButton.setOrigin(Vector2f(0, exitButton.getOrigin().y));
    exitText.setPosition(nextLevelText.getPosition() + Vector2f(0, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(-BUTTON_PADDING / 2, BUTTON_PADDING / 2));

    // Make buttons for selecting upgrades from this list
    const int UPGRADE_BUTTON_FONT_SIZE = 36;
    const int NUM_UPGRADES = 6;
    const std::string UPGRADE_TEXT[NUM_UPGRADES] = {
            "Increased rate of fire",
            "Increased clip size (next reload)",
            "Increased max health",
            "Increased run speed",
            "More and better health pickups",
            "More and better ammo pickups"
    };
    int upgradeIndex = -1;

    Text upgradeText[NUM_UPGRADES];
    RectangleShape upgradeButton[NUM_UPGRADES];

    for (int i = 0; i < NUM_UPGRADES; i++) {
        upgradeText[i] = Text(UPGRADE_TEXT[i], fontBebas, UPGRADE_BUTTON_FONT_SIZE);
        upgradeText[i].setFillColor(Color::Black);
        upgradeText[i].setOrigin(
                Vector2f(upgradeText[i].getLocalBounds().width, upgradeText[i].getLocalBounds().height / 2));
        upgradeText[i].setPosition(
                Vector2f(screenshot.getGlobalBounds().getPosition().x + screenshot.getGlobalBounds().getSize().x,
                         300 + i * 100));
        upgradeButton[i] = RectangleShape(Vector2f(upgradeText[i].getLocalBounds().width + BUTTON_PADDING,
                                                   upgradeText[i].getLocalBounds().height + BUTTON_PADDING));
        upgradeButton[i].setOrigin(
                Vector2f(upgradeButton[i].getLocalBounds().width, upgradeButton[i].getLocalBounds().height / 2));
        upgradeButton[i].setPosition(upgradeText[i].getPosition() + Vector2f(BUTTON_PADDING / 2, BUTTON_PADDING / 2));
    }


    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(nextLevelButton, mouseScreenPosition, Color(189, 189, 189),
                                                   Color::White);
                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(189, 189, 189), Color::White);

                for (int i = 0; i < NUM_UPGRADES; i++) {
                    Color hoverColor = Color(189, 189, 189);
                    Color baseColor = Color::White;
                    if (upgradeIndex == i) {
                        hoverColor = Color(0x26A69AFF);
                        baseColor = Color(0x4DB6ACFF);
                    }

                    setRectangleShapeColorOnMouseHover(upgradeButton[i], mouseScreenPosition, hoverColor, baseColor);
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                if (nextLevelButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    currentLevel++;
                    dynamic_cast<Game *>(getGamePtr())->regenerate();
                    return {ScenesList::SCENE_GAME};
                } else if (exitButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return {ScenesList::SCENE_GAMEOVER};
                }

                for (int i = 0; i < NUM_UPGRADES; i++) {
                    if (upgradeButton[i].getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                        upgradeIndex = i;

                        for (auto & j : upgradeButton) {
                            j.setFillColor(Color::White);
                        }
                        upgradeButton[upgradeIndex].setFillColor(Color(0x4DB6ACFF));
                    }
                }
            }
        }
        // Draw frame
        window.clear(COLOR_BACKGROUND);

        window.draw(screenshot);
        window.draw(darkOverlay);
        window.draw(boxLevelUp);
        window.draw(textLevelUp);
        window.draw(nextLevelButton);
        window.draw(nextLevelText);
        window.draw(exitButton);
        window.draw(exitText);

        for (int i = 0; i < NUM_UPGRADES; i++) {
            window.draw(upgradeButton[i]);
            window.draw(upgradeText[i]);
        }

        window.display();
    }


    return SceneChange(ScenesList::EXIT);
}
