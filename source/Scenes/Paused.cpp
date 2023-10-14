#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../CommonEnum.hpp"

class Paused : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange Paused::run(RenderWindow &window) {
    return SceneChange(ScenesList::SCENE_GAMEOVER);
}
