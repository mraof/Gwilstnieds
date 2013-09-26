#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define LETTERS 95.0

namespace Graphics
{
    void init();
    int loadImage(const std::string& filename);
    void drawSprite(int x, int y, int width, int height, GLuint texture, bool withOffset = true);
    void drawText(int x, int y, double width, double height, GLuint texture, const std::string& text);
    void refresh();
}


#endif // GRAPHICS_H_INCLUDED
