#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "Scenes.hpp"
#include "../Zombie/Zombie.hpp"
#include "../Player/Player.cpp"
#include "../Bullet/Bullet.cpp"
#include "../PickUps/PickUps.cpp"

using namespace sf;

class Game : public Scenes {
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

        Font            m_FontBebas;
        const float     m_HudBackgroundPadding = 10;
        RectangleShape  m_HudBackground;
        RectangleShape  m_HealthBar;
        float           m_HealthBarSegmentSize;
        Text            m_HealthLabel;
        Text            m_ScoreText;
        Text            m_AmmoLabel;
        Text            m_CurrentAmmoText;
        Text            m_SpareAmmoText;
        Text            m_WaveText;

        Sound           m_SoundLoaded;
        Sound           m_SoundHit;
        Sound           m_SoundKilled;
        Sound           m_SoundShoot;
        Sound           m_SoundReload;
        Sound           m_SoundPickupLow;
        Sound           m_SoundPickupHigh;

        Player          m_Player = Player(M_SPRITE_SCALING);
        const Time      M_LAST_HIT_COOLDOWN = milliseconds(300);
        Time            m_LastHit = seconds(0);
        const int       M_PLAYER_BASE_HEALTH = 5;
        int             m_PlayerMaxHealth = M_PLAYER_BASE_HEALTH;
        int             m_PlayerHealth = M_PLAYER_BASE_HEALTH;

        unsigned int    m_Score = 0;
        int             m_ScoreMultiplier = 1;
        const int       M_MAX_BULLETS = 100;
        Bullet          m_Bullets[100];
        int             m_CurrentBulletIndex = 0;
        int             m_SpareAmmo = 24;
        int             m_ClipSize = 6;
        int             m_BulletsInClip;
//        float           m_FireRate = 1;
        Time            m_LastShot;
        const Time      m_BASE_BULLET_COOLDOWN = milliseconds(300);
        Time            m_BulletCooldown = m_BASE_BULLET_COOLDOWN;

        vector<PickUps> m_PickUpsList;
        Sprite          m_PickupsSprite;
        PickupsType     m_BuffType;
        Time            m_BuffTimer = seconds(0);
        Sprite          m_BuffSprite;
        CircleShape     m_BuffVisualizerOutline;
        RectangleShape  m_BuffVisualizerWiper;
        float           m_BuffVisualizerAnglePerSecond;

        bool            m_MovementKeyPressed[sizeof(MovementKey)];
        bool            m_MouseKeyPressed[sizeof(MouseButton)];
//        int             m_Stage = 0;
        int             m_NumZombies;
        int             m_NumZombiesAlive;
        Zombie*         m_Zombies = nullptr;

        void handlePickUps_(PickupsType pickUpsType, int pickupValue, Time buffDuration);
        void removeBuff_(PickupsType pickUpsType);
    public:
        SceneChange run(RenderWindow &window) override;
        Game(Vector2f screenResolution, Vector2f levelSize);
        void regenerate();
        void setPaused();
        void setPerks(int perks);
        unsigned int getScore();
};

// prototype createBackground function, with a vertex array reference parameter and intrect parameter
int createBackground (VertexArray& rVA, IntRect playArea);

// prototype createHorde function, returns a zombie pointer
Zombie* createHorde(int numZombies, float spriteScaling, IntRect arena);
