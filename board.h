#ifndef BOARD_H
#define BOARD_H
#include <cell.h>

class Board
{
public:
    Board(uint8_t height, uint8_t width);
    void clear();
    Cell getCell(uint8_t y, uint8_t x);
    void setCell(uint8_t y, uint8_t x, Cell cell);
    void dellWallinCell(uint8_t y, uint8_t x, Cell::TypeWall wall);
    void setWallinCell(uint8_t y, uint8_t x, Cell::TypeWall wall);
    void generateTheBeginningOfTheLabyrinth();
    void checkCellAsVisited(uint8_t y, uint8_t x);
    uint8_t getWidth();
    uint8_t getHeight();

    //-- maze generating functions
    void generateMaze_methodDFS(uint8_t yStart, uint8_t xStart);
    void generateMaze_methodDFS_horizontal(uint8_t yStart, uint8_t xStart);
    void generateMaze_methodDFS_vertical(uint8_t yStart, uint8_t xStart);
    void generateMaze_methodDFS_spiral(uint8_t y, uint8_t x, int8_t directory, uint8_t l, uint8_t lmax); //d = 1,2,3,4 right || -1,-2,-3,-4 left  l = step  lmax = lenght arm

private:
    Cell board[100][200];   //ymax = 100, xmax = 200
    uint8_t width;
    uint8_t height;

public: //temporary is public
    void generateFrame();
};

#endif // BOARD_H
