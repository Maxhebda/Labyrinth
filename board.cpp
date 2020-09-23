#include "board.h"

Board::Board(int height, int width)
{
    if (height > 100 || width > 200 || height < 10 || width < 10)       //set default
    {
        height = 20;
        width = 20;
    }
    this->height = height;
    this->width = width;
    clear();
}

void Board::clear()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            board[y][x].clear();
        }
    }
}

Cell Board::getCell(int y, int x)
{
    if (y < 0 || x < 0 || y >= height || x >= width)
    {
        Cell lockCell;
        lockCell.checkTheLock();
        return lockCell;
    }
    return board[y][x];
}

void Board::setCell(int y, int x, Cell cell)
{
    if (y >= 0 && x >= 0 && y < height && x < width)
    {
        board[y][x] = cell;
    }
}

void Board::generateFrame()
{
    Cell * tmpCell1 = new Cell();
    Cell * tmpCell2 = new Cell();
    tmpCell1->setWall(Cell::UP);
    tmpCell2->setWall(Cell::DOWN);
    for (int x = 0; x < width; x++)
    {
        board[0][x] = *tmpCell1;
        board[height - 1][x] = *tmpCell2;
    }

    tmpCell1->delWall(Cell::UP);
    tmpCell2->delWall(Cell::DOWN);
    tmpCell1->setWall(Cell::LEFT);
    tmpCell2->setWall(Cell::RIGHT);
    for (int y = 0; y < height; y++)
    {
        board[y][0] = *tmpCell1;
        board[y][width - 1] = *tmpCell2;
    }

    delete tmpCell1;
    delete tmpCell2;
}
