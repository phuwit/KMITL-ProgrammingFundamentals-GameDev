#pragma once
#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../Zombie/Zombie.hpp"
#include "../Player/Player.cpp"
#include "../Bullet/Bullet.cpp"

using namespace sf;

class Game : public Scenes {
    private: 
        private:
        Clock           m_FrameTimeClock;
        const int       M_BACKGROUND_SCALE = 4;
        Vector2f        m_ScreenResolution;
        IntRect         m_BackgroundSize;
        Texture         m_TextureBackground;
        VertexArray     m_Background;
        int             m_TileSize;
        IntRect         m_PlayArea;
        float           M_SPRITE_SCALING = 4;

        View            m_GameView;
        View            m_HudView;
        
        // Player*         m_PlayerPtr = nullptr;
        // Player          m_Player = *m_PlayerPtr;
        const Time      M_LAST_HIT_COOLDOWN = milliseconds(300);
        Time            m_LastHit = seconds(0);
        const int       M_PLAYER_BASE_HEALTH = 5;
        int             m_PlayerHealth = M_PLAYER_BASE_HEALTH;

        int             m_Score = 0;
        const int       M_MAX_BULLETS = 100;
        Bullet          m_Bullets[100];
        int             m_CurrentBullet = 0;
        int             m_BulletsSpare = 24;
        const int       m_ClipSize = 6;
        int             m_BulletsInClip = m_ClipSize;
        float           m_FireRate = 1;
        Time            m_LastShot;
        const Time      M_BULLET_COOLDOWN = milliseconds(100);

        bool            m_MovementKeyPressed[sizeof(MovementKey)];
        bool            m_MouseKeyPressed[sizeof(MouseButton)];
        int             m_Stage = 0;
        int             m_NumZombies = 2 + (3 * currentLevel);
        int             m_NumZombiesAlive = m_NumZombies;
        Zombie*         m_Zombies = nullptr;

    public:
        virtual SceneChange run(RenderWindow &window);
        Game(Vector2f screenResolution, Vector2f levelSize);
        void setPaused();
        void setPerks();
};

// prototype createBackground function, with a vertexarray reference parameter and intrect parameter
int createBackground (VertexArray& rVA, IntRect playArea);

// prototype createHorde function, returns a zombie pointer
Zombie* createHorde(int numZombies, float spriteScaling, IntRect arena);