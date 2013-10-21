#include "graphics.h"
#include "input.h"
#include "profile.h"
#include "unit.h"
#include "map.h"
#include <cstdlib>

int state;
int unitTileTexture;
int mapTileTexture;

int main(int argc, char *argv[])
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        return 1;
    Graphics::init();
    int sprite0 = Graphics::loadImage("resources/sprites2.png");
    int fontTexture = Graphics::loadImage("resources/Font.png");
    unitTileTexture = Graphics::loadImage("resources/Tile.png");
    mapTileTexture = Graphics::loadImage("resources/mapTile0.png");
    int offset = 0;
    Profile profile("test");
    ability punch = {"Punch", 1, true, 3, 0};
    UnitBase golem("Mud Golem", 6, 1, sprite0, punch);
    Map currentMap("0.map");
    Unit unit0(golem, 2, 5, &currentMap);
    while(handleInput())
    {
        unit0.moveDirection(state);
        currentMap.draw();
        unit0.draw();
        if(!(rand() & 2047))
            unit0.damage(1);
        Graphics::drawText(0, 200, 8, 16, fontTexture, unit0.abilities[0].name);
        Graphics::refresh();
    }
    return 0;
}
