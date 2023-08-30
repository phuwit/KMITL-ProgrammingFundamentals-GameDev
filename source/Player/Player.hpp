#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
    private:
        const IntRect m_TEXTURE_SHEET_OFFSET = IntRect(3, 13, 20, 35);
        Texture textureBase, textureArm, textureGun;
        const float m_SPRITE_SCALING = 4;
        // const Vector2f m_ARM_BASE_OFFSET = Vector2f(10.5 * m_SPRITE_SCALING, 29.5 * m_SPRITE_SCALING);
        const Vector2f m_BASE_ORIGIN_OFFSET = Vector2f(m_TEXTURE_SHEET_OFFSET.width / 2, m_TEXTURE_SHEET_OFFSET.height / 2);
        const Vector2f m_ARM_ORIGIN_OFFSET = Vector2f(4.5, 14.5);
        const Vector2f m_ARM_BASE_OFFSET = Vector2f((3.5 * m_SPRITE_SCALING), (0.5 * m_SPRITE_SCALING));
        Sprite m_Base, m_Arm, m_Gun;
        
        Vector2f m_Position;
        float m_ArmAngle;
        
        Vector2f m_ScreenResolution;
   
    public:
        Player(Vector2f screenResolution);
        Sprite getSpriteBase();
        Sprite getSpriteArm();
        Sprite getSpriteGun();
        float getArmAngle();
        // return arm's joint/origin global position 
        Vector2f getArmPosition();
        void update(Vector2i mousePosition);
};