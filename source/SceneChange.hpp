#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"

using namespace sf;

class SceneChange {
    private:
        Texture m_Screenshot;
        int m_nextScreen;
    public:
        SceneChange(int nextScreen, Texture screenshot);
        SceneChange(int nextScreen);
        Texture getScreenShot();
        int getNextScreen();
};

SceneChange::SceneChange(int nextScreen, Texture screenshot) {
    m_Screenshot = screenshot;
    m_nextScreen = nextScreen;
}

SceneChange::SceneChange(int nextScreen) {
    m_Screenshot = TextureHolder::GetTexture("assets/notexture.png");
    m_nextScreen = nextScreen;
}

Texture SceneChange::getScreenShot() {
    return m_Screenshot;
}

int SceneChange::getNextScreen() {
    return m_nextScreen;
}