#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"

class Info : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};

SceneChange Info::run(RenderWindow &window) {
    return SceneChange(ScenesList::EXIT);
}
