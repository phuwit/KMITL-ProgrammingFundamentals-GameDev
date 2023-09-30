#include <SFML/Graphics.hpp>

#include "CommonEnum.hpp"
#include "Scenes.hpp"

class LevelUp : public Scenes {
    public:
        virtual SceneChange run(RenderWindow &window);
};
