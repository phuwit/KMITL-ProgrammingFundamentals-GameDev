#include <SFML/Graphics.hpp>

#include "Bullet.hpp"

using namespace sf;

Bullet::Bullet() {
    m_BulletShape.setSize(Vector2f(2, 2));
}

void Bullet::shoot(Vector2f startPos, Vector2f targetPos) {
    // keeping track of bullet
    m_InFlight = true;
    m_Position = startPos;
    // calculate gradient of flight path
    float gradient = (startPos.x - targetPos.x) / (startPos.y - targetPos.y);
    // make gradient positive
    if (gradient < 0) {
        gradient *= -1;
    }

    // calculate XY ratio and set speed
    float ratioXY = m_BulletSpeed / (1 + gradient);
    m_BulletDeltaY = ratioXY;
    m_BulletDeltaX = ratioXY * gradient;

    // point buillet in the right direction
    if (targetPos.x < startPos.x) m_BulletDeltaX *= -1;
    if (targetPos.y < startPos.y) m_BulletDeltaY *= -1;

    // set max range
    m_MinX = startPos.x - m_MAX_RANGE;
    m_MaxX = startPos.x + m_MAX_RANGE;
    m_MinY = startPos.y - m_MAX_RANGE;
    m_MaxY = startPos.y + m_MAX_RANGE;

    // set bullet position
    m_BulletShape.setPosition(startPos);
}

void Bullet::stop() {
    m_InFlight = false;
}

bool Bullet::isInFlight() {
    return m_InFlight;
}

FloatRect Bullet::getPosition() {
    return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape() {
    return m_BulletShape;
}

void Bullet::update(float elapsedTime) {
    // update position
    m_Position.x += m_BulletDeltaX * elapsedTime;
    m_Position.y += m_BulletDeltaY * elapsedTime;
    m_BulletShape.setPosition(m_Position);

    // remove if out of range
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX || 
        m_Position.y < m_MinY || m_Position.y > m_MaxY) {
            m_InFlight = false;
        }
}
