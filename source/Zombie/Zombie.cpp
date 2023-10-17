#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Zombie.hpp"
#include "../CommonEnum.hpp"
#include "../Holders/TextureHolder.hpp"
#include "../Tools/SetOriginCenter.cpp"

using namespace std;

Zombie::Zombie(){}

void Zombie::spawn(Vector2f spawnLoaction, float spriteScaling, ZombieType type, ZombieMoveStyle moveStyle, int seed, FloatRect playArea) {
    m_Type = type;
    m_SpriteScaling = spriteScaling;

    Texture &texture = TextureHolder::GetTexture(M_SPRITE_RUN_FILENAME[m_Type]);
//    Vector2f textureSize = (Vector2f)texture.getSize();
    m_Sprite = Sprite(texture, M_SPRITE_RUN_CROP[m_Type]);
    m_Sprite.setScale(Vector2f(m_SpriteScaling, m_SpriteScaling));
//    m_CenterOffset = Vector2f((m_Sprite.getLocalBounds().width * m_SpriteScaling) / 2, ((m_Sprite.getLocalBounds().height * m_SpriteScaling) / 2));
    m_Health = M_HEALTH_BASE[m_Type];
    m_Sprite.setColor(M_COLOR_BASE[m_Type]);

    // vary speed to make each one unique
    srand((int)(time(0)) * seed);
    // somewhere between 80-100
    float modifierX = (rand() % M_MAX_VARIANCE) + M_OFFSET;
    float modifierY = (rand() % M_MAX_VARIANCE) + M_OFFSET;
    // convert to a fraction of 1; range 0.7-1
    modifierX /= 100;
    modifierY /= 100;
    m_Speed = Vector2f(M_SPEED_BASE[m_Type] * modifierX, M_SPEED_BASE[m_Type] * modifierY);

    // initialize locatio
    m_Position = spawnLoaction;
    m_PlayArea = playArea;
    m_MoveStyle = moveStyle;
    // set origin to center
//    m_Sprite.setOrigin(m_CenterOffset);
    spriteSetOriginCenter(m_Sprite);
    // set position
    m_Sprite.setPosition(m_Position);
    // set bounds size
    m_Bounds = m_Sprite.getLocalBounds();

    // make alive
    m_Alive = true;
}

bool Zombie::hit() {
    m_Health--;
    if (m_Health < 0) {
        // dead
        m_Alive = false;
        m_Sprite.setOrigin(Vector2f(m_Sprite.getLocalBounds().width / 2, -m_Sprite.getLocalBounds().height / 2));
        m_Sprite.setTexture(TextureHolder::GetTexture(M_SPRITE_DEATH_FILENAME[m_Type]));
        m_Sprite.setTextureRect(M_SPRITE_DEATH_CROP[m_Type]);
        return true;
    }
    else {
        return false;
    }
}

bool Zombie::isAlive() {
    return m_Alive;
}

FloatRect Zombie::getHitBox() {
//    FloatRect bounds(
//        m_Position.x - (m_CenterOffset.x * m_SpriteScaling),
//        m_Position.y - (m_CenterOffset.y * m_SpriteScaling),
//        m_Bounds.width * m_SpriteScaling,
//        m_Bounds.height * m_SpriteScaling);
//    return bounds;
    return m_Sprite.getGlobalBounds();
}

RectangleShape Zombie::getDrawableHitbox() {
    FloatRect bounds = Zombie::getHitBox();
    RectangleShape drawableHitbox(sf::Vector2f(bounds.width, bounds.height));
    drawableHitbox.setPosition(bounds.left, bounds.top);

    // Set the fill color to transparent and set an outline color and thickness
    drawableHitbox.setFillColor(sf::Color::Transparent);
    drawableHitbox.setOutlineColor(sf::Color::Red);
    drawableHitbox.setOutlineThickness(1.f);

    return drawableHitbox;
}

Sprite Zombie::getSprite() {
    return m_Sprite;
}

Vector2f Zombie::getPosition() {
    return m_Position;
}

Time Zombie::getTimeSinceSpawned() {
    return m_TimeSinceSpawn;
}

