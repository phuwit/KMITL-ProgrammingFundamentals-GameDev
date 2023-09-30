#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"

class GameOver : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange GameOver::run(RenderWindow &window) {
    return SceneChange(ScenesList::EXIT);
}