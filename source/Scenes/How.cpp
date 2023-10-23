#include "How.hpp"

SceneChange How::run(RenderWindow &window) {
    int PADDING = 30;

    Font fontBebas = FontHolder::GetFont("assets/fonts/BebasNeue-Regular.otf");

    Text exitText("<", fontBebas);
    exitText.setFillColor(Color::Black);
    exitText.setCharacterSize(60);
    RectangleShape exitButton(Vector2f(exitText.getLocalBounds().width + PADDING, exitText.getLocalBounds().height + PADDING));
    textSetOriginCenter(exitText);
    shapeSetOriginCenter(exitButton);
    exitText.setPosition(Vector2f(100, 100));
    exitButton.setPosition(exitText.getPosition() + Vector2f(0, PADDING));

    struct HowStruct {
        Sprite sprite;
        Text overlay;
        Text description;
    } howStruct[] = {
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/keyboard_blank.png")), Text("W", fontBebas), Text("Move up", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/keyboard_blank.png")), Text("A", fontBebas), Text("Move left", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/keyboard_blank.png")), Text("S", fontBebas), Text("Move down", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/keyboard_blank.png")), Text("D", fontBebas), Text("Move right", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/keyboard_blank.png")), Text("R", fontBebas), Text("Reload", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/mouse_right.png")), Text("", fontBebas), Text("Reload", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/ui/mouse_left.png")), Text("", fontBebas), Text("Shoot", fontBebas)}
    };

    for (unsigned int i = 0; i < sizeof(howStruct) / sizeof(howStruct[0]); i++) {
        howStruct[i].sprite.setScale(0.8, 0.8);
        howStruct[i].sprite.setPosition(Vector2f(200, 300 + (i * 100)));
        spriteSetOriginCenter(howStruct[i].sprite);

        textSetOriginCenter(howStruct[i].overlay);
        howStruct[i].overlay.setPosition(howStruct[i].sprite.getPosition() - Vector2f(0, 15));
        howStruct[i].overlay.setFillColor(Color::Black);
        howStruct[i].overlay.setCharacterSize(40);

        howStruct[i].description.setOrigin(0, howStruct[i].description.getLocalBounds().height / 2);
        howStruct[i].description.setPosition(howStruct[i].sprite.getPosition() + Vector2f(100, -(howStruct[i].sprite.getLocalBounds().height / 4)));
        howStruct[i].description.setFillColor(Color::White);
        howStruct[i].description.setCharacterSize(60);
    }

    Music* musicPtr = &MusicHolder::GetMusic("assets/music/Spow.ogg");
    musicPtr->play();

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
        for (auto & i : howStruct) {
            window.draw(i.sprite);
            window.draw(i.overlay);
            window.draw(i.description);
        }
        window.display();
    }

    return SceneChange(ScenesList::EXIT);
}
