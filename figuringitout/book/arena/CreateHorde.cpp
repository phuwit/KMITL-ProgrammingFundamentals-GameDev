#include "Arena.hpp"
#include "Zombie.hpp"

Zombie* createHorde(int numZombies, IntRect arena) {
    Zombie* zombies = new Zombie[numZombies];

    int maxY = arena.height - 20;
    int minY = arena.top + 20;
    int maxX = arena.width - 20;
    int minX = arena.left + 20;

    for (int i = 0; i < numZombies; i++) {
        // random side to spawn
        srand((int)time(0) * i);
        int side = rand() % 4;
        Vector2f spawnLocation;
        switch (side) {
            case 0:
                // left
                spawnLocation.x = minX;
                spawnLocation.y = (rand() % maxY) - minY;
                break;
            
            case 1:
                // right
                spawnLocation.x = maxX;
                spawnLocation.y = (rand() % maxY) - minY;
                break;
            
            case 2:
                // top
                spawnLocation.x = (rand() % maxX) - minX;
                spawnLocation.y = minY;
                break;
            
            case 3:
                // bottom
                spawnLocation.x = (rand() % maxX) - minX;
                spawnLocation.y = maxY;
                break;
        }

        // random types to spawn
        srand ((int)time(0) * i * 2);
        Zombie::ZombieType type = (Zombie::ZombieType)(rand() % 3);
        // spawn new zombies into array
        zombies[i].spawn(spawnLocation, type, i);
    }

    return zombies;
}