#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <vector>
#include "map.h"

struct ability
{
    std::string name;
    int abilityID;
    bool target;
    int power;
    int sacrifice;
};


class UnitBase
{
    public:
        int maxSize; //maximum amount of space it can take up
        int speed; //max distance it can move in one turn
        int texture; //index of texture
        ability abilities[4];
        std::string name;

        UnitBase(const std::string &name, int maxSize, int speed, int texture, ability ability0, ability ability1 = ability(), ability ability2 = ability(), ability ability3 = ability());
};
struct Coordinate
{
    int x, y;
    Coordinate(int x_, int y_) : x(x_), y(y_) {};
};
class Unit
{
    public:
        int maxSize;
        int speed;
        int texture;
        int distanceToMoveX, distanceToMoveY;

        std::string name;
        ability *abilities;
        std::vector<Coordinate> parts;
        int centralX, centralY;
        Map *currentMap;

        Unit(UnitBase &baseUnit, int startX, int startY, Map *currentMap);
        int moveTo(int x, int y);
        void moveDirection(int direction);
        void draw();
        bool damage(int value);
};

#endif // UNIT_H
