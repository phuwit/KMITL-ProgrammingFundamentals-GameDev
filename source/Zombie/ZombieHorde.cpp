#include "../CommonEnum.hpp"
#include "../BrainBlast.hpp"
#include "Zombie.hpp"

Zombie* createHorde(int numZombies, float spriteScaling, IntRect playArea) {
    Zombie* zombies = new Zombie[numZombies];

    const int WALL_PADDING = 20;

    int maxY = playArea.height - (WALL_PADDING * 2);
    int minY = playArea.top + WALL_PADDING;
    int maxX = playArea.width - (WALL_PADDING * 2);
    int minX = playArea.left + WALL_PADDING;

    for (int i = 0; i < numZombies; i++) {
        // random side to spawn
        srand((int)time(0) * i);
        int side = rand() % 4;
        Vector2f spawnLocation;
        switch (side) {
            case 0:
                // left
                spawnLocation.x = minX;
                spawnLocation.y = (rand() % maxY) + minY;
                break;
            
            case 1:
                // right
                spawnLocation.x = maxX;
                spawnLocation.y = (rand() % maxY) + minY;
                break;
            
            case 2:
                // top
                spawnLocation.x = (rand() % maxX) + minX;
                spawnLocation.y = minY;
                break;
            
            case 3:
                // bottom
                spawnLocation.x = (rand() % maxX) + minX;
                spawnLocation.y = maxY;
                break;
        }

        // random types to spawn
        srand ((int)time(0) * i * 2);
        ZombieType type = (ZombieType)(rand() % (sizeof(ZombieType) - 1));
        // spawn new zombies into array
        zombies[i].spawn(spawnLocation, spriteScaling, type, i);
    }

    return zombies;
}