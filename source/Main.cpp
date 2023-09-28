#include "CommonEnum.hpp"
#include "TextureHolder.cpp"
#include "Scene.hpp"

// #include "Menu.cpp"
#include "Game.cpp"
// #include "Paused.cpp"
// #include "LevelUp.cpp"
// #include "GameOver.cpp"

int main() {
    // instance THE singleton instance of texture holder
    TextureHolder holder;

    // Applications variables
    std::vector<Scenes*> Scenes;
    SceneChange currentScene = SceneChange(ScenesList::SCENE_MENU);

    Vector2f screenResolution;

    std::vector<sf::VideoMode> allVideoModes = VideoMode::getFullscreenModes();
    VideoMode videoMode = VideoMode((int)allVideoModes[0].width, (int)allVideoModes[0].height, allVideoModes[0].bitsPerPixel);
    
    screenResolution.x = videoMode.width;
    screenResolution.y = videoMode.height;

    // screenResolution.x = 1920;
    // screenResolution.y = 1080;
    
    // RenderWindow window(videoMode, "Brain Blast!", Style::Fullscreen);
    RenderWindow window(videoMode, "Brain Blast!");
    // RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Brain Blast!");

    // window.setMouseCursorVisible(false);

    // Mouse cursor no more visible
    window.setMouseCursorVisible(false);

    // Screens preparations
    // Menu menu;
    // Scenes.push_back(&menu);
    Game game;
    Scenes.push_back(&game);
    // Paused paused;
    // Scenes.push_back(&paused);
    // LevelUp levelUp;
    // Scenes.push_back(&levelUp);
    // GameOver gameOver;
    // Scenes.push_back(&gameOver);

    // Main loop
    while (currentScene.getNextScreen() >= 0) {
        currentScene = Scenes[currentScene.getNextScreen()]->run(window);
    }

    return EXIT_SUCCESS;
}