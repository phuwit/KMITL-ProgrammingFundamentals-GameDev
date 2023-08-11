#pragma once

#include "Pickups.hpp"
#include "TextureHolder.cpp"

Pickups::Pickups(PickupTypes type) {
    m_Type = type;
    string filename;
    
    // set type specific values
    if (m_Type == PickupTypes::health) {
        // m_Sprite = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));
        filename = "graphics/health_pickup.png";
        m_Value = HEALTH_BASE_VALUE;
    }
    else if (m_Type == PickupTypes::ammo) {
        // m_Sprite = Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
        filename = "graphics/ammo_pickup.png";
        m_Value = AMMO_BASE_VALUE;
    }

    m_Sprite = Sprite(TextureHolder::GetTexture(filename));
    m_Sprite.setOrigin(25, 25);

    m_SecondsToLive = BASE_SECONDS_TO_LIVE;
    m_SecondsToWait = BASE_SECONDS_TO_WAIT;
}

void Pickups::setArena(IntRect arena) {
    // copy arena's detail
    m_Arena.left = arena.left + 50;
    m_Arena.width = arena.width - 50;
    m_Arena.top = arena.top + 50;
    m_Arena.height = arena.height - 50;
    spawn();
}

void Pickups::spawn() {
    // spawn at random location
    srand((uint)time(0) / ((uint)m_Type + 1));
    int x = (rand() % m_Arena.width);
    srand((uint)time(0) * ((uint)m_Type + 1));
    int y = (rand() % m_Arena.height);
    m_Sprite.setPosition(x, y);

    m_SecondsSinceSpawned = 0;
    m_Spawned = true;
}

int Pickups::pickUp() {
    m_Spawned = false;
    m_SecondsSinceDespawned = 0;
    return m_Value;
}

void Pickups::upgrade() {
    if (m_Type == PickupTypes::health) {
        m_Value += (HEALTH_BASE_VALUE * 0.5);
    }
    else if (m_Type == PickupTypes::ammo) {
        m_Value += (AMMO_BASE_VALUE * 0.5);
    }

    // reduce spawn timer and increase time to despawn
    m_SecondsToWait -= (BASE_SECONDS_TO_WAIT / 10);
    m_SecondsToLive -= (BASE_SECONDS_TO_LIVE / 10);
}

FloatRect Pickups::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Sprite Pickups::getSprite() {
    return m_Sprite;
}

bool Pickups::isSpawned() {
    return m_Spawned;
}

void Pickups::update(float elapsedTime) {
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
        spawn();
    }
}
