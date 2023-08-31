#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
    private:
        const int M_BASE_SPEED = 400;
        const int M_BASE_DAMAGE = 10;

        Vector2f m_Position;
        Sprite m_Sprite;
        bool m_InFlight = false;
        float m_BulletSpeed = 1000;
        // bullet distance between frame
        float m_BulletDeltaX;
        float m_BulletDeltaY;

        IntRect m_PlayArea;
    
    public:
        Bullet();
        // make new bullet
        void shoot(Vector2f startPos, Vector2f targetPos, IntRect playArea);
        // stop bullet
        void stop();

        // getters
        bool isInFlight();
        FloatRect getPosition();
        Sprite getShape();

        void update(Time frameTime);
};