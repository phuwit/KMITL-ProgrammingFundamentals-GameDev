#include "CommonEnum.hpp"
#include "TextureHolder.cpp"
#include "Scene.hpp"

#include "Game.cpp"

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
    // TODO
    // scene_0 s0;
    // Scenes.push_back(&s0);
    // scene_1 s1;
    // Scenes.push_back(&s1);
    Game game;
    Scenes.push_back(&game);

    // Main loop
    while (currentScene.getNextScreen() >= 0) {
        currentScene = Scenes[currentScene.getNextScreen()]->run(window);
    }

    return EXIT_SUCCESS;
}