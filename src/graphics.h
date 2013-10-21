#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//#include <SDL2/SDL_opengles.h>
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define LETTERS 95.0
#define UNIT_SIZE 32
#define TILE_SIZE 32

namespace Graphics
{
    void init();
    int loadImage(const std::string& filename);
    void drawSprite(float x, float y, float width, float height, GLuint texture, bool withOffset = true);
    void drawText(float x, float y, float width, float height, GLuint texture, const std::string& text);
    void refresh();
}


#endif // GRAPHICS_H_INCLUDED
