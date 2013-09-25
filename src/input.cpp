#include "input.h"
#include <SDL/SDL.h>

SDL_Event event;

bool handleInput()
{
    while( SDL_PollEvent( &event ) )
    {
        //Handle user quit
        if( event.type == SDL_QUIT )
            return false;
    }
    return true;
}
