#pragma once

#include <SFML/Graphics.hpp>

#include "../CommonEnum.hpp"

using namespace sf;

class PickUps {
    private:
        // base values
        const int BASE_VALUE[sizeof(PickupsType)] = {5, 12, 2, 2};
        const String TEXTURE_NAME[sizeof(PickupsType)] = {"assets/sprites/pickups/pickups/health.png", "assets/sprites/pickups/pickups/ammo.png", "assets/sprites/pickups/pickups/speed.png", "assets/sprites/pickups/pickups/score.png"};
        const int BASE_SECONDS_TO_WAIT = 10;
        const int BASE_SECONDS_TO_LIVE = 5;

        Sprite m_Sprite;
        IntRect m_Arena;
        // pickup resource value
        int m_Value;
        // pickup type
        PickupsType m_Type;

        // handle spawning and disappearing
        bool m_SpawnRandom;
        bool m_Spawned;
        float m_SecondsSinceSpawned;
        float m_SecondsSinceDespawned;
        float m_SecondsToLive;
        float m_SecondsToWait;

    public:
        PickUps(PickupsType type, bool isSpawnRandom);
        void setArena(IntRect arena);
        void spawnRandom();
        void spawnAt(Vector2f location);

        // pick up the... pickups and return the pickup value
        int take();
        void upgrade();

        // getters
        FloatRect getPosition();
        Sprite getSprite();
        bool isSpawned();

        void update(float elapsedTime);
};
