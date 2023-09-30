#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"

class Paused : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};
