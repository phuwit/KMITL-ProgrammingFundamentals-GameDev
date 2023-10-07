#pragma once

#include <SFML/Graphics.hpp>
#include "../CommonEnum.hpp"

using namespace sf;

class Zombie {
    private:
        const float M_SPEED_BASE[sizeof(ZombieType)] = {50, 35, 65};
        const float M_HEALTH_BASE[sizeof(ZombieType)] = {5, 8, 3};
        const Color M_COLOR_BASE[sizeof(ZombieType)] = {Color(255, 255, 0, 255), Color(0, 255, 255, 255), Color(255, 0, 255, 255)};
        const String M_SPRITE_FILENAME[sizeof(ZombieType)] = {"assets/sprites/zombies/wild/Run.png", "assets/sprites/zombies/male/Run.png","assets/sprites/zombies/female/Run.png"};
        const IntRect M_SPRITE_CROP[sizeof(ZombieType)] = {IntRect(26 + 96, 40, 50, 56), IntRect(18, 32, 68, 64) , IntRect(31, 33, 57, 63)};
        // make each zombie speed varies slightly to prevent bunching up
        const int M_MAX_VARIANCE = 30;
        const int M_OFFSET = 101 - M_MAX_VARIANCE;

        FloatRect m_PlayArea;
        Vector2f m_Position;
        float m_SpriteScaling = 1;
        Sprite m_Sprite;
        FloatRect m_Bounds;
        Vector2f m_CenterOffset;
        Vector2f m_Speed;
        Vector2i m_SpeedInverse = Vector2i(1, 1);
        Vector2i M_BASE_INVERSE_CHANCE = Vector2i(10000, 10000);
        ZombieMoveStyle m_MoveStyle;
        float m_Peroid = 0;
        float m_SinAmplitude = 20;
        float m_Health;
        bool m_Alive;

    public:
        Zombie();
        // spawn a new zombie
        void spawn(Vector2f spawnLoaction, float spriteScaling, ZombieType type, ZombieMoveStyle moveStyle, int seed, FloatRect playArea);
        // handle bullet hitting a zombie
        bool hit();
        
        // getters
        bool isAlive();
        FloatRect getHitBox();
        Sprite getSprite();
        RectangleShape getDrawableHitbox();

        void update(Time frameTime, Vector2f playerLocation);
};