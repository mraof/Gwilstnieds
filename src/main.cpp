#include "graphics.h"
#include "input.h"
#include "profile.h"
#include "unit.h"

int state;
int tileTexture;

int main(int argc, char *argv[])
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        return 1;
    Graphics::init();
    int sprite0 = Graphics::loadImage("resources/sprites2.png");
    int fontTexture = Graphics::loadImage("resources/Font.png");
    tileTexture = Graphics::loadImage("resources/Tile.png");
    int offset = 0;
    Profile profile("test");
    ability punch = {"Punch", 1, true, 3, 0};
    UnitBase golem("Mud Golem", 6, 1, sprite0, punch);
    Unit unit0(golem, 2, 5);

    while(handleInput())
    {
        unit0.moveDirection(state);
        unit0.draw();
        Graphics::drawText(0, 200, 8, 16, fontTexture, unit0.abilities[0].name);
        Graphics::refresh();
    }
    return 0;
}
