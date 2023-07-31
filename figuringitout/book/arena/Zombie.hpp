#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie {
    private:
        enum class ZombieType { Bloater, Chaser, Crawler};
        // speed of each zombie types
        const float BLOATER_SPEED = 40;
        const float CHASER_SPEED = 40;
        const float CRAWLER_SPEED = 40;
        // hp of each zombie type
        const float BLOATER_HEALTH = 5;
        const float CHASER_HEALTH = 1;
        const float CRAWLER_HEALTH = 3;
        // make each zombie speed varies slightly to prevent bunching up
        const int MAX_VARIANCE = 30;
        const int OFFSET = 101 - MAX_VARIANCE;

        Vector2f m_Position;
        Sprite m_Sprite;
        float m_Speed;
        float m_Health;
        bool m_Alive;

    public:
        // spawn a new zombie
        void spawn(float startX, float startY, ZombieType type, int seed);
        // handle bullet hitting a zombie
        bool hit();
        
        // getters
        bool isAlive();
        FloatRect getPosition();
        Sprite getSprite();

        void update(float elapsedTime, Vector2f playerLocation);
};