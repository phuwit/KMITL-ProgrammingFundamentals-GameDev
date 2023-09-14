#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Zombie.hpp"
#include "../TextureHolder.hpp"
#include "../CommonEnum.hpp"

using namespace std;

Zombie::Zombie(){}

void Zombie::spawn(Vector2f spawnLoaction, float spriteScaling, ZombieType type, int seed) {

    m_SpriteScaling = spriteScaling;

    Texture &texture = TextureHolder::GetTexture("../assets/sprites/zombies/Run.png");
    Vector2f textureSize = (Vector2f)texture.getSize();
    m_Sprite = Sprite(texture, IntRect(26 + 96, 40, 50, 56));
    m_Sprite.setScale(Vector2f(m_SpriteScaling, m_SpriteScaling));
    m_CenterOffset = Vector2f(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
    m_Speed = M_SPEED[type];
    m_Health = M_HEALTH[type];
    m_Sprite.setColor(M_COLOR[type]);

    // vary speed to make each one unique
    srand((int)(time(0)) * seed);
    // somewhere between 80-100
    float modifier = (rand() % M_MAX_VARIANCE) + M_OFFSET;
    // convert to a fraction of 1; range 0.7-1
    modifier /= 100;
    m_Speed *= modifier;

    // initialize location
    m_Position = spawnLoaction;
    // set origin to center
    m_Sprite.setOrigin(m_CenterOffset);
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
        // m_Sprite.setTexture(TextureHolder::GetTexture("die.png"));

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
    FloatRect bounds(
        m_Position.x - m_CenterOffset.x,
        m_Position.y - m_CenterOffset.y,
        m_Bounds.width,
        m_Bounds.height);
    return bounds;
}

Sprite Zombie::getSprite() {
    return m_Sprite;
}

RectangleShape Zombie::getDrawableHitbox() {
    FloatRect bounds = Zombie::getPosition();
    RectangleShape drawableHitbox(sf::Vector2f(bounds.width, bounds.height));
    drawableHitbox.setPosition(bounds.left, bounds.top);

    // Set the fill color to transparent and set an outline color and thickness
    drawableHitbox.setFillColor(sf::Color::Transparent);
    drawableHitbox.setOutlineColor(sf::Color::Red);
    drawableHitbox.setOutlineThickness(1.f);

    return drawableHitbox;
}

void Zombie::update(Time frameTime, Vector2f playerLocation) {
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    // move zombie to player 
    if (playerX > m_Position.x) m_Position.x += m_Speed * frameTime.asSeconds();
    if (playerX < m_Position.x) m_Position.x -= m_Speed * frameTime.asSeconds();
    if (playerY > m_Position.y) m_Position.y += m_Speed * frameTime.asSeconds();
    if (playerY < m_Position.y) m_Position.y -= m_Speed * frameTime.asSeconds();

    // set new position
    m_Sprite.setPosition(m_Position);

    // // face zombie to player
    // float angle = (atan2(playerY - m_Position.y,
    //                     playerX - m_Position.x)
    //                * 180) / M_PI;
    // m_Sprite.setRotation(angle);
}
