#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <string>

class Map
{
    public:
        int width, height;
        char* tileGrid;
        int* tileGridTextures;
        int* unitIdGrid;

        Map(const std::string &filename);
        ~Map();
        void draw();
};

#endif // MAP_H_INCLUDED
