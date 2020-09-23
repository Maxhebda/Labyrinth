#ifndef CEIL_H
#define CEIL_H
#include <QList>

class Ceil
{
public:
    Ceil();
    enum TypeWall{ UP = 0, RIGHT, DOWN, LEFT};
    void clear();
    bool isVisited();
    void checkVisited();
    int getX();
    int getY();
    bool getWall(TypeWall typewall);
    void setWall(TypeWall typewall);
    void delWall(TypeWall typewall);
    QList<uint8_t> getData();
    void setData(QList<uint8_t>);
    void clearData();

private:
    int y;                  //cell position
    int x;                  //cell position
    bool walls[4];          //walls / 0-up 1-right 2-down 3-left
    QList<uint8_t> data;    //other data about the cell
    bool visited;           //have already visited
};

#endif // CEIL_H
