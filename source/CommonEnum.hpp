#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

enum OS {OS_WINDOWS, OS_LINUX, OS_MAC, OS_OTHER};

enum ScenesList {SCENE_MENU, SCENE_INFO, SCENE_GAME, SCENE_PAUSED, SCENE_LEVELUP, SCENE_GAMEOVER, EXIT = -1};

Color COLOR_BACKGROUND = Color(37, 19, 26);
enum MovementKey {MOVEMENT_UP, MOVEMENT_DOWN, MOVEMENT_LEFT, MOVEMENT_RIGHT};
enum MouseButton {MOUSE_LEFT, MOUSE_LRIGHT};
enum ZombieType {ZOMBIE_NORMAL, ZOMBIE_BOOMER, ZOMBIE_HUNTER};
enum ZombieMoveStyle {ZOMBIE_MOVESTYLE_LINEAR, ZOMBIE_MOVESTYLE_XFIRST, ZOMBIE_MOVESTYLE_YFIRST};
enum PickupsType {PICKUPS_HEALTH, PICKUPS_AMMO, PICKUPS_SPEED, PICKUPS_SCORE};
int ZombieDifficulty[sizeof(ZombieType)] {30, 40, 40};

int currentLevel = 1;
bool paused = false;
