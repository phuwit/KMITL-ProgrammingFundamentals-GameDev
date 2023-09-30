#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"

class LevelUp : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange LevelUp::run(RenderWindow &window) {
    Texture textureScreenshot;
    textureScreenshot.loadFromImage(getScreenShot());
    Sprite screenshot(textureScreenshot);

    Font fontBebas;
    fontBebas.loadFromFile("assets/fonts/BebasNeue-Regular.otf");
    Text textLevelUp("Level Up!", fontBebas, 60);
    textLevelUp.setPosition(Vector2f(50, 50));

    while (window.isOpen())
    {   
        window.clear(COLOR_BACKGROUND);
        window.draw(screenshot);
        window.draw(textLevelUp);
        window.display();
    }
    

    return SceneChange(ScenesList::EXIT);
}
