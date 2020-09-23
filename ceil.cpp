#include "ceil.h"

Ceil::Ceil()
{
    clear();
}

void Ceil::clear()
{
    visited = false;
    for(uint8_t i = 0; i < 4 ; i++)
    {
        walls[i] = false;
    }
    clearData();
}

bool Ceil::isVisited()
{
    return visited;
}

void Ceil::checkVisited()
{
    visited = true;
}

int Ceil::getX()
{
    return  x;
}

int Ceil::getY()
{
    return y;
}

bool Ceil::getWall(TypeWall typewall)
{
    return walls[typewall];
}

void Ceil::setWall(TypeWall typewall)
{
    walls[typewall] = true;
}

void Ceil::delWall(TypeWall typewall)
{
    walls[typewall] = false;
}


QList<uint8_t> Ceil::getData()
{
    return data;
}

void Ceil::setData(QList<uint8_t> data)
{
    this->data = data;
}

void Ceil::clearData()
{
    data.clear();
}
