#pragma once

#include <SFML/Graphics.hpp>
#include "../CommonEnum.hpp"

using namespace sf;

class Zombie {
    private:
        const float M_SPEED_BASE[sizeof(ZombieType)] = {120, 80, 150};
        const float M_HEALTH_BASE[sizeof(ZombieType)] = {6, 8, 4};
        const Color M_COLOR_BASE[sizeof(ZombieType)] = {Color(255, 255, 0, 255), Color(0, 255, 255, 255), Color(255, 0, 255, 255)};
        const String M_SPRITE_RUN_FILENAME[sizeof(ZombieType)] = {"assets/sprites/zombies/wild/Run.png", "assets/sprites/zombies/male/Run.png", "assets/sprites/zombies/female/Run.png"};
        const String M_SPRITE_DEATH_FILENAME[sizeof(ZombieType)] = {"assets/sprites/zombies/wild/Dead.png", "assets/sprites/zombies/male/Dead.png","assets/sprites/zombies/female/Dead.png"};
//        const IntRect M_SPRITE_RUN_CROP[sizeof(ZombieType)] = {IntRect(26, 40, 50, 56), IntRect(18, 32, 68, 64) , IntRect(31, 33, 57, 63)};
        const IntRect M_SPRITE_RUN_CROP[sizeof(ZombieType)] = {IntRect(0, 0, 96, 96), IntRect(0, 0, 96, 96) , IntRect(0, 0, 96, 96)};
        const IntRect M_SPRITE_DEATH_CROP[sizeof(ZombieType)] = {IntRect(406, 86, 74, 10), IntRect(416, 86, 64, 10) , IntRect(389, 86, 64, 10)};
        // make each zombie speed varies slightly to prevent bunching up
        const int M_MAX_VARIANCE = 30;
        const int M_OFFSET = 101 - M_MAX_VARIANCE;

        ZombieType m_Type;
        FloatRect m_PlayArea;
        Vector2f m_Position;
        float m_SpriteScaling = 1;
        Sprite m_Sprite;
        FloatRect m_Bounds;
        Vector2f m_CenterOffset;
        Vector2f m_Speed;
        Vector2i m_SpeedInverse = Vector2i(1, 1);
        Vector2i M_BASE_INVERSE_CHANCE = Vector2i(30000, 30000);
        ZombieMoveStyle m_MoveStyle;
        float m_Health;
        bool m_Alive;
        Time m_TimeSinceSpawn;

    public:
        Zombie();
        // spawn a new zombie
        void spawn(Vector2f spawnLoaction, float spriteScaling, ZombieType type, ZombieMoveStyle moveStyle, int seed, FloatRect playArea);
        // handle bullet hitting a zombie
        bool hit();
        
        // getters
        bool isAlive();
        FloatRect getHitBox();
        RectangleShape getDrawableHitbox();
        Sprite getSprite();
        Vector2f getPosition();
        Time getTimeSinceSpawned();

        void update(Time frameTime, Vector2f playerLocation);
        void animate();
};