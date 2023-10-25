#include "GameOver.hpp"

SceneChange GameOver::run(RenderWindow &window) {
    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    Text gameOverText("Game Over!", fontBebas);
    gameOverText.setFillColor(Color::White);
    gameOverText.setCharacterSize(80);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setPosition(Vector2f(window.getSize().x / 2, 150));
    textSetOriginCenter(gameOverText);

    Text exitText("<", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(60);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + 30, exitText.getLocalBounds().height + 30));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setPosition(Vector2f(100, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(0, 30));

    Text enterYourNameText("Enter your name:", fontBebas);
    enterYourNameText.setFillColor(Color::White);
    enterYourNameText.setCharacterSize(56);
    enterYourNameText.setStyle(Text::Bold);
    textSetOriginCenter(enterYourNameText);
    enterYourNameText.setPosition(Vector2f(window.getSize().x / 2, 500));

    string nameString = "";

    Text nameText("", fontBebas);
    nameText.setFillColor(Color::White);
    nameText.setCharacterSize(56);
    nameText.setStyle(Text::Bold);
    textSetOriginCenter(nameText);
    nameText.setPosition(enterYourNameText.getPosition() + Vector2f(0, 100));

    RectangleShape nameCursor = RectangleShape(Vector2f(5, nameText.getCharacterSize()));
    nameCursor.setFillColor(Color::White);
    shapeSetOriginCenter(nameCursor);
    nameCursor.setPosition(nameText.getPosition() + Vector2f(nameText.getLocalBounds().width / 2 + 10, 14));

    Clock nameCursorTimer;

    Text saveText("Save Score", fontBebas);
    saveText.setFillColor(Color::Black);
    saveText.setCharacterSize(60);
    RectangleShape saveButton(Vector2f(saveText.getLocalBounds().width + 30, saveText.getLocalBounds().height + 30));
    textSetOriginCenter(saveText);
    shapeSetOriginCenter(saveButton);
    saveText.setPosition(nameText.getPosition() + Vector2f(0, 200));
    saveButton.setPosition(saveText.getPosition() + Vector2f(0, 15));

    std::vector<Score> scores = readScore();

    Music* musicPtr = &MusicHolder::GetMusic("assets/music/Votely.ogg");
    musicPtr->stop();
    musicPtr->setLoop(true);
    musicPtr->setVolume(5);
    musicPtr->play();
    
    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                return SceneChange(ScenesList::SCENE_MENU);
            }

            if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) && Keyboard::isKeyPressed(Keyboard::Escape)) {
                return {ScenesList::EXIT};
            }

            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
                setRectangleShapeColorOnMouseHover(saveButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (saveButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
                        if (nameText.getString() != "") {
                            scores.emplace_back(nameString, ((Game*)(getGamePtr()))->getScore());
                            sortScore(scores);
                            saveScore(scores);
                            return {ScenesList::SCENE_LEADERBOARD};
                        }
                    }

                    if (exitButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
                        return {ScenesList::SCENE_MENU};
                    }
                }
            }

            if (event.type == Event::TextEntered) {
                 if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    nameString += static_cast<char>(event.text.unicode);
                 } else if (event.text.unicode == 8) {
                     if (!nameString.empty()) {
                         nameString.pop_back();
                     }
                 } else if (event.text.unicode == 13) {
                     if (nameText.getString() != "") {
                        scores.emplace_back(nameString, ((Game*)(getGamePtr()))->getScore());
                        sortScore(scores);
                        saveScore(scores);
                        return {ScenesList::SCENE_LEADERBOARD};
                     }
                 }
                 nameText.setString(nameString);
                 textSetOriginCenter(nameText);
                 nameCursor.setPosition(nameText.getPosition() + Vector2f(nameText.getLocalBounds().width / 2 + 10, 14));
            }
        }

        if (nameCursorTimer.getElapsedTime() > milliseconds(500)) {
            nameCursorTimer.restart();
            if (nameCursor.getFillColor() == Color::White) {
                nameCursor.setFillColor(Color::Transparent);
            } else {
                nameCursor.setFillColor(Color::White);
            }
        }

        // Draw frame
        window.clear(COLOR_BACKGROUND);
        window.draw(gameOverText);
        window.draw(exitButton);
        window.draw(exitText);
        window.draw(enterYourNameText);
        window.draw(nameText);
        window.draw(nameCursor);
        window.draw(saveButton);
        window.draw(saveText);
        window.display();
    }
    
    return SceneChange(ScenesList::EXIT);
}