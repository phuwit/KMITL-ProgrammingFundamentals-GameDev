#pragma once

#include <SFML/Graphics.hpp>

#include "../CommonEnum.hpp"

using namespace sf;

class PickUps {
    private:
        // base values
        const int BASE_VALUE[sizeof(PickupsType)] = {5, 12, 2, 2};
        const Time BASE_BUFF_DURATION[sizeof(PickupsType)] = {seconds(0), seconds(0), seconds(5), seconds(5)};
        const String TEXTURE_NAME[sizeof(PickupsType)] = {"assets/sprites/pickups/health.png", "assets/sprites/pickups/ammo.png", "assets/sprites/pickups/speed.png", "assets/sprites/pickups/score.png"};
        const int BASE_SECONDS_TO_WAIT = 10;
        const int BASE_SECONDS_TO_LIVE = 5;

        Sprite m_Sprite;
        IntRect m_PlayArea;
        // pickup resource value
        int m_Value;
        Time m_BuffDuration;
        // pickup type
        PickupsType m_Type;

        // handle spawning and disappearing
        bool m_SpawnRandom;
        bool m_Spawned = false;
        float m_SecondsSinceSpawned;
        float m_SecondsSinceDespawned;
        float m_SecondsToLive;
        float m_SecondsToWait;

    public:
        PickUps(PickupsType type, bool isSpawnRandom, IntRect playArea);
        void spawnRandom();
        void spawnAt(Vector2f location);

        // pick up the... pickups and return the pickup value
        int take();
        void upgrade();

        // getters
        FloatRect getPosition();
        Sprite getSprite();
        Time getBuffDuration();
        bool isSpawned();

        void update(Time frameTime);
};
