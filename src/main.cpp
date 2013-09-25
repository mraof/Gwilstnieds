#include "graphics.h"
#include "input.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        return 1;
    Graphics::init();
    int sprite0 = Graphics::loadImage("resources/Untitled4.png");
    int fontTexture = Graphics::loadImage("resources/Font.png");
    while(handleInput())
    {
        glClearColor(1, 1, 1, 0);
        glClear( GL_COLOR_BUFFER_BIT );
        Graphics::drawSprite(16, 16, 32, 32, sprite0);
        Graphics::drawText(0, 200, 8, 16, fontTexture, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz\n~!@#$%^&*()_+`-=[]\\{}|;':\",./<>?");
        SDL_GL_SwapBuffers();
    }
    return 0;
}
