#include "CommonEnum.hpp"
#include "Holders/TextureHolder.hpp"
#include "Holders/FontHolder.hpp"
#include "Holders/SoundHolder.hpp"
#include "Holders/MusicHolder.hpp"

#include "Scenes/Scenes.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Info.hpp"
#include "Scenes/Game.hpp"
#include "Scenes/Paused.hpp"
#include "Scenes/LevelUp.hpp"
#include "Scenes/GameOver.hpp"
#include "Scenes/Leaderboard.hpp"
#include "Scenes/How.hpp"

int main() {
    // instance THE singleton instance of texture holder
    TextureHolder textureHolder;
    FontHolder fontHolder;
    SoundHolder soundHolder;
    MusicHolder musicHolder;

    // Applications variables
    std::vector<Scenes*> Scenes;
    SceneChange currentScene = SceneChange(ScenesList::SCENE_MENU);

    std::vector<sf::VideoMode> allVideoModes = VideoMode::getFullscreenModes();
     VideoMode videoMode = VideoMode(allVideoModes[0]);
//    VideoMode videoMode = VideoMode(1920, 1080);
      
//     RenderWindow window(videoMode, "Brain Blast!", ContextSettings(0, 0, 8));
//     RenderWindow window(videoMode, "Brain Blast!", Style::None, ContextSettings(0, 0, 8));
     RenderWindow window(videoMode, "Brain Blast!", Style::Fullscreen, ContextSettings(0, 0, 8));

    // window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    // Screens preparations
    Menu menu;
    Scenes.push_back(&menu);
    Info info;
    Scenes.push_back(&info);
    Game* gamePtr = new Game(Vector2f(window.getSize()), Vector2f(1920, 1080));
    Scenes.push_back(gamePtr);
    Paused scenePaused;
    Scenes.push_back(&scenePaused);
    LevelUp levelUp;
    Scenes.push_back(&levelUp);
    GameOver gameOver;
    Scenes.push_back(&gameOver);
    Leaderboard leaderboard;
    Scenes.push_back(&leaderboard);
    How how;
    Scenes.push_back(&how);

    for (auto & Scene : Scenes) {
        Scene->setGamePtr(gamePtr);
    }

    // Main loop
    while (currentScene.getNextScreen() >= 0) {
        Scenes[currentScene.getNextScreen()]->setScreenShot(currentScene.getScreenShot());
        MusicHolder::PauseAll();
        currentScene = Scenes[currentScene.getNextScreen()]->run(window);
    }

    return EXIT_SUCCESS;
}