#include <utility>
#include "PickUps.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.hpp"

PickUps::PickUps(PickupsType type, bool isSpawnRandom, IntRect playArea) {
    srand((unsigned int)time(0) * (type + 1));
    m_Type = type;
    m_SpawnRandom = isSpawnRandom;
    m_PlayArea = playArea;

    m_Sprite = Sprite(TextureHolder::GetTexture(TEXTURE_NAME[m_Type]));
    m_Value = BASE_VALUE[m_Type];
    m_BuffDuration = BASE_BUFF_DURATION[m_Type];
    m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);

    m_SecondsToLive = BASE_SECONDS_TO_LIVE;
    m_SecondsToWait = BASE_SECONDS_TO_WAIT;
}

void PickUps::spawnRandom() {
    // spawn at random location
    int x = (rand() % m_PlayArea.width);
    int y = (rand() % m_PlayArea.height);
    m_Sprite.setPosition(x, y);

    m_SecondsSinceSpawned = 0;
    m_Spawned = true;
}

void PickUps::spawnNearPlayer(Vector2f playerLocation) {
    // spawn at random location
    int x = (rand() % (2 * MAX_DISTANCE_FROM_PLAYER)) - MAX_DISTANCE_FROM_PLAYER;
    int y = (rand() % (2 * MAX_DISTANCE_FROM_PLAYER)) - MAX_DISTANCE_FROM_PLAYER;

    int x_delta = abs(x - playerLocation.x);
    int y_delta = abs(y - playerLocation.y);

    if (x_delta < MIN_DISTANCE_FROM_PLAYER) {
        bool negative = (rand() % 2);
        if (negative) {
            x = -MIN_DISTANCE_FROM_PLAYER;
        } else {
            x = MIN_DISTANCE_FROM_PLAYER;
        }
    }

    if (y_delta < MIN_DISTANCE_FROM_PLAYER) {
        bool negative = (rand() % 2);
        if (negative) {
            y = -MIN_DISTANCE_FROM_PLAYER;
        } else {
            y = MIN_DISTANCE_FROM_PLAYER;
        }
    }

    Vector2f position = playerLocation + Vector2f(x, y);

    if (position.x > m_PlayArea.width) {
        position.x = m_PlayArea.width - 100;
    } else if (position.x < 0) {
        position.x = 100;
    }

    if (position.y > m_PlayArea.height) {
        position.y = m_PlayArea.height - 100;
    } else if (position.y < 0) {
        position.y = 100;
    }

    m_Sprite.setPosition(position);

    m_SecondsSinceSpawned = 0;
    m_Spawned = true;
}

void PickUps::spawnAt(Vector2f location) {
    m_Sprite.setPosition(location);

    m_SecondsSinceSpawned = 0;
    m_Spawned = true;
}

float PickUps::take() {
    m_Spawned = false;
    m_SecondsSinceDespawned = 0;
    return m_Value;
}

void PickUps::upgrade() {
    if (m_Type == PickupsType::PICKUPS_HEALTH) {
        m_Value += (BASE_VALUE[m_Type] * 0.1);
    }
    else if (m_Type == PickupsType::PICKUPS_AMMO) {
        m_Value += (BASE_VALUE[m_Type] * 0.1);
    }

    // reduce spawn timer and increase time to despawn
    m_SecondsToWait -= (BASE_SECONDS_TO_WAIT / 10);
    m_SecondsToLive -= (BASE_SECONDS_TO_LIVE / 10);
}

FloatRect PickUps::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Sprite PickUps::getSprite() {
    return m_Sprite;
}

Time PickUps::getBuffDuration() {
    return m_BuffDuration;
}

bool PickUps::isSpawned() {
    return m_Spawned;
}

void PickUps::update(Time frameTime, Vector2f playerLocation) {
    // update timer
    if (m_Spawned)  m_SecondsSinceSpawned += frameTime.asSeconds();
    else            m_SecondsSinceDespawned += frameTime.asSeconds();

    if (m_Spawned && (m_SecondsSinceSpawned > m_SecondsToLive * 0.8)) {
        m_Sprite.setColor(Color(255, 128, 128, 192));
    } else {
        m_Sprite.setColor(Color(255, 255, 255, 255));
    }

    // hide the pickup if timeout
    if ((m_SecondsSinceSpawned > m_SecondsToLive) && m_Spawned) {
        m_Spawned = false;
        m_SecondsSinceDespawned = 0;
    }
    // spawn new one if exceeded the despawn timer
    else if ((m_SecondsSinceDespawned > m_SecondsToWait) && !m_Spawned && m_SpawnRandom) {
        spawnNearPlayer(playerLocation);
    }
}
