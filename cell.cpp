#include "cell.h"

Cell::Cell()
{
    clear();
}

void Cell::clear()
{
    visited = false;
    for(uint8_t i = 0; i < 4 ; i++)
    {
        walls[i] = false;
    }
    clearData();
}

bool Cell::isVisited()
{
    return visited;
}

void Cell::checkVisited()
{
    visited = true;
}

int Cell::getX()
{
    return  x;
}

int Cell::getY()
{
    return y;
}

bool Cell::getWall(TypeWall typewall)
{
    return walls[typewall];
}

void Cell::setWall(TypeWall typewall)
{
    walls[typewall] = true;
}

void Cell::delWall(TypeWall typewall)
{
    walls[typewall] = false;
}


QList<uint8_t> Cell::getData()
{
    return data;
}

void Cell::setData(QList<uint8_t> data)
{
    this->data = data;
}

void Cell::clearData()
{
    data.clear();
}

void Cell::checkTheLock()
{
    for(uint8_t i = 0; i < 4 ; i++)
    {
        walls[i] = true;
    }
}