void Zombie::update(Time frameTime, Vector2f playerLocation) {
    if(m_Alive){
        m_TimeSinceSpawn += frameTime;

        float distanceX = (playerLocation.x - m_Position.x);
        float distanceY = (playerLocation.y - m_Position.y);

        bool moveX, moveY;

        Vector2f speed = m_Speed;

        Vector2i inverseChance = M_BASE_INVERSE_CHANCE;

        if (m_SpeedInverse.x == -1) {
            inverseChance.x /= 2;
        }
        if (m_SpeedInverse.y == -1) {
            inverseChance.y /= 2;
        }

        if ((rand() % inverseChance.x) == 0) m_SpeedInverse.x = -m_SpeedInverse.x;
        if ((rand() % inverseChance.y) == 0) m_SpeedInverse.y = -m_SpeedInverse.y;

        if (!m_PlayArea.contains(m_Position)) {
            if (m_Position.x < m_PlayArea.left)   m_SpeedInverse.x = 1;
            if (m_Position.x > m_PlayArea.width)  m_SpeedInverse.x = 1;
            if (m_Position.y < m_PlayArea.top)    m_SpeedInverse.y = 1;
            if (m_Position.y > m_PlayArea.height) m_SpeedInverse.y = 1;
        }

        if (distanceX != 0) {
            moveX = true;
        }
        if (distanceY != 0) {
            moveY = true;
        }

        if (distanceX < 0) {
            m_Sprite.setScale(Vector2f(-m_SpriteScaling, m_SpriteScaling));
        }
        else {
            m_Sprite.setScale(Vector2f(m_SpriteScaling, m_SpriteScaling));
        }


        if (m_MoveStyle == ZombieMoveStyle::ZOMBIE_MOVESTYLE_XFIRST) {
            if (abs(distanceX) >= 50) {
                moveX = true;
                moveY = false;
            }
        }
        else if (m_MoveStyle == ZombieMoveStyle::ZOMBIE_MOVESTYLE_YFIRST) {
            if (abs(distanceY) >= 50) {
                moveX = false;
                moveY = true;
            }
        }
        else if (m_MoveStyle == ZombieMoveStyle::ZOMBIE_MOVESTYLE_RANDOM) {
            moveX = (rand() % 2) == 0;
            moveY = (rand() % 2) == 0;
        }

        // check for moving in diagonal
        if (moveX && moveY) {
            speed = Vector2f(m_Speed.x * sqrt(0.5), m_Speed.y * sqrt(0.5));
        }


        if (moveX == true) {
            if (distanceX > 0) m_Position.x += (speed.x * m_SpeedInverse.x) * frameTime.asSeconds();
            if (distanceX < 0) m_Position.x -= (speed.x * m_SpeedInverse.x) * frameTime.asSeconds();
        }
        if (moveY == true) {
            if (distanceY > 0) m_Position.y += (speed.y * m_SpeedInverse.y) * frameTime.asSeconds();
            if (distanceY < 0) m_Position.y -= (speed.y * m_SpeedInverse.y) * frameTime.asSeconds();
        }

        // flip zombie if facing in -x direction
        // set new position
        m_Sprite.setPosition(m_Position);

        // // face zombie to player
        // float angle = (atan2(playerY - m_Position.y,
        //                     playerX - m_Position.x)
        //                * 180) / M_PI;
        // m_Sprite.setRotation(angle);
    }
}

//void Player::animate() {
//    if (m_MovementButtonPressed > 0) {
//        m_Base.setTexture(TextureHolder::GetTexture("assets/sprites/player/base/Run2.png"));
//    } else {
//        m_Base.setTexture(TextureHolder::GetTexture("assets/sprites/player/base/Idle2.png"));
//    }
//    IntRect newCrop = IntRect(m_Base.getTextureRect().left + SPRITE_SIZE, m_TEXTURE_SHEET_OFFSET.top, m_TEXTURE_SHEET_OFFSET.width, m_TEXTURE_SHEET_OFFSET.height);
//    if ((unsigned int)newCrop.left > m_Base.getTexture()->getSize().x) {
//        newCrop.left = m_TEXTURE_SHEET_OFFSET.left;
//    }
//    m_Base.setTextureRect(newCrop);
//}

void Zombie::animate() {
    if (m_Alive) {
        IntRect newCrop = IntRect(m_Sprite.getTextureRect().left + 96, m_Sprite.getTextureRect().top,
                                  m_Sprite.getTextureRect().width, m_Sprite.getTextureRect().height);
        if ((unsigned int) newCrop.left >= m_Sprite.getTexture()->getSize().x) {
            newCrop.left = 0;
        }
        m_Sprite.setTextureRect(newCrop);
    }
}
