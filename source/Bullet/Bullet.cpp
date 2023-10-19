#include <cmath>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include "../Holders/TextureHolder.hpp"

using namespace sf;

Bullet::Bullet() {
    m_Sprite.setTexture(TextureHolder::GetTexture("assets/sprites/gun/bullet.png"));
    m_Sprite.setScale(m_SpriteScaling, m_SpriteScaling);
}

void Bullet::shoot(Vector2f startPos, Vector2f targetPos, Vector2f spawnPos, IntRect playArea, float spriteScaling) {
    // keeping track of bullet
    m_InFlight = true;
    m_Position = spawnPos;
    m_SpriteScaling = spriteScaling;

    m_BulletRotationDegrees = ((atan2(targetPos.y - startPos.y,
                                    targetPos.x - startPos.x) 
                                * 180) / M_PI);

    m_PlayArea = playArea;
    m_Sprite.setPosition(m_Position);
    m_Sprite.setRotation(m_BulletRotationDegrees);
    m_Sprite.setScale(m_SpriteScaling, m_SpriteScaling);
    m_Sprite.setColor(Color(255, 255, 255, m_SpriteAlpha));

    // // calculate gradient of flight path
    // float gradient = (startPos.x - targetPos.x) / (startPos.y - targetPos.y);
    // // make gradient positive
    // if (gradient < 0) {
    //     gradient *= -1;
    // }

    // // calculate gradient of flight path
    // float gradient = (startPos.x - targetPos.x) / (startPos.y - targetPos.y);
    // // make gradient positive
    // if (gradient < 0) {
    //     gradient *= -1;
    // }

    // // calculate XY ratio and set speed
    // float ratioXY = m_BulletSpeed / (1 + gradient);
    // m_BulletDeltaY = ratioXY;
    // m_BulletDeltaX = ratioXY * gradient;

    // // point buillet in the right direction
    // if (targetPos.x < startPos.x) m_BulletDeltaX *= -1;
    // if (targetPos.y < startPos.y) m_BulletDeltaY *= -1;

    Vector2f direction = targetPos - startPos;
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction = direction / magnitude;
    m_BulletDeltaX = m_BulletSpeed * direction.x;
    m_BulletDeltaY = m_BulletSpeed * direction.y;
}

void Bullet::stop() {
    m_InFlight = false;
}

bool Bullet::isInFlight() {
    return m_InFlight;
}

Vector2f Bullet::getPosition() {
    return m_Position;
}

FloatRect Bullet::getHitBox() {
    return m_Sprite.getGlobalBounds();
}

Sprite Bullet::getSprite() {
    return m_Sprite;
}

void Bullet::update(Time frameTime) {
    // update position
    m_Position.x += m_BulletDeltaX * frameTime.asSeconds();
    m_Position.y += m_BulletDeltaY * frameTime.asSeconds();
    m_Sprite.setPosition(m_Position);

    // remove if out of range
    if (m_Sprite.getGlobalBounds().intersects(FloatRect(m_PlayArea)) == false) {
        m_InFlight = false;
    }
}
