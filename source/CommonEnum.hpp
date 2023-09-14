#pragma once

enum MovementKey {MOVEMENT_UP, MOVEMENT_DOWN, MOVEMENT_LEFT, MOVEMENT_RIGHT};
enum MouseButton {MOUSE_LEFT, MOUSE_LRIGHT};
enum ZombieType {ZOMBIE_NORMAL, ZOMBIE_BOOMER, ZOMBIE_HUNTER};
int ZombieDifficulty[sizeof(ZombieType)] {30, 40, 40};
