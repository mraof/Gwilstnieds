#include "map.h"
#include "graphics.h"

extern int mapTileTexture;

Map::Map(const std::string &filename)
{
    width = 10;
    height = 10;
    tileGrid = new char[width * height];
    tileGridTextures = new int[width * height];
    unitIdGrid = new int[width * height];
    for(int i = 0; i < width * height; i++)
    {
        tileGrid[i] = rand() & 1 ^ 1;
        tileGridTextures[i] = tileGrid[i] == 1 ? 4 : 0;
    }
}
Map::~Map()
{
    delete tileGrid;
    delete tileGridTextures;
    delete unitIdGrid;
}
void Map::draw()
{
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
               Graphics::drawSprite(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileGridTextures[x + y * width]);
}
