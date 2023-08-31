#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "../TextureHolder.cpp"
#include "../CommonEnum.hpp"

Player::Player() {
    textureBase = TextureHolder::GetTexture("assets/sprites/player/base/Idle2.png");
    textureArm = TextureHolder::GetTexture("assets/sprites/player/arm/8.png");
    textureGun = TextureHolder::GetTexture("assets/sprites/player/gun/1_1.png");
    m_Base.setTexture(textureBase);
    m_Base.setTextureRect(m_TEXTURE_SHEET_OFFSET);
    m_Base.setOrigin(m_BASE_ORIGIN_OFFSET);
    m_Arm.setTexture(textureArm);
    m_Arm.setOrigin(m_ARM_ORIGIN_OFFSET);
    m_Gun.setTexture(textureGun);
    m_Gun.setOrigin(m_GUN_ORIGIN_OFFSET);

    m_Base.setScale(m_SPRITE_SCALING, m_SPRITE_SCALING);
    m_Arm.setScale(m_SPRITE_SCALING, m_SPRITE_SCALING);
    m_Gun.setScale(m_SPRITE_SCALING, m_SPRITE_SCALING);
    m_MovementKeyPressed[MovementKey::DOWN] = true;
}
void Player::spawn(IntRect playArea, Vector2f screenResolution) {
    m_ScreenResolution = screenResolution;
    m_PlayArea = playArea;

    // positions organs haha yes
    m_Position = Vector2f(m_ScreenResolution.x / 2, m_ScreenResolution.y / 2);
    setSpritesPosition();
}

Sprite Player::getSpriteBase() {
    return m_Base;
}

Sprite Player::getSpriteArm() {
    return m_Arm;
}

Sprite Player::getSpriteGun() {
    return m_Gun;
}

Vector2f Player::getPosition() {
    return m_Position;
}

float Player::getArmAngle() {
    return m_ArmAngle;
}

Vector2f Player::getArmPosition() {
    return m_Arm.getPosition();
}

void Player::setMovementKeyPressed(int movementKey, bool isPressed) {
    m_MovementKeyPressed[movementKey] = isPressed;
}

void Player::update(Vector2i mousePosition, Time frameTime) {
    // movement
    if (m_MovementKeyPressed[MovementKey::LEFT])  m_Position.x -= m_Speed * frameTime.asSeconds();
    if (m_MovementKeyPressed[MovementKey::RIGHT]) m_Position.x += m_Speed * frameTime.asSeconds();
    if (m_MovementKeyPressed[MovementKey::UP])    m_Position.y -= m_Speed * frameTime.asSeconds();
    if (m_MovementKeyPressed[MovementKey::DOWN])  m_Position.y += m_Speed * frameTime.asSeconds();

    // detect wall collision
    if (m_Position.x > m_PlayArea.width)  m_Position.x = m_PlayArea.width;
    if (m_Position.x < m_PlayArea.left)   m_Position.x = m_PlayArea.left;
    if (m_Position.y > m_PlayArea.height) m_Position.y = m_PlayArea.height;
    if (m_Position.y < m_PlayArea.top)    m_Position.y = m_PlayArea.top;

    m_ArmAngle = (atan2(mousePosition.y - ((m_Arm.getPosition().y)),
                         mousePosition.x - ((m_Arm.getPosition().x) - (20)))
                   * 180 / M_PI);
    m_Arm.setRotation(m_ArmAngle);
    m_Gun.setRotation(m_ArmAngle);
    
    setSpritesPosition();
}