#include "CommonEnum.hpp"
#include "Scene.hpp"
#include "SceneChange.hpp"

int main() {
    // Applications variables
    std::vector<Scenes*> Scenes;
    int currentScene = 0;

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

    // instance THE singleton instance of texture holder
    TextureHolder holder;

    // Mouse cursor no more visible
    window.setMouseCursorVisible(false);

    // Screens preparations
    // TODO
    // scene_0 s0;
    // Scenes.push_back(&s0);
    // scene_1 s1;
    // Scenes.push_back(&s1);

    // Main loop
    while (currentScene >= 0) {
        currentScene = Scenes[currentScene]->Run(window);
    }

    return EXIT_SUCCESS;
}