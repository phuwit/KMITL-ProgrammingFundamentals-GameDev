#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"

class LevelUp : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange LevelUp::run(RenderWindow &window) {
    Sprite screenshot(getScreenShot());

    while (window.isOpen())
    {   
        window.clear(COLOR_BACKGROUND);
        window.draw(screenshot);
        window.display();
    }
    

    return SceneChange(ScenesList::EXIT);
}
