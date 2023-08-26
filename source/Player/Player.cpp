#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "../TextureHolder.cpp"

Player::Player(Vector2f screenResolution) {
    textureBase.loadFromFile("assets/sprites/player/base/Idle2.png");
    textureArm.loadFromFile("assets/sprites/player/arm/8.png");
    textureGun.loadFromFile("assets/sprites/player/gun/1_1.png");
    m_Base.setTexture(textureBase);
    m_Base.setTextureRect(m_TEXTURE_SHEET_OFFSET);
    m_Base.setOrigin(m_BASE_ORIGIN_OFFSET);
    m_Arm.setTexture(textureArm);
    m_Arm.setOrigin(m_ARM_ORIGIN_OFFSET);
    m_Gun.setTexture(textureGun);
    m_Gun.setOrigin(Vector2f(1.5, 2.5));

    m_Base.setScale(m_SPRITE_SCALING, m_SPRITE_SCALING);
    m_Arm.setScale(m_SPRITE_SCALING, m_SPRITE_SCALING);
    m_Gun.setScale(m_SPRITE_SCALING, m_SPRITE_SCALING);

    m_ScreenResolution = screenResolution;

    m_Position = Vector2f(screenResolution.x / 2, screenResolution.y / 2);
    m_Base.setPosition(m_Position);
    m_Arm.setPosition(Vector2f(m_Position.x - m_ARM_BASE_OFFSET.x, m_Position.y - m_ARM_BASE_OFFSET.y));
    m_Gun.setPosition(Vector2f(m_Position.x - m_ARM_BASE_OFFSET.x, m_Position.y - m_ARM_BASE_OFFSET.y));
    // m_Arm.setPosition(m_Position);
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

void Player::update(Vector2i mousePosition) {
    float angle = (atan2(mousePosition.y - ((m_ScreenResolution.y / 2)),
                         mousePosition.x - ((m_ScreenResolution.x / 2) - (20)))
                   * 180 / M_PI);
    m_Arm.setRotation(angle);
    m_Gun.setRotation(angle);
}