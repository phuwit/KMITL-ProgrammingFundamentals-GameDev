#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie {
    private:
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
        enum ZombieType { Bloater, Chaser, Crawler };
        // spawn a new zombie
        void spawn(Vector2f spawnLoaction, ZombieType type, int seed);
        // handle bullet hitting a zombie
        bool hit();
        
        // getters
        bool isAlive();
        FloatRect getPosition();
        Sprite getSprite();
        RectangleShape getDrawableHitbox();

        void update(float elapsedTime, Vector2f playerLocation);
};