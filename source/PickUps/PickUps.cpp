#pragma once

#include "PickUps.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.hpp"

PickUps::PickUps(PickupsType type, bool isSpawnRandom) {
    m_Type = type;
    m_SpawnRandom = isSpawnRandom;

    m_Sprite = Sprite(TextureHolder::GetTexture(TEXTURE_NAME[m_Type]));
    m_Value = BASE_VALUE[m_Type];
    m_Sprite.setOrigin(25, 25);

    m_SecondsToLive = BASE_SECONDS_TO_LIVE;
    m_SecondsToWait = BASE_SECONDS_TO_WAIT;
}

void PickUps::setArena(IntRect arena) {
    // copy arena's detail
    m_Arena.left = arena.left + 50;
    m_Arena.width = arena.width - 50;
    m_Arena.top = arena.top + 50;
    m_Arena.height = arena.height - 50;
}

void PickUps::spawnRandom() {
    // spawn at random location
    srand((uint)time(0) / ((uint)m_Type + 1));
    int x = (rand() % m_Arena.width);
    srand((uint)time(0) * ((uint)m_Type + 1));
    int y = (rand() % m_Arena.height);
    m_Sprite.setPosition(x, y);

    m_SecondsSinceSpawned = 0;
    m_Spawned = true;
}

void PickUps::spawnAt(Vector2f location) {
    m_Sprite.setPosition(location);

    m_SecondsSinceSpawned = 0;
    m_Spawned = true;
}

int PickUps::take() {
    m_Spawned = false;
    m_SecondsSinceDespawned = 0;
    return m_Value;
}

void PickUps::upgrade() {
    if (m_Type == PickupsType::PICKUPS_HEALTH) {
        m_Value += (BASE_VALUE[m_Type] * 0.5);
    }
    else if (m_Type == PickupsType::PICKUPS_AMMO) {
        m_Value += (BASE_VALUE[m_Type] * 0.5);
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

bool PickUps::isSpawned() {
    return m_Spawned;
}

void PickUps::update(float elapsedTime) {
    // update timer
    if (m_Spawned)  m_SecondsSinceSpawned += elapsedTime;
    else            m_SecondsSinceDespawned += elapsedTime;

    // hide the pcikup if timeout
    if ((m_SecondsSinceSpawned > m_SecondsToLive) && m_Spawned) {
        m_Spawned = false;
        m_SecondsSinceDespawned = 0;
    }
    // spawn new one if exceeded the despawn timer
    else if ((m_SecondsSinceDespawned > m_SecondsToWait) && !m_Spawned) {
        spawnRandom();
    }
}
