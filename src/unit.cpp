#include "unit.h"
#include "input.h"
#include "graphics.h"

extern int tileTexture;

UnitBase::UnitBase(const std::string &name, int maxSize, int speed, int texture, ability ability0, ability ability1, ability ability2, ability ability3)
{
    this->name = name;
    this->maxSize = maxSize;
    this->speed = speed;
    this->texture = texture;

    abilities[0] = ability0;
    abilities[1] = ability1;
    abilities[2] = ability2;
    abilities[3] = ability3;
}


Unit::Unit(UnitBase &baseUnit, int startX, int startY)
{
    name = baseUnit.name;
    maxSize = baseUnit.maxSize;
    speed = baseUnit.speed;
    texture = baseUnit.texture;
    abilities = baseUnit.abilities;
    distanceToMoveX = 0;
    distanceToMoveY = 0;
    moveTo(startX, startY);
}

int Unit::moveTo(int x, int y)
{
    centralX = x;
    centralY = y;
    bool exists = false;
    for(unsigned int i = 0; i < parts.size(); i++)
        if(parts[i].x == x && parts[i].y == y)
            parts.erase(parts.begin() + i);
        parts.push_back(Coordinate(x, y));
        if(parts.size() > maxSize)
            parts.erase(parts.begin()); //this needs to be improved so it only removes adjacent parts
    return 0;
}

void Unit::moveDirection(int direction)
{
    if(direction != 0 && distanceToMoveX == 0 && distanceToMoveY == 0)
    {
        int xChange = (direction == RIGHT) - (direction == LEFT);
        int yChange = (direction == DOWN) - (direction == UP);
        moveTo(centralX + xChange, centralY + yChange);
        distanceToMoveX = xChange * 32;
        distanceToMoveY = yChange * 32;
    }
}
void Unit::draw()
{
    for(unsigned int i = 0; i < parts.size(); i++)
        Graphics::drawSprite(parts[i].x * 32, parts[i].y * 32, 32, 32, tileTexture);
    Graphics::drawSprite(centralX * 32 - distanceToMoveX, centralY * 32 - distanceToMoveY, 32, 32, texture);
    if(distanceToMoveX > 0)
        distanceToMoveX--;
    else if(distanceToMoveX < 0)
        distanceToMoveX++;
    else if(distanceToMoveY > 0)
        distanceToMoveY--;
    else if(distanceToMoveY < 0)
        distanceToMoveY++;
}
