#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Pickups {
    // so i can make a pickuptypes variable and not mess up the code styling too much
    public: enum PickupTypes { health, ammo };

    private:
        // base values
        const int HEALTH_BASE_VALUE = 50;
        const int AMMO_BASE_VALUE = 12;
        const int BASE_SECONDS_TO_WAIT = 10;
        const int BASE_SECONDS_TO_LIVE = 5;

        Sprite m_Sprite;
        // set arena size and call spawn
        IntRect m_Arena;
        // pickup resource value
        int m_Value;
        // pickup type
        PickupTypes m_Type;

        // handle spawning and disappearing
        bool m_Spawned;
        float m_SecondsSinceSpawned;
        float m_SecondsSinceDespawned;
        float m_SecondsToLive;
        float m_SecondsToWait;

    public:
        Pickups(PickupTypes type);
        void setArena(IntRect arena);
        void spawn();

        // pick up the... pickups and return the pickup value
        int pickUp();
        void upgrade();

        // getters
        FloatRect getPosition();
        Sprite getSprite();
        bool isSpawned();

        void update(float elapsedTime);
};
