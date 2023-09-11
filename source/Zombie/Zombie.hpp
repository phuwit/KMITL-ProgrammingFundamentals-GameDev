#pragma once

#include <SFML/Graphics.hpp>
#include "../CommonEnum.hpp"

using namespace sf;

class Zombie {
    private:
        const float SPEED[sizeof(ZombieType)] = {50, 35, 65};
        const float HEALTH[sizeof(ZombieType)] = {50, 85, 35};
        // make each zombie speed varies slightly to prevent bunching up
        const int MAX_VARIANCE = 30;
        const int OFFSET = 101 - MAX_VARIANCE;

        Vector2f m_Position;
        float m_SpriteScaling = 1;
        Sprite m_Sprite;
        FloatRect m_Bounds;
        Vector2f m_CenterOffset;
        float m_Speed;
        float m_Health;
        bool m_Alive;

    public:
        Zombie(float spriteScaling);
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