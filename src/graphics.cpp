#include "graphics.h"
#include "stb_image.h"
namespace Graphics
{
    void init()
    {
        //Create Window
        SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);

        //OpenGL stuff
        glMatrixMode(GL_PROJECTION); //set mode to 2D
        glLoadIdentity();
        glOrtho (0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
        glMatrixMode (GL_MODELVIEW);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLoadIdentity();
        //Displacement trick for exact pixelization
        glTranslatef(0.375, 0.375, 0);
    }

    //loads an image and returns the handle of the texture
    int loadImage(const std::string& filename)
    {
        GLuint texture_handle;
        int width, height, channels;
        unsigned char* ptr = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        glGenTextures(1, &texture_handle);
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
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

    void drawSprite(int x, int y, int width, int height, GLuint texture, bool withOffset)
    {
//        if(withOffset)
//        {
//            x = x - offsetX;
//            y = y - offsetY;
//        }
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_TRIANGLE_STRIP);
        //Top Left
        glTexCoord2d(0.0d, 0.0d);
        glVertex2f(x, y);
        //Bottom Left
        glTexCoord2d(0.0d, 1.0d);
        glVertex2f(x, y + height);
        //Top Right
        glTexCoord2d(1.0d, 0.0d);
        glVertex2f(x + width, y);
        //Bottom Right
        glTexCoord2d(1.0d, 1.0d);
        glVertex2f(x + width, y + height);
        glEnd();
    }
    void drawText(int x, int y, double width, double height, GLuint texture, const std::string& text)
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
            double letterOffset = ((text[i] - 32) % (int) LETTERS) / LETTERS;
            double letterWidth = 1.0 / LETTERS;
            glBegin(GL_QUADS);
            glTexCoord2d(letterOffset, 0);
            glVertex2d(x + i * width, y);
            glTexCoord2d(letterOffset, 1);
            glVertex2d(x + i * width, y + height);
            glTexCoord2d(letterOffset + letterWidth, 1);
            glVertex2d(x + i * width + width, y + height);
            glTexCoord2d(letterOffset + letterWidth, 0);
            glVertex2d(x + i * width + width, y);
            glEnd();
        }
    }
}
