#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scenes.hpp"
#include "Game.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.hpp"
#include "../Holders/FontHolder.hpp"
#include "../Holders/SoundHolder.hpp"
#include "../Holders/MusicHolder.cpp"
#include "../Tools/SetOriginCenter.cpp"
#include "../Tools/SetRectangleShapeOnMouseHover.cpp"

class Menu : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange Menu::run(RenderWindow &window) {
    Sprite logo(TextureHolder::GetTexture("assets/sprites/brand/logo.png"));
    spriteSetOriginCenter(logo);
    logo.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y * 0.25));

    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    int BUTTON_PADDING = 30;

    Text playText("Play!", fontBebas);
    playText.setFillColor(Color::Black);
    playText.setCharacterSize(60);
    RectangleShape playButton(Vector2f(playText.getLocalBounds().width + BUTTON_PADDING, playText.getLocalBounds().height + BUTTON_PADDING));
    playButton.setFillColor(Color(0x4DB6ACFF));
    textSetOriginCenter(playText);
    shapeSetOriginCenter(playButton);
    playText.setPosition(logo.getPosition() + Vector2f(0, 400));
    playButton.setPosition(playText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

    Text leaderboardText("Leaderboard", fontBebas);
    leaderboardText.setFillColor(Color::Black);
    leaderboardText.setCharacterSize(60);
    RectangleShape leaderboardButton(Vector2f(leaderboardText.getLocalBounds().width + BUTTON_PADDING, leaderboardText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(leaderboardText);
    shapeSetOriginCenter(leaderboardButton);
    leaderboardText.setPosition(playText.getPosition() + Vector2f(0, 100));
    leaderboardButton.setPosition(leaderboardText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

    Text infoText("Info", fontBebas);
    infoText.setFillColor(Color::Black);
    infoText.setCharacterSize(60);
    RectangleShape infoButton(Vector2f(infoText.getLocalBounds().width + BUTTON_PADDING, infoText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(infoText);
    shapeSetOriginCenter(infoButton);
    infoText.setPosition(leaderboardText.getPosition() + Vector2f(0, 100));
    infoButton.setPosition(infoText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

    Text exitText("Exit", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(60);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + BUTTON_PADDING, exitText.getLocalBounds().height + BUTTON_PADDING));
    exitButton.setFillColor(Color(0xE57373FF));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setPosition(infoText.getPosition() + Vector2f(0, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

//    Sound soundClick(SoundHolder::GetSound("assets/sfx/click.ogg"));
//    Sound soundHover(SoundHolder::GetSound("assets/sfx/hover.ogg"));

    Music* musicPtr = &MusicHolder::GetMusic("assets/music/Spow.ogg");
    musicPtr->setLoop(true);
    musicPtr->setVolume(10);
    musicPtr->play();

    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(playButton, mouseScreenPosition, Color(0x26A69AFF), Color(0x4DB6ACFF));
                setRectangleShapeColorOnMouseHover(infoButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
                setRectangleShapeColorOnMouseHover(leaderboardButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(0xEF5350FF), Color(0xE57373FF));
            }

            if (event.type == Event::MouseButtonPressed) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                if (playButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    dynamic_cast<Game *>(getGamePtr())->newGame();
                    return {ScenesList::SCENE_GAME};
                } else if (infoButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return {ScenesList::SCENE_INFO};
                } else if (leaderboardButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return {ScenesList::SCENE_LEADERBOARD};
                } else if (exitButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return {ScenesList::EXIT};
                }
            }

            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                return {ScenesList::EXIT};
            }
        }

        // Draw frame

        window.clear(COLOR_BACKGROUND);
            window.draw(logo);

            window.draw(playButton);
            window.draw(playText);
            window.draw(infoButton);
            window.draw(infoText);
            window.draw(leaderboardButton);
            window.draw(leaderboardText);
            window.draw(exitButton);
            window.draw(exitText);

        window.display();
    }

    return SceneChange(EXIT);
}
