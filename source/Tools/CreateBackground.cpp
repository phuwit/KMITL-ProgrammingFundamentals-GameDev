#include "CreateBackground.hpp"

int createBackground (VertexArray& rVA, IntRect playArea, int scale) {
    // anything we did to rVA is really doing to background in the main function
    const int SCALE = scale;
    const int TILE_SIZE = 16 * SCALE;

    const int FLOOR_TILE_TYPES = 12;
    const int SPRITESHEET_FLOOR_TILE_PER_ROW = 4;
    const Vector2f FLOOR_STARTING_POS = Vector2f(96 * SCALE, 0 * SCALE);

    const int WALL_NORTH_TILE_TYPES = 4;
    const Vector2f WALL_NORTH_STARTING_POS = Vector2f(16 * SCALE, 0 * SCALE);

    const int WALL_SOUTH_TILE_TYPES = 4;
    const Vector2f WALL_SOUTH_STARTING_POS = Vector2f(16 * SCALE, 64 * SCALE);

    const int WALL_EAST_TILE_TYPES = 2;
    const Vector2f WALL_EAST_STARTING_POS = Vector2f(80 * SCALE, 0 * SCALE);
    
    const int WALL_WEST_TILE_TYPES = 2;
    const Vector2f WALL_WEST_STARTING_POS = Vector2f(0 * SCALE, 0 * SCALE);

    const Vector2f WALL_SOUTH_EAST_STARTING_POS = Vector2f(80 * SCALE, 64 * SCALE);
    const Vector2f WALL_SOUTH_WEST_STARTING_POS = Vector2f(0 * SCALE, 64 * SCALE);

    const int VERTS_IN_QUAD = 4;
    int worldWidth = playArea.width / TILE_SIZE;
    int worldHeight = playArea.height / TILE_SIZE;

    // set vertexarray primitive type
    rVA.setPrimitiveType(Quads);
    // set vertexarray size
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
    // start at the beginning of vertexarray
    int currentVertex = 0;
    for (int w = 0; w < worldWidth; w++) {
        for (int h = 0; h < worldHeight; h++) {
            // position each vertex in current quad
            rVA[currentVertex + 0].position = 
                Vector2f(w * TILE_SIZE - 1, h * TILE_SIZE - 1);

            rVA[currentVertex + 1].position = 
                Vector2f((w * TILE_SIZE) + TILE_SIZE + 1, h * TILE_SIZE - 1);

            rVA[currentVertex + 2].position = 
                Vector2f((w * TILE_SIZE) + TILE_SIZE + 1, (h * TILE_SIZE) + TILE_SIZE + 1);

            rVA[currentVertex + 3].position = 
                Vector2f(w * TILE_SIZE - 1, (h * TILE_SIZE) + TILE_SIZE + 1);

            // define possition in the texture for current quad
            // either grass, stone, bush, or wall


            srand((int)(time(0) + h * w - h));

            // south-east corner
            if (w == worldWidth - 1 && h == worldHeight - 1) {
                int xOffset = 0;
                int yOffset = 0;
                // use wall texture
                rVA[currentVertex + 0].texCoords = 
                    WALL_SOUTH_EAST_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    WALL_SOUTH_EAST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    WALL_SOUTH_EAST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    WALL_SOUTH_EAST_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }
            // south-west corner
            else if (w == 0 && h == worldHeight - 1) {
                int xOffset = 0;
                int yOffset = 0;
                // use wall texture
                rVA[currentVertex + 0].texCoords = 
                    WALL_SOUTH_WEST_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    WALL_SOUTH_WEST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    WALL_SOUTH_WEST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    WALL_SOUTH_WEST_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }
            // west wall
            else if (w == 0) {
                // alternate wall texture
                int randomTileIndex = (h % WALL_WEST_TILE_TYPES);
                int xOffset = 0;
                int yOffset = randomTileIndex * TILE_SIZE;
                // use wall texture
                rVA[currentVertex + 0].texCoords = 
                    WALL_WEST_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    WALL_WEST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    WALL_WEST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    WALL_WEST_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }
            // east wall
            else if (w == worldWidth - 1) {
                // alternate wall texture
                int randomTileIndex = (h % WALL_EAST_TILE_TYPES);
                int xOffset = 0;
                int yOffset = randomTileIndex * TILE_SIZE;
                // use wall texture
                rVA[currentVertex + 0].texCoords = 
                    WALL_EAST_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    WALL_EAST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    WALL_EAST_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    WALL_EAST_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }
            // north wall
            else if (h == 0) {
                // use a random wall texture
                int randomTileIndex = (rand() % WALL_NORTH_TILE_TYPES);
                int xOffset = (randomTileIndex % SPRITESHEET_FLOOR_TILE_PER_ROW) * TILE_SIZE;
                int yOffset = (randomTileIndex / SPRITESHEET_FLOOR_TILE_PER_ROW) * TILE_SIZE;
                // use wall texture
                rVA[currentVertex + 0].texCoords = 
                    WALL_NORTH_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    WALL_NORTH_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    WALL_NORTH_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    WALL_NORTH_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }
            // south wall
            else if (h == worldHeight - 1) {
                // use a random wall texture
                int randomTileIndex = (rand() % WALL_SOUTH_TILE_TYPES);
                int xOffset = (randomTileIndex % SPRITESHEET_FLOOR_TILE_PER_ROW) * TILE_SIZE;
                int yOffset = (randomTileIndex / SPRITESHEET_FLOOR_TILE_PER_ROW) * TILE_SIZE;
                // use wall texture
                rVA[currentVertex + 0].texCoords = 
                    WALL_SOUTH_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    WALL_SOUTH_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    WALL_SOUTH_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    WALL_SOUTH_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }
            
            else {
                // use a random floor texture
                int randomTileIndex = (rand() % FLOOR_TILE_TYPES);
                int xOffset = (randomTileIndex % SPRITESHEET_FLOOR_TILE_PER_ROW) * TILE_SIZE;
                int yOffset = (randomTileIndex / SPRITESHEET_FLOOR_TILE_PER_ROW) * TILE_SIZE;

                rVA[currentVertex + 0].texCoords = 
                    FLOOR_STARTING_POS +
                    Vector2f(xOffset, yOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    FLOOR_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, yOffset);

                rVA[currentVertex + 2].texCoords = 
                    FLOOR_STARTING_POS +
                    Vector2f(TILE_SIZE + xOffset, TILE_SIZE + yOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    FLOOR_STARTING_POS +
                    Vector2f(xOffset, TILE_SIZE + yOffset);
            }

            // prepare for next loop
            currentVertex += VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}