#include "CommonEnum.hpp"
#include "Holders/TextureHolder.hpp"
#include "Holders/FontHolder.cpp"

#include "Scenes/Scenes.hpp"
#include "Scenes/Menu.cpp"
#include "Scenes/Info.cpp"
#include "Scenes/Game.cpp"
#include "Scenes/Paused.cpp"
#include "Scenes/LevelUp.cpp"
#include "Scenes/GameOver.cpp"

int main() {
    // instance THE singleton instance of texture holder
    TextureHolder textureHolder;
    FontHolder fontHolder;

    // Applications variables
    std::vector<Scenes*> Scenes;
    SceneChange currentScene = SceneChange(ScenesList::SCENE_MENU);

    std::vector<sf::VideoMode> allVideoModes = VideoMode::getFullscreenModes();
    // VideoMode videoMode = VideoMode(allVideoModes[0]);
    VideoMode videoMode = VideoMode(1920, 1080); 
      
    // RenderWindow window(videoMode, "Brain Blast!", Style::Fullscreen);
    RenderWindow window(videoMode, "Brain Blast!");
    // RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Brain Blast!");

    // window.setMouseCursorVisible(false);

    // Screens preparations
    Menu menu;
    Scenes.push_back(&menu);
    Info info;
    Scenes.push_back(&info);
    Game game(Vector2f(window.getSize()), Vector2f(window.getSize()));
    Scenes.push_back(&game);
    Paused paused;
    Scenes.push_back(&paused);
    LevelUp levelUp;
    Scenes.push_back(&levelUp);
    GameOver gameOver;
    Scenes.push_back(&gameOver);

    // Main loop
    while (currentScene.getNextScreen() >= 0) {
        Scenes[currentScene.getNextScreen()]->setScreenShot(currentScene.getScreenShot());
        currentScene = Scenes[currentScene.getNextScreen()]->run(window);
    }

    return EXIT_SUCCESS;
}