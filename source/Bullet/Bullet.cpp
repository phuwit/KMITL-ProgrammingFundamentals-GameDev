#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "../TextureHolder.hpp"
#include "Bullet.hpp"

using namespace sf;

Bullet::Bullet() {
    m_Sprite.setTexture(TextureHolder::GetTexture("assets/sprites/gun/bullet.png"));
    m_Sprite.setScale(m_SpriteScaling, m_SpriteScaling);
}

void Bullet::shoot(Vector2f startPos, Vector2f targetPos, IntRect playArea, float spriteScaling) {
    // keeping track of bullet
    m_InFlight = true;
    m_Position = startPos;
    m_SpriteScaling = spriteScaling;

    float bulletRadian = atan2(targetPos.y - startPos.y,
                         targetPos.x - startPos.x);

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

    // save playarea
    m_PlayArea = playArea;

    // set bullet position
    m_Sprite.setPosition(startPos);
    m_Sprite.setRotation((bulletRadian * 180) / M_PI);
    m_Sprite.setScale(m_SpriteScaling, m_SpriteScaling);
    m_Sprite.setColor(Color(255, 255, 255, m_SpriteAlpha));
}

void Bullet::stop() {
    m_InFlight = false;
}

bool Bullet::isInFlight() {
    return m_InFlight;
}

FloatRect Bullet::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Sprite Bullet::getShape() {
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