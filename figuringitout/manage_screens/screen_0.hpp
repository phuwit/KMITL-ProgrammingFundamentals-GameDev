#include <SFML/Graphics.hpp>
#include <iostream>

#include "cScreen.hpp"

class screen_0 : public cScreen {
   private:
    int alpha_max;
    int alpha_div;
    bool playing;

   public:
    screen_0(void);
    virtual int Run(sf::RenderWindow &App);
};

screen_0::screen_0(void) {
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
}

int screen_0::Run(sf::RenderWindow &App) {
    sf::Event Event;
    bool Running = true;
    sf::Texture Texture;
    sf::Sprite Sprite;
    int alpha = 0;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;

    if (!Texture.loadFromFile("presentation.jpg")) {
        std::cerr << "Error loading presentation.jpg" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    Sprite.setColor(sf::Color(255, 255, 255, alpha));
    if (!Font.loadFromFile("BebasNeue-Regular.otf")) {
        std::cerr << "Error loading BebasNeue-Regular.otf" << std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Play");
    Menu1.setPosition({280.f, 160.f});

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Exit");
    Menu2.setPosition({280.f, 220.f});

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Continue");
    Menu3.setPosition({280.f, 160.f});

    if (playing) {
        alpha = alpha_max;
    }

    while (Running) {
        // Verifying events
        while (App.pollEvent(Event)) {
            // Window closed
            if (Event.type == sf::Event::Closed) {
                return (-1);
            }
            // Key pressed
            if (Event.type == sf::Event::KeyPressed) {
                switch (Event.key.code) {
                    case sf::Keyboard::Up:
                        menu = 0;
                        break;
                    case sf::Keyboard::Down:
                        menu = 1;
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0) {
                            // Let's get play !
                            playing = true;
                            return (1);
                        } else {
                            // Let's get work...
                            return (-1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        // When getting at alpha_max, we stop modifying the sprite
        if (alpha < alpha_max) {
            alpha++;
        }
        Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
        if (menu == 0) {
            Menu1.setFillColor(sf::Color(255, 0, 0, 255));
            Menu2.setFillColor(sf::Color(255, 255, 255, 255));
            Menu3.setFillColor(sf::Color(255, 0, 0, 255));
        } else {
            Menu1.setFillColor(sf::Color(255, 255, 255, 255));
            Menu2.setFillColor(sf::Color(255, 0, 0, 255));
            Menu3.setFillColor(sf::Color(255, 255, 255, 255));
        }

        // Clearing screen
        App.clear();
        // Drawing
        App.draw(Sprite);
        if (alpha == alpha_max) {
            if (playing) {
                App.draw(Menu3);
            } else {
                App.draw(Menu1);
            }
            App.draw(Menu2);
        }
        App.display();
    }

    // Never reaching this point normally, but just in case, exit the
    // application
    return (-1);
}