#pragma once

enum ScenesList {SCENE_MENU, SCENE_INFO, SCENE_GAME, SCENE_PAUSED, SCENE_LEVELUP, SCENE_GAMEOVER, EXIT = -1};

enum MovementKey {MOVEMENT_UP, MOVEMENT_DOWN, MOVEMENT_LEFT, MOVEMENT_RIGHT};
enum MouseButton {MOUSE_LEFT, MOUSE_LRIGHT};
enum ZombieType {ZOMBIE_NORMAL, ZOMBIE_BOOMER, ZOMBIE_HUNTER};
int ZombieDifficulty[sizeof(ZombieType)] {30, 40, 40};

int currentLevel = 1;