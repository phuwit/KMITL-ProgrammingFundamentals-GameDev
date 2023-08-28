#include <SFML/Graphics.hpp>

#include "ColorScale.cpp"

int main() {
    const int SIZE = 500;
    ColorScale gradient;
    gradient.insert(0.0, sf::Color::Red);
    gradient.insert(1.0, sf::Color::Magenta);
    gradient.insert(2.0, sf::Color::Blue);
    gradient.insert(3.0, sf::Color::Cyan);
    gradient.insert(4.0, sf::Color::Green);
    gradient.insert(5.0, sf::Color::Yellow);
    gradient.insert(6.0, sf::Color::Red);

    sf::Image image;
    image.create(SIZE, SIZE, sf::Color::Black);
    // draw circular gradient into an image : params = image reference, circle center, width of each band, gradient style
    gradient.draw(image, sf::Vector2f(500.0, 500.0), sf::Vector2f(100.0, 0.0),
                  GradientStyle::Circle);
    sf::Texture imageTexture;
    imageTexture.loadFromImage(image);

    sf::Sprite sprite(imageTexture);
    sf::RenderWindow App(sf::VideoMode(SIZE, SIZE, 32), "Gradient");
    App.draw(sprite);
    App.display();
    App.setFramerateLimit(1);

    while (App.isOpen()) {
        sf::Event event;
        while (App.pollEvent(event))
            ;
        App.display();
    }

    return 0;
}