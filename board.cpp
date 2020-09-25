#include "board.h"
#include <QDebug>

Board::Board(uint8_t height, uint8_t width)
{
    if (width > 200)       //set default
    {
        width = 200;
    }
    if (width < 10)        //set default
    {
        width = 10;
    }
    if (height > 100)      //set default
    {
        height = 100;
    }
    if (height < 10)      //set default
    {
        height = 10;
    }
    this->height = height;
    this->width = width;
    clear();
}

void Board::clear()
{
    for (uint8_t y = 0; y < height; y++)
    {
        for (uint8_t x = 0; x < width; x++)
        {
            board[y][x].clear();
        }
    }
}

void Board::dellWallinCell(uint8_t y, uint8_t x, Cell::TypeWall wall)
{
    board[y][x].delWall(wall);
}

void Board::setWallinCell(uint8_t y, uint8_t x, Cell::TypeWall wall)
{
    board[y][x].setWall(wall);
}

Cell Board::getCell(uint8_t y, uint8_t x)
{
    if (y >= height || x >= width)
    {
        Cell lockCell;
        lockCell.checkTheLock();
        return lockCell;
    }
    return board[y][x];
}

void Board::setCell(uint8_t y, uint8_t x, Cell cell)
{
    if (y >= 0 && x >= 0 && y < this->height && x < this->width)
    {
        board[y][x] = cell;
    }
}

void Board::generateFrame()
{
    for (uint8_t x = 0; x < width; x++)
    {
        board[0][x].setWall(Cell::UP);
        board[height - 1][x].setWall(Cell::DOWN);
    }
    for (uint8_t y = 0; y < height; y++)
    {
        board[y][0].setWall(Cell::LEFT);
        board[y][width - 1].setWall(Cell::RIGHT);
    }
}

void Board::checkCellAsVisited(uint8_t y, uint8_t x)
{
    board[y][x].checkVisited();
}

void Board::generateTheBeginningOfTheLabyrinth()
{
    for (uint8_t y = 0; y < height; y++)
    {
        for (uint8_t x = 0; x < width; x++)
        {
            board[y][x].checkTheLock();
        }
    }
}

uint8_t rDirectory;
void Board::generateMaze_methodDFS(uint8_t y, uint8_t x)
{
    //-- set the cell as visited
    board[y][x].checkVisited();

    //-- random direction permutation
    uint8_t tabDirectory[4] = {0,1,2,3};
    uint8_t directionPermutation[4];
    rDirectory = rand()%4;
    directionPermutation[0] = tabDirectory[rDirectory];
    if (rDirectory!=3) tabDirectory[rDirectory] = tabDirectory[3];
    rDirectory = rand()%3;
    directionPermutation[1] = tabDirectory[rDirectory];
    if (rDirectory!=2) tabDirectory[rDirectory] = tabDirectory[2];
    rDirectory = rand()%2;
    directionPermutation[2] = tabDirectory[rDirectory];
    if (rDirectory==0) directionPermutation[3] = tabDirectory[1];
    else directionPermutation[3] = tabDirectory[0];

    //-- check/go permutation function
    for (int r = 0; r < 4; r++) {
        switch (directionPermutation[r])
        {
            case 0 :    //up
            {
                if ( y > 0 )
                {
                    if (board[y-1][x].isVisited()==false)
                    {
                        board[y][x].delWall(Cell::UP);
                        board[y-1][x].delWall(Cell::DOWN);
                        generateMaze_methodDFS(y-1,x);
                    }
                }
                break;
            }
            case 1 :    //rigth
            {
                if ( x < width - 1 )
                {
                    if (board[y][x+1].isVisited()==false)
                    {
                        board[y][x].delWall(Cell::RIGHT);
                        board[y][x+1].delWall(Cell::LEFT);
                        generateMaze_methodDFS(y,x+1);
                    }
                }
                break;
            }
            case 2 :    //down
            {
                if ( y < height - 1 )
                {
                    if (board[y+1][x].isVisited()==false)
                    {
                        board[y][x].delWall(Cell::DOWN);
                        board[y+1][x].delWall(Cell::UP);
                        generateMaze_methodDFS(y+1,x);
                    }
                }
                break;
            }
            case 3 :    //left
            {
                if ( x > 0 )
                {
                    if (board[y][x-1].isVisited()==false)
                    {
                        board[y][x].delWall(Cell::LEFT);
                        board[y][x-1].delWall(Cell::RIGHT);
                        generateMaze_methodDFS(y,x-1);
                    }
                }
                break;
            }
        }
    }
}

uint8_t Board::getWidth()
{
    return this->width;
}

uint8_t Board::getHeight()
{
    return this->height;
}
