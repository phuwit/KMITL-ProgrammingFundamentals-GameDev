#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
    private:
        const IntRect m_TEXTURE_SHEET_OFFSET = IntRect(3, 13, 20, 35);
        // Texture textureBase, textureArm, textureGun;
        float m_SpriteScaling = 1;
        // const Vector2f m_ARM_BASE_OFFSET = Vector2f(10.5 * m_SpriteScaling, 29.5 * m_SpriteScaling);
        const Vector2f m_BASE_ORIGIN_OFFSET = Vector2f(m_TEXTURE_SHEET_OFFSET.width / 2, m_TEXTURE_SHEET_OFFSET.height / 2);
        const Vector2f m_ARM_ORIGIN_OFFSET = Vector2f(4.5, 14.5);
        const Vector2f m_GUN_ORIGIN_OFFSET = Vector2f(1.5, 2.5);
        const Vector2f m_ARM_BASE_OFFSET = Vector2f((3.5 * m_SpriteScaling), (0.5 * m_SpriteScaling));
        Sprite m_Base, m_Arm, m_Gun;

        float m_BaseSpeed = 250;
        float m_Speed = m_BaseSpeed;
        float m_SpeedDiagonal = m_Speed * sqrt(0.5);
        
        bool m_MovementKeyPressed[4] = {false};
        Vector2f m_Position;
        void m_SetSpritesPosition();
        float m_ArmAngle;
        bool m_Flipped = false;
        void m_Flip();
        void m_UnFlip();
        
        Vector2f m_ScreenResolution;
        FloatRect m_PlayArea;
   
    public:
        Player(float spriteScaling);
        void spawn(FloatRect playArea, Vector2f screenResolution);

        Sprite getSpriteBase();
        Sprite getSpriteArm();
        Sprite getSpriteGun();
        Vector2f getPosition();
        FloatRect getHitbox();
        float getArmAngle();
        // return arm's joint/origin global position 
        Vector2f getArmPosition();
        Vector2f getBarrelPosition();

        void setSpeedWithMultiplier(float multiplier);
        void setSpeedReset();

        void setMovementKeyPressed(int movementKey, bool isPressed);

        void update(Vector2f mousePosition, Time deltaTime);
};