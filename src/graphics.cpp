#include "graphics.h"
#include "stb_image.h"

namespace Graphics
{
    SDL_Window *sdlWindow; //window program displays in
    const float fullTexCoords[8] =
    {
        0.0d, 0.0d,
        0.0d, 1.0d,
        1.0d, 0.0d,
        1.0d, 1.0d,
    }; //coordinates for entire texturs, top/left is 0, bottom/right is 1
    const float letterWidth = 1.0 / LETTERS;
    void init()
    {
        //set up SDL with OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //set OpenGL profile
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 ); //set OpenGL version

        sdlWindow = SDL_CreateWindow("Gwilstnieds", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); //create window with support for OpenGL
        SDL_GL_CreateContext(sdlWindow); //create OpenGL context
        SDL_GL_SetSwapInterval(true); //set VSync

        //OpenGL stuff
        glMatrixMode(GL_PROJECTION); //set mode to 2D
        glLoadIdentity();
        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
        glMatrixMode (GL_MODELVIEW);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND); //enables blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //blends transparency
        glLoadIdentity();
        //Displacement trick for exact pixelization
        glTranslatef(0.375, 0.375, 0);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
    }

    //loads an image and returns the handle of the texture
    int loadImage(const std::string& filename)
    {
        GLuint texture_handle;
        int width, height, channels;
        unsigned char* ptr = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        glGenTextures(1, &texture_handle);
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA,
            width, height,
            0,
            GL_RGBA, GL_UNSIGNED_BYTE, ptr
        );
        return texture_handle;
    }

    void drawSprite(float x, float y, float width, float height, GLuint texture, bool withOffset)
    {
//        if(withOffset)
//        {
//            x = x - offsetX;
//            y = y - offsetY;
//        }
        float vertices[8] =
        {
            x, y,
            x, y + height,
            x + width, y,
            x + width, y + height,
        };


        glBindTexture(GL_TEXTURE_2D, texture);

        glTexCoordPointer(2, GL_FLOAT, 0, fullTexCoords);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void drawText(float x, float y, float width, float height, GLuint texture, const std::string& text)
    {

        glBindTexture(GL_TEXTURE_2D, texture);
        for(unsigned int i = 0; i < text.length(); i++)
        {
            if(text[i] == '\n')
            {
                x = x - (i + 1) * width;
                y = y + height;
                continue;

            }

            float letterOffset = ((text[i] - 32) % (int) LETTERS) / LETTERS;


            float vertices[8] =
            {
                x + i * width, y,
                x + i * width, y + height,
                x + i * width + width, y,
                x + i * width + width, y + height,
            };

            float letterTexCoords[8] =
            {
                letterOffset, 0.0d,
                letterOffset, 1.0d,
                letterOffset + letterWidth, 0.0d,
                letterOffset + letterWidth, 1.0d,
            };

            glBindTexture(GL_TEXTURE_2D, texture);

            glTexCoordPointer(2, GL_FLOAT, 0, letterTexCoords);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }

    void refresh()
    {
        SDL_GL_SwapWindow(sdlWindow);
        glClearColor(1, 1, 1, 0);
        glClear( GL_COLOR_BUFFER_BIT );
    }
}
