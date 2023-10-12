#include <fstream>
#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.cpp"
#include "../Tools/SetOriginCenter.cpp"
#include "../Tools/SetRectangleShapeOnMouseHover.cpp"
#include "../Scores/Score.hpp"
#include "../Scores/ReadScores.cpp"
#include "../Scores/SaveScores.cpp"
#include "../Scores/SortScores.cpp"


class Leaderboard : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange Leaderboard::run(RenderWindow &window) {
    const int SCORES_COUNT = 5;
    const int BUTTON_PADDING = 30;

    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    std::vector<Score> scores = readScore();

    Text exitText("<", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(60);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + BUTTON_PADDING, exitText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setPosition(Vector2f(100, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(0, BUTTON_PADDING));

    Text leaderboardHeader("Leaderboard", fontBebas);
    leaderboardHeader.setFillColor(Color::White);
    leaderboardHeader.setCharacterSize(72);
    textSetOriginCenter(leaderboardHeader);
    leaderboardHeader.setPosition(Vector2f(window.getSize().x / 2, 150));

    Text scoresHeader("Score", fontBebas);
    scoresHeader.setFillColor(Color::White);
    scoresHeader.setCharacterSize(48);
    scoresHeader.setPosition(Vector2f(200, 100));

    Text namesHeader("Name", fontBebas);
    scoresHeader.setFillColor(Color::White);
    scoresHeader.setCharacterSize(48);
    scoresHeader.setPosition(Vector2f(400, 100));

    Text scoresText[SCORES_COUNT];
    Text namesText[SCORES_COUNT];

    for (int i = 0; i < SCORES_COUNT; i++) {
        scoresText[i].setString(scores[i].getScore());
        scoresText[i].setFont(fontBebas);
        scoresText[i].setFillColor(Color::White);
        scoresText[i].setCharacterSize(48);
        scoresText[i].setPosition(Vector2f(200, 200 + (i * 100)));

        namesText[i].setString(scores[i].getName());
        namesText[i].setFont(fontBebas);
        namesText[i].setFillColor(Color::White);
        namesText[i].setCharacterSize(48);
        namesText[i].setPosition(Vector2f(400, 200 + (i * 100)));
    }

    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
            } else if (event.type == Event::MouseButtonPressed) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                if (exitButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return SceneChange(ScenesList::SCENE_MENU);
                }
            } else if (event.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    return SceneChange(ScenesList::SCENE_MENU);
                }
            }
        }
        // Draw frame
        window.clear(COLOR_BACKGROUND);
        window.draw(exitButton);
        window.draw(exitText);
        window.draw(leaderboardHeader);
        window.draw(scoresHeader);
        window.draw(namesHeader);
        for (int i = 0; i < SCORES_COUNT; i++) {
            window.draw(scoresText[i]);
            window.draw(namesText[i]);
        }
        window.display();
    }

    return SceneChange(ScenesList::EXIT);
}
