#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.cpp"

Player::Player(float spriteScaling) {
    m_SpriteScaling = spriteScaling;
    m_Base.setTexture(TextureHolder::GetTexture("assets/sprites/player/base/Idle2.png"));
    m_Base.setTextureRect(m_TEXTURE_SHEET_OFFSET);
    m_Base.setOrigin(m_BASE_ORIGIN_OFFSET);
    m_Arm.setTexture(TextureHolder::GetTexture("assets/sprites/player/arm/8.png"));
    m_Arm.setOrigin(m_ARM_ORIGIN_OFFSET);
    m_Gun.setTexture(TextureHolder::GetTexture("assets/sprites/gun/gun.png"));
    m_Gun.setOrigin(m_GUN_ORIGIN_OFFSET);

    m_Base.setScale(m_SpriteScaling, m_SpriteScaling);
    m_Arm.setScale(m_SpriteScaling, m_SpriteScaling);
    m_Gun.setScale(m_SpriteScaling, m_SpriteScaling);
    m_MovementKeyPressed[MovementKey::MOVEMENT_DOWN] = true;

    m_ArmAngle = 0;
}

void Player::spawn(FloatRect playArea, Vector2f screenResolution) {
    m_ScreenResolution = screenResolution;
    m_PlayArea = playArea;
    float paddingWidth = (m_Base.getLocalBounds().width) / 2;
    float paddingHeight = (m_Base.getLocalBounds().height) / 2;
    m_PlayArea = FloatRect(playArea.left + paddingWidth, playArea.top + paddingHeight, playArea.width - paddingWidth, playArea.height - paddingHeight);

    // positions organs haha yes
    m_Position = Vector2f((playArea.width + playArea.left) / 2, (playArea.height + playArea.top) / 2);
    m_SetSpritesPosition();
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

FloatRect Player::getHitbox() {
    return m_Base.getGlobalBounds();
}

float Player::getArmAngle() const {
    return m_ArmAngle;
}

Vector2f Player::getArmPosition() {
    return m_Arm.getPosition();
}

Vector2f Player::getBarrelPosition() {
    return (m_Arm.getPosition() + 
            Vector2f(23 * m_SpriteScaling * cos(m_ArmAngle * (M_PI / 180)), 
                     23 * m_SpriteScaling * sin(m_ArmAngle * (M_PI / 180)))
           );
}

void Player::setMovementKeyPressed(int movementKey, bool isPressed) {
    m_MovementKeyPressed[movementKey] = isPressed;
}

void Player::setSpeedWithMultiplier(float multiplier) {
    m_Speed = m_BaseSpeed * multiplier;
    m_SpeedDiagonal = m_Speed * sqrt(0.5);
}

void Player::setSpeedReset() {
    m_Speed = m_BaseSpeed;
    m_SpeedDiagonal = m_Speed * sqrt(0.5);
}

void Player::update(Vector2f mousePosition, Time frameTime) {
    // movement
    // detect diagonals
    m_MovementButtonPressed = 0;
    for (unsigned int i = 0; i < (unsigned int)(sizeof(MovementKey)); i++) {
        if (m_MovementKeyPressed[i] == true) {
            m_MovementButtonPressed++;
        }
    }

    // actually move
    if (m_MovementButtonPressed == 1) {
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_LEFT])  m_Position.x -= m_Speed * frameTime.asSeconds();
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_RIGHT]) m_Position.x += m_Speed * frameTime.asSeconds();
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_UP])    m_Position.y -= m_Speed * frameTime.asSeconds();
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_DOWN])  m_Position.y += m_Speed * frameTime.asSeconds();
    }
    else if (m_MovementButtonPressed > 1) {
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_LEFT])  m_Position.x -= m_SpeedDiagonal * frameTime.asSeconds();
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_RIGHT]) m_Position.x += m_SpeedDiagonal * frameTime.asSeconds();
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_UP])    m_Position.y -= m_SpeedDiagonal * frameTime.asSeconds();
        if (m_MovementKeyPressed[MovementKey::MOVEMENT_DOWN])  m_Position.y += m_SpeedDiagonal * frameTime.asSeconds();
    }

    // detect wall collision
    if (m_Position.x > m_PlayArea.width)  m_Position.x = m_PlayArea.width;
    if (m_Position.x < m_PlayArea.left)   m_Position.x = m_PlayArea.left;
    if (m_Position.y > m_PlayArea.height) m_Position.y = m_PlayArea.height;
    if (m_Position.y < m_PlayArea.top)    m_Position.y = m_PlayArea.top;

    m_ArmAngle = (atan2(mousePosition.y - (m_Arm.getPosition().y),
                        mousePosition.x - (m_Arm.getPosition().x))
                   * 180 / M_PI);
    m_Arm.setRotation(m_ArmAngle);
    m_Gun.setRotation(m_ArmAngle);

    if (m_ArmAngle > -90 && m_ArmAngle < 90) {
        m_UnFlip();
    }
    else {
        m_Flip();
    }
    
    m_SetSpritesPosition();
}

void Player::animate() {
    if (m_MovementButtonPressed > 0) {
        m_Base.setTexture(TextureHolder::GetTexture("assets/sprites/player/base/Run2.png"));
    } else {
        m_Base.setTexture(TextureHolder::GetTexture("assets/sprites/player/base/Idle2.png"));
    }
    IntRect newCrop = IntRect(m_Base.getTextureRect().left + SPRITE_SIZE, m_TEXTURE_SHEET_OFFSET.top, m_TEXTURE_SHEET_OFFSET.width, m_TEXTURE_SHEET_OFFSET.height);
    if ((unsigned int)newCrop.left > m_Base.getTexture()->getSize().x) {
        newCrop.left = m_TEXTURE_SHEET_OFFSET.left;
    }
    m_Base.setTextureRect(newCrop);
}

void Player::m_SetSpritesPosition() {
    m_Base.setPosition(m_Position);
    m_Arm.setPosition(Vector2f(m_Position.x - m_ARM_BASE_OFFSET.x, m_Position.y - m_ARM_BASE_OFFSET.y));
    m_Gun.setPosition(Vector2f(m_Position.x - m_ARM_BASE_OFFSET.x, m_Position.y - m_ARM_BASE_OFFSET.y));
}

void Player::m_Flip() {
    m_Base.setScale(-m_SpriteScaling, m_SpriteScaling);
    m_Arm.setScale(m_SpriteScaling, -m_SpriteScaling);
    m_Gun.setScale(m_SpriteScaling, -m_SpriteScaling);
}

void Player::m_UnFlip() {
    m_Base.setScale(m_SpriteScaling, m_SpriteScaling);
    m_Arm.setScale(m_SpriteScaling, m_SpriteScaling);
    m_Gun.setScale(m_SpriteScaling, m_SpriteScaling);
}