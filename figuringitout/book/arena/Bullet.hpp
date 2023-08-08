#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
    private:
        Vector2f m_Position;
        RectangleShape m_BulletShape;
        bool m_InFlight = false;
        float m_BulletSpeed = 1000;
        // bullet distance between frame
        float m_BulletDeltaX;
        float m_BulletDeltaY;

        // remove if exit the boundries
        // max range 1000 px
        const float m_MAX_RANGE = 1000;
        float m_MaxX;
        float m_MinX;
        float m_MaxY;
        float m_MinY;
    
    public:
        Bullet();
        // make new bullet
        void shoot(Vector2f startPos, Vector2f targetPos);
        // stop bullet
        void stop();

        // getters
        bool isInFlight();
        FloatRect getPosition();
        RectangleShape getShape();

        void update(float elapsedTime);
};