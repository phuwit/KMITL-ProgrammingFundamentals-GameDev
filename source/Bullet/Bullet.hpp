#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
    private:
        Vector2f m_Position;
        float m_SpriteScaling = 1;
        Uint8 m_SpriteAlpha = 0.75 * 255;
        Sprite m_Sprite;
        bool m_InFlight = false;
        float m_BulletSpeed = 500;
        // bullet distance between frame
        float m_BulletDeltaX;
        float m_BulletDeltaY;

        IntRect m_PlayArea;
    
    public:
        Bullet();
        // make new bullet
        void shoot(Vector2f startPos, Vector2f targetPos, IntRect playArea, float spriteScaling);
        // stop bullet
        void stop();

        // getters
        bool isInFlight();
        FloatRect getPosition();
        Sprite getShape();

        void update(Time frameTime);
};