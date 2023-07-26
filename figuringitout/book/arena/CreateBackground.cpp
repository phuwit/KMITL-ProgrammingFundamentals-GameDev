#include "Arena.hpp"

int createBackground (VertexArray& rVA, IntRect arena) {
    // anything we did to rVA is really doing to background in the main function

    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;
    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

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
                Vector2f(w * TILE_SIZE, h * TILE_SIZE);

            rVA[currentVertex + 1].position = 
                Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);

            rVA[currentVertex + 2].position = 
                Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

            rVA[currentVertex + 3].position = 
                Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

            // define possition in the texture for current quad
            // either grass, stone, bush, or wall

            if (h == 0 || h == worldHeight - 1 ||
                w == 0 || w == worldHeight - 1) {
                    // use wall texture
                    rVA[currentVertex + 0].texCoords = 
                        Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
                    
                    rVA[currentVertex + 1].texCoords = 
                        Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);

                    rVA[currentVertex + 2].texCoords = 
                        Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
                    
                    rVA[currentVertex + 3].texCoords = 
                        Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
                }
            else {
                // use a random floor texture
                srand((int)(time(0) + h * w - h));
                // mOrG = mud or grass
                int mOrG = (rand() % TILE_TYPES);
                int verticalOffset = mOrG * TILE_SIZE;

                rVA[currentVertex + 0].texCoords = 
                        Vector2f(0, 0 + verticalOffset);
                    
                rVA[currentVertex + 1].texCoords = 
                    Vector2f(TILE_SIZE, 0 + verticalOffset);

                rVA[currentVertex + 2].texCoords = 
                    Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                
                rVA[currentVertex + 3].texCoords = 
                    Vector2f(0, TILE_SIZE + verticalOffset);
            }

            // prepare for next loop
            currentVertex += VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}