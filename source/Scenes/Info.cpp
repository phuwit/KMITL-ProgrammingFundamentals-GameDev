#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/FontHolder.cpp"
#include "../Tools/SetOriginCenter.cpp"
#include "../Tools/SetRectangleShapeOnMouseHover.cpp"
#include "../Tools/OpenURL.cpp"

using namespace sf;

class Info : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange Info::run(RenderWindow &window) {
    int BUTTON_PADDING = 30;

    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    Text exitText("<", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(60);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + BUTTON_PADDING, exitText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setPosition(Vector2f(100, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(0, BUTTON_PADDING));
    
    Text paragraphText;
    paragraphText.setFont(fontBebas);
    paragraphText.setCharacterSize(48);
    paragraphText.setPosition(Vector2f(200, 200));
    paragraphText.setString("\
    Brain Blast! \n\
    2D top-down arcade zombie shooter.\n\
    Made using C++ and SFML.\n\
    \n\
    Made for KMITL 01076103 \"Programming Fundamentals\".\n\
    Instructed by Asst.Prof.Dr. Thanunchai Threepak.\n\
    \n\
    Made by Phuwit Puthipairoj, with help from friends :> \n\
    KMITL Computer Engineering Student, Class of 2023. Student ID : 66010648 \n\
    ");

    Text githubText("Git Repo", fontBebas);
    githubText.setFillColor(Color::Black);
    githubText.setCharacterSize(60);
    RectangleShape githubButton(Vector2f(githubText.getLocalBounds().width + BUTTON_PADDING, githubText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(githubText);
    shapeSetOriginCenter(githubButton);
    githubText.setPosition(paragraphText.getPosition() + Vector2f((githubText.getLocalBounds().width / 2) + BUTTON_PADDING + 20,  paragraphText.getLocalBounds().height + 50));
    githubButton.setPosition(githubText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

    Text attributionText("Attributions", fontBebas);
    attributionText.setFillColor(Color::Black);
    attributionText.setCharacterSize(60);
    RectangleShape attributionButton(Vector2f(attributionText.getLocalBounds().width + BUTTON_PADDING, attributionText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(attributionText);
    shapeSetOriginCenter(attributionButton);
    attributionText.setPosition(githubText.getPosition() + Vector2f((githubText.getLocalBounds().width / 2) + (attributionText.getLocalBounds().width / 2) + BUTTON_PADDING + 50, 0));
    attributionButton.setPosition(attributionText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

    Text downloadText("Download Latest Build", fontBebas);
    downloadText.setFillColor(Color::Black);
    downloadText.setCharacterSize(60);
    RectangleShape downloadButton(Vector2f(downloadText.getLocalBounds().width + BUTTON_PADDING, downloadText.getLocalBounds().height + BUTTON_PADDING));
    textSetOriginCenter(downloadText);
    shapeSetOriginCenter(downloadButton);
    downloadText.setPosition(attributionText.getPosition() + Vector2f((attributionText.getLocalBounds().width / 2) + (downloadText.getLocalBounds().width / 2) + BUTTON_PADDING + 50, 0));
    downloadButton.setPosition(downloadText.getPosition() + Vector2f(0, BUTTON_PADDING / 2));

    Music* musicPtr = &MusicHolder::GetMusic("assets/music/Spow.ogg");
    musicPtr->play();

    while (window.isOpen()) {
        // Update frame
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                setRectangleShapeColorOnMouseHover(exitButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
                setRectangleShapeColorOnMouseHover(githubButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
                setRectangleShapeColorOnMouseHover(attributionButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
                setRectangleShapeColorOnMouseHover(downloadButton, mouseScreenPosition, Color(189, 189, 189), Color::White);
            } else if (event.type == Event::MouseButtonPressed) {
                Vector2f mouseScreenPosition = Vector2f(Mouse::getPosition(window));

                if (exitButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    return SceneChange(ScenesList::SCENE_MENU);
                } else if (githubButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    openURL("https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev");
                } else if (attributionButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    openURL("https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev/blob/main/attribution.md");
                } else if (downloadButton.getGlobalBounds().contains(Vector2f(mouseScreenPosition))) {
                    openURL("https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev/actions/workflows/ci.yml\?query=branch%3Amain+is%3Asuccess");
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
        window.draw(paragraphText);
        window.draw(githubButton);
        window.draw(githubText);
        window.draw(attributionButton);
        window.draw(attributionText);
        window.draw(downloadButton);
        window.draw(downloadText);
        window.display();
    }

    return SceneChange(ScenesList::EXIT);
}
