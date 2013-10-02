#include "input.h"
#include <SDL2/SDL.h>


SDL_Event event;
extern int state;

bool handleInput()
{
    state = 0;
    while( SDL_PollEvent( &event ) )
    {
        //Handle user quit
        if( event.type == SDL_QUIT )
            return false;
        if( event.type = SDL_KEYDOWN)
            switch(event.key.keysym.scancode)
            {
            case SDL_SCANCODE_LEFT:
                state = LEFT;
                break;
            case SDL_SCANCODE_RIGHT:
                state = RIGHT;
                break;
            case SDL_SCANCODE_UP:
                state = UP;
                break;
            case SDL_SCANCODE_DOWN:
                state = DOWN;
                break;
            default:
                break;
            }
    }
    return true;
}
