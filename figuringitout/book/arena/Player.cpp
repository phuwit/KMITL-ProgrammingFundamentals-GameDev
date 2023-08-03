#include <cmath>
#define _USE_MATH_DEFINES

#include "Player.hpp"
#include "TextureHolder.cpp"

Player::Player () {
    resetPlayerStats();

    m_Texture = TextureHolder::GetTexture("graphics/player.png");
    m_Sprite.setTexture(m_Texture);

    // Set origin to center of a sprite to get good rotation
    m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize) {
    // set pos to middle of arena
    m_Position.x = arena.width / 2;
    m_Position.y = arena.height / 2;

    // copy detials of arena params to member var
    // to detetct wall collision
    m_Arena.left = arena.left;
    m_Arena.width = arena.width;
    m_Arena.top = arena.top;
    m_Arena.height = arena.height;

    // save tile size to member var
    m_TileSize = tileSize;

    // save screen resolution to member var
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats() {
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

bool Player::hit(Time timeHit) {
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    else {
        return false;
    }
}


Time Player::getLastHitTime() {
    return m_LastHit;
}

FloatRect Player::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter() {
    return m_Position;
}

float Player::getRotation() {
    return m_Sprite.getRotation();
}

Sprite Player::getSprite() {
    return m_Sprite;
}

int Player::getHealth() {
    return m_Health;
}


void Player::upgradeSpeed() {
    // 20% speed upgrade
    m_Speed += START_SPEED * 0.2;
}

void Player::upgradeHealth() {
    // 20%v health upgrade
    m_MaxHealth += START_HEALTH * 0.2;
}

void Player::increaseHealthLevel(int amount) {
    m_Health += amount;
    if (m_Health > m_MaxHealth) {
        m_Health = m_MaxHealth;
    }
}


void Player::moveLeft() {
    m_LeftPressed = true;
}

void Player::moveRight() {
    m_RightPressed = true;
}

void Player::moveUp() {
    m_UpPressed = true;
}

void Player::moveDown() {
    m_DownPressed = true;
}

void Player::stopLeft() {
    m_LeftPressed = false;
}

void Player::stopRight() {
    m_RightPressed = false;
}

void Player::stopUp() {
    m_UpPressed = false;
}

void Player::stopDown() {
    m_DownPressed = false;
}


void Player::update(float elapsedTime, Vector2i mousePosition) {
    // movement
    if (m_LeftPressed)  m_Position.x -= m_Speed * elapsedTime;
    if (m_RightPressed) m_Position.x += m_Speed * elapsedTime;
    if (m_UpPressed)    m_Position.y -= m_Speed * elapsedTime;
    if (m_DownPressed)  m_Position.y += m_Speed * elapsedTime;
    m_Sprite.setPosition(m_Position);

    // detect wall collision
    if (m_Position.x > m_Arena.width - m_TileSize)  m_Position.x = m_Arena.width - m_TileSize;
    if (m_Position.x < m_Arena.left + m_TileSize)   m_Position.x = m_Arena.left + m_TileSize;
    if (m_Position.y > m_Arena.height - m_TileSize) m_Position.y = m_Arena.height - m_TileSize;
    if (m_Position.y < m_Arena.top + m_TileSize)    m_Position.y = m_Arena.top + m_TileSize;

    // calculate player angle
    float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
                         mousePosition.x - m_Resolution.x / 2)
                   * 180 / M_PI);
    m_Sprite.setRotation(angle);
}
