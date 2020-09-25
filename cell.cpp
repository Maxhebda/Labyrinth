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
        walls = 0;
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

uint8_t Cell::getX()
{
    return  x;
}

uint8_t Cell::getY()
{
    return y;
}

bool Cell::getWall(TypeWall typewall)
{
    return (typewall & walls) == typewall ? true : false;        //AND bit   :  if 0110 && 0010 = 0010 then true
}

void Cell::setWall(TypeWall maskTypewall)
{
    walls = walls | maskTypewall;                                   //OR bit   : = 0110 || 0001 = 0111
}

void Cell::delWall(TypeWall maskTypewall)
{
    walls = walls & !maskTypewall;                                 //ADN !bit  : = 0110 && !(0010) = 0110 && 1101 = 0100
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
        walls = 15;
    }
}
