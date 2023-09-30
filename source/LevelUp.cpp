#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"
#include "Tools/SetOriginCenter.cpp"
#include "Tools/SetRectangleShapeOnMouseHover.cpp"

class LevelUp : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

void setRectangleShapeColorWhenMouseHover (sf::RectangleShape &rectangleShape, sf::Vector2f &mousePos);

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

    Font fontBebas;
    fontBebas.loadFromFile("assets/fonts/BebasNeue-Regular.otf");
    Text textLevelUp("Level Up!", fontBebas, 80);
    textSetOriginCenter(textLevelUp);
    textLevelUp.setOrigin(Vector2f(0, textLevelUp.getOrigin().y));
    textLevelUp.setPosition(Vector2f(200, 100));

    RectangleShape boxLevelUp(Vector2f(textLevelUp.getLocalBounds().width + TEXT_BOX_PADDING, textLevelUp.getLocalBounds().height + TEXT_BOX_PADDING));
    shapeSetOriginCenter(boxLevelUp);
    boxLevelUp.setOrigin(Vector2f(0, boxLevelUp.getOrigin().y));
    boxLevelUp.setFillColor(Color::Black);
    boxLevelUp.setPosition(textLevelUp.getPosition() + Vector2f(-TEXT_BOX_PADDING / 2, TEXT_BOX_PADDING / 2));
    
    Text nextLevelText("Next Level!", fontBebas);
    nextLevelText.setFillColor(Color::Black);
    nextLevelText.setCharacterSize(48);
    RectangleShape nextLevelButton(Vector2f(nextLevelText.getLocalBounds().width + BUTTON_PADDING, nextLevelText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(nextLevelText);
    shapeSetOriginCenter(nextLevelButton);
    nextLevelText.setOrigin(Vector2f(0, nextLevelText.getOrigin().y));
    nextLevelButton.setOrigin(Vector2f(0, nextLevelButton.getOrigin().y));
    nextLevelText.setPosition(Vector2f(200, window.getSize().y * 0.7));
    nextLevelButton.setPosition(nextLevelText.getPosition() + Vector2f(-BUTTON_PADDING / 2, BUTTON_PADDING / 2));

    Text exitText("Exit and save", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(48);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + BUTTON_PADDING, exitText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setOrigin(Vector2f(0, exitText.getOrigin().y));
    exitButton.setOrigin(Vector2f(0, exitButton.getOrigin().y));
    exitText.setPosition(nextLevelText.getPosition() + Vector2f(0, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(-BUTTON_PADDING / 2, BUTTON_PADDING / 2));

    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(nextLevelButton, mouseScreenPosition, Color(176, 190, 197), Color::White);
                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(176, 190, 197), Color::White);
            }
            if (event.type == Event::MouseButtonPressed) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                if (nextLevelButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    currentLevel++;
                    return SceneChange(ScenesList::SCENE_GAME);
                } else if (exitButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return SceneChange(ScenesList::EXIT);
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
        window.display();
    }
    

    return SceneChange(ScenesList::EXIT);
}
