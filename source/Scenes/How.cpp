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

    for (unsigned int i = 0; i < sizeof(howStruct) / sizeof(HowStruct); i++) {
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

    Text paragraphText;
    paragraphText.setFont(fontBebas);
    paragraphText.setCharacterSize(48);
    paragraphText.setPosition(Vector2f(600, 250));
    paragraphText.setString("\
    Kill zombies to get points! \n\
    Kill zombies faster to get more points! \n\
    \n\
    ");

    struct PickupStruct {
        Sprite sprite;
        Text description;
    } pickupStruct[] = {
            {Sprite(TextureHolder::GetTexture("assets/sprites/pickups/ammo.png")), Text("Get ammo", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/pickups/health.png")), Text("Heal yourself", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/pickups/score.png")), Text("Score multiplier", fontBebas)},
            {Sprite(TextureHolder::GetTexture("assets/sprites/pickups/speed.png")), Text("Speed boost", fontBebas)}
    };

    for (unsigned int i = 0; i < sizeof(pickupStruct) / sizeof(PickupStruct); i++) {
        pickupStruct[i].sprite.setScale(0.8, 0.8);
        pickupStruct[i].sprite.setPosition(Vector2f(paragraphText.getPosition().x + pickupStruct[i].sprite.getGlobalBounds().width, paragraphText.getPosition().y + paragraphText.getLocalBounds().height + 100 + (i * 100)));
        spriteSetOriginCenter(pickupStruct[i].sprite);

        pickupStruct[i].description.setOrigin(0, pickupStruct[i].description.getLocalBounds().height / 2);
        pickupStruct[i].description.setPosition(pickupStruct[i].sprite.getPosition() + Vector2f(100, -(pickupStruct[i].sprite.getLocalBounds().height / 4)));
        pickupStruct[i].description.setFillColor(Color::White);
        pickupStruct[i].description.setCharacterSize(60);
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

        if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) && Keyboard::isKeyPressed(Keyboard::Escape)) {
            return {ScenesList::EXIT};
        }

        // Draw frame
        window.clear(COLOR_BACKGROUND);
        window.draw(exitButton);
        window.draw(exitText);
        window.draw(paragraphText);

        for (auto & i : howStruct) {
            window.draw(i.sprite);
            window.draw(i.overlay);
            window.draw(i.description);
        }

        for (auto & i : pickupStruct) {
            window.draw(i.sprite);
            window.draw(i.description);
        }

        window.display();
    }

    return SceneChange(ScenesList::EXIT);
}
