#include <SFML/Graphics.hpp>
#include <iostream>

#include "screens.hpp"

int main(int argc, char** argv) {
    // Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;

    // Window creation
    sf::RenderWindow App(sf::VideoMode(640, 480, 32), "SFML Demo 3");

    // Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    // Screens preparations
    screen_0 s0;
    Screens.push_back(&s0);
    screen_1 s1;
    Screens.push_back(&s1);

    // Main loop
    while (screen >= 0) {
        screen = Screens[screen]->Run(App);
    }

    return EXIT_SUCCESS;
}