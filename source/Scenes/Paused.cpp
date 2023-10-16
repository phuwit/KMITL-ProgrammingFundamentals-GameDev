#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/TextureHolder.hpp"
#include "../Tools/SetOriginCenter.cpp"
#include "../Tools/SetRectangleShapeOnMouseHover.cpp"

class Paused : public Scenes {
    public:
        SceneChange run(RenderWindow &window) override;
};

SceneChange Paused::run(RenderWindow &window) {
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

    Text textPaused("Paused", fontBebas, 80);
    textSetOriginCenter(textPaused);
    textPaused.setOrigin(Vector2f(0, textPaused.getOrigin().y));
    textPaused.setPosition(Vector2f(200, 100));

    RectangleShape boxLevelUp(Vector2f(textPaused.getLocalBounds().width + TEXT_BOX_PADDING,
                                       textPaused.getLocalBounds().height + TEXT_BOX_PADDING));
    shapeSetOriginCenter(boxLevelUp);
    boxLevelUp.setOrigin(Vector2f(0, boxLevelUp.getOrigin().y));
    boxLevelUp.setFillColor(Color::Black);
    boxLevelUp.setPosition(textPaused.getPosition() + Vector2f(-TEXT_BOX_PADDING / 2, TEXT_BOX_PADDING / 2));

    Text continueText("Continue", fontBebas);
    continueText.setFillColor(Color::Black);
    continueText.setCharacterSize(48);
    RectangleShape continueButton(Vector2f(continueText.getLocalBounds().width + BUTTON_PADDING,
                                            continueText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(continueText);
    shapeSetOriginCenter(continueButton);
    continueText.setOrigin(Vector2f(0, continueText.getOrigin().y));
    continueButton.setOrigin(Vector2f(0, continueButton.getOrigin().y));
    continueText.setPosition(Vector2f(200, window.getSize().y * 0.7));
    continueButton.setPosition(continueText.getPosition() + Vector2f(-BUTTON_PADDING / 2, BUTTON_PADDING / 2));

    Text exitText("Exit and save", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(48);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + BUTTON_PADDING,
                                       exitText.getLocalBounds().height + BUTTON_PADDING));
    exitButton.setFillColor(Color(0xE57373FF));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setOrigin(Vector2f(0, exitText.getOrigin().y));
    exitButton.setOrigin(Vector2f(0, exitButton.getOrigin().y));
    exitText.setPosition(continueText.getPosition() + Vector2f(0, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(-BUTTON_PADDING / 2, BUTTON_PADDING / 2));

    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(continueButton, mouseScreenPosition, Color(189, 189, 189),Color::White);
                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(0xEF5350FF), Color(0xE57373FF));
            }
            if (event.type == Event::MouseButtonPressed) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                if (continueButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return {ScenesList::SCENE_GAME};
                } else if (exitButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return {ScenesList::SCENE_GAMEOVER};
                }
            }
        }
        // Draw frame
        window.clear(COLOR_BACKGROUND);

        window.draw(screenshot);
        window.draw(darkOverlay);
        window.draw(boxLevelUp);
        window.draw(textPaused);
        window.draw(continueButton);
        window.draw(continueText);
        window.draw(exitButton);
        window.draw(exitText);

        window.display();
    }


    return SceneChange(ScenesList::EXIT);
}
