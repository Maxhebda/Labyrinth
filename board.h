#ifndef BOARD_H
#define BOARD_H
#include <cell.h>

class Board
{
public:
    Board(int height, int width);
    void clear();
    Cell getCell(int y, int x);
    void setCell(int y, int x, Cell cell);

private:
    Cell board[100][200];   //ymax = 100, xmax = 200
    int width;
    int height;

public: //temporary is public
    void generateFrame();
};

#endif // BOARD_H
