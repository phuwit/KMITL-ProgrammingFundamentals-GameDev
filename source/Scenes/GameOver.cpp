#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"

class GameOver : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange GameOver::run(RenderWindow &window) {
    return SceneChange(ScenesList::EXIT);
}