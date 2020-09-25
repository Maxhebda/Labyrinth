#ifndef Cell_H
#define Cell_H
#include <QList>

class Cell
{
public:
    Cell();
    enum TypeWall{ UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8};      //its bit : 0110 = 6 = Right + down
    void clear();
    bool isVisited();
    void checkVisited();
    uint8_t getX();
    uint8_t getY();
    bool getWall(TypeWall typewall);
    void setWall(TypeWall mask);        //set only 1 , if 1 then check 1
    void delWall(TypeWall mask);        //del only 1, if 1 then check 0
    QList<uint8_t> getData();
    void setData(QList<uint8_t>);
    void clearData();
    void checkTheLock();                          //lock object. all 4 walls. square

private:
    uint8_t y;                  //cell position
    uint8_t x;                  //cell position
    uint8_t walls;          //its bit : 0110 = 6 = Right + Down
    QList<uint8_t> data;    //other data about the cell
    bool visited;           //have already visited
};

#endif // Cell_H
