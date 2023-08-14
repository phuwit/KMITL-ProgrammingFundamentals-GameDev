#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
    private:
        const float START_SPEED = 200;
        const float START_HEALTH = 100;

        Vector2f m_Position;
        Texture m_Texture;
        Sprite m_Sprite;
        Vector2f m_Resolution;
        IntRect m_Arena;
        int m_TileSize;

        int m_Health;
        int m_MaxHealth;
        Time m_LastHit;
        float m_Speed;

        bool m_UpPressed;
        bool m_DownPressed;
        bool m_LeftPressed;
        bool m_RightPressed;

    public:
        Player();
        // spawns player (duh) args: size-location of a level, resolution, size of background tiles
        void spawn(IntRect arena, Vector2f resolution, int tileSize);
        void resetPlayerStats();
        bool hit(Time timeHit);

        // getters
        // last hit time for grace period between attacks
        Time getLastHitTime();
        FloatRect getPosition();
        // get pos center of a sprite
        Vector2f getCenter();
        float getRotation();
        Sprite getSprite();
        RectangleShape getDrawableHitbox();
        int getHealth();

        // speed upgrade
        void upgradeSpeed();
        // max health upgrade
        void upgradeHealth();
        // refill health
        void increaseHealthLevel(int amount);

        // movements
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void stopLeft();
        void stopRight();
        void stopUp();
        void stopDown();

        void update(float elapsedTime, Vector2i mousePosition);
};
