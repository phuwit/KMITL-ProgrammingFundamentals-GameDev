#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Zombie.hpp"
#include "TextureHolder.hpp"

using namespace std;

void Zombie::spawn(Vector2f spawnLoaction, ZombieType type, int seed) {
    switch (type) {
        case ZombieType::Bloater :
            m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            break;

        case ZombieType::Chaser :
            m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            break;

        case ZombieType::Crawler :
            m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            break;
    }

    // vary speed to make each one unique
    srand((int)(time(0)) * seed);
    // somewhere between 80-100
    float modifier = (rand() % MAX_VARIANCE) + OFFSET;
    // convert to a fraction of 1; range 0.7-1
    modifier /= 100;
    m_Speed *= modifier;

    // initialize location
    m_Position = spawnLoaction;
    // set origin to center
    m_Sprite.setOrigin(25, 25);
    // set position
    m_Sprite.setPosition(m_Position);

    // make alive
    m_Alive = true;
}

bool Zombie::hit() {
    m_Health--;
    if (m_Health < 0) {
        // dead
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));

        return true;
    }
    else {
        return false;
    }
}

bool Zombie::isAlive() {
    return m_Alive;
}

FloatRect Zombie::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite() {
    return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation) {
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    // move zombie to player 
    if (playerX > m_Position.x) m_Position.x += m_Speed * elapsedTime;
    if (playerX < m_Position.x) m_Position.x -= m_Speed * elapsedTime;
    if (playerY > m_Position.y) m_Position.y += m_Speed * elapsedTime;
    if (playerY < m_Position.y) m_Position.y -= m_Speed * elapsedTime;

    // set new position
    m_Sprite.setPosition(m_Position);

    // face zombie to player
    float angle = (atan2(playerY - m_Position.y,
                        playerX - m_Position.x)
                   * 180) / M_PI;
    m_Sprite.setRotation(angle);
}
