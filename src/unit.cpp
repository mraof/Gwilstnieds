#include "unit.h"
#include "input.h"
#include "graphics.h"

extern int unitTileTexture;

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


Unit::Unit(UnitBase &baseUnit, int startX, int startY, Map *currentMap)
{
    name = baseUnit.name;
    maxSize = baseUnit.maxSize;
    speed = baseUnit.speed;
    texture = baseUnit.texture;
    abilities = baseUnit.abilities;
    distanceToMoveX = 0;
    distanceToMoveY = 0;
    this->currentMap = currentMap;
    moveTo(startX, startY);
}

int Unit::moveTo(int x, int y)
{
    if(x >= currentMap->width || y >= currentMap->height || x < 0 || y < 0)
        return 1;
    if(!currentMap->tileGrid[x + y * currentMap->width])
        return 1;
    centralX = x;
    centralY = y;
    bool exists = false;
    for(unsigned int i = 0; i < parts.size(); i++)
        if(parts[i].x == x && parts[i].y == y)
            parts.erase(parts.begin() + i);
    parts.push_back(Coordinate(x, y));
    if(parts.size() > maxSize)
        parts.erase(parts.begin());
    return 0;
}

void Unit::moveDirection(int direction)
{
    if(direction != 0 && distanceToMoveX == 0 && distanceToMoveY == 0)
    {
        int xChange = (direction == RIGHT) - (direction == LEFT);
        int yChange = (direction == DOWN) - (direction == UP);
        if(!moveTo(centralX + xChange, centralY + yChange))
        {
            distanceToMoveX = xChange * TILE_SIZE;
            distanceToMoveY = yChange * TILE_SIZE;
        }
    }
}
void Unit::draw()
{
    for(unsigned int i = 0; i < parts.size(); i++)
        Graphics::drawSprite(parts[i].x * TILE_SIZE, parts[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE, unitTileTexture);
    Graphics::drawSprite(centralX * TILE_SIZE - distanceToMoveX, centralY * TILE_SIZE - distanceToMoveY, UNIT_SIZE, UNIT_SIZE, texture);
    if(distanceToMoveX > 0)
        distanceToMoveX--;
    else if(distanceToMoveX < 0)
        distanceToMoveX++;
    else if(distanceToMoveY > 0)
        distanceToMoveY--;
    else if(distanceToMoveY < 0)
        distanceToMoveY++;
}
bool Unit::damage(int value)
{
    for(int i = 0; i < value && parts.size() > 0; i++)
        parts.erase(parts.begin());
    return parts.size() > 0;
}
