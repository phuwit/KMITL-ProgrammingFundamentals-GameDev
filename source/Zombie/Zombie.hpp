#pragma once

#include <SFML/Graphics.hpp>
#include "../CommonEnum.hpp"

using namespace sf;

class Zombie {
    private:
        const float M_SPEED_BASE[sizeof(ZombieType)] = {50, 35, 65};
        const float M_HEALTH_BASE[sizeof(ZombieType)] = {5, 8, 3};
        const Color M_COLOR_BASE[sizeof(ZombieType)] = {Color(255, 255, 0, 255), Color(0, 255, 255, 255), Color(255, 0, 255, 255)};
        const String M_SPRITE_FILENAME[sizeof(ZombieType)] = {"../assets/sprites/zombies/wild/Run.png", "../assets/sprites/zombies/male/Run.png","../assets/sprites/zombies/female/Run.png"};
        // make each zombie speed varies slightly to prevent bunching up
        const int M_MAX_VARIANCE = 30;
        const int M_OFFSET = 101 - M_MAX_VARIANCE;

        Vector2f m_Position;
        float m_SpriteScaling = 1;
        Sprite m_Sprite;
        FloatRect m_Bounds;
        Vector2f m_CenterOffset;
        float m_Speed;
        float m_Health;
        bool m_Alive;

    public:
        Zombie();
        // spawn a new zombie
        void spawn(Vector2f spawnLoaction, float spriteScaling, ZombieType type, int seed);
        // handle bullet hitting a zombie
        bool hit();
        
        // getters
        bool isAlive();
        FloatRect getHitBox();
        Sprite getSprite();
        RectangleShape getDrawableHitbox();

        void update(Time frameTime, Vector2f playerLocation);
};