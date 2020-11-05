#include "board.h"
#include <QDebug>

uint8_t rDirectory;

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

void Board::generateMaze_methodDFS_horizontal(uint8_t y, uint8_t x)
{
    //-- set the cell as visited
    board[y][x].checkVisited();

    //-- random direction permutation
    uint8_t tabDirectory[4] = {0,1,2,3};
    uint8_t directionPermutation[4];

    //--- random horizontal direction left/right in 50%
    if (rand()%2==0)
    {
        rDirectory = rand()%2;
        if (rDirectory==0)
        {
            directionPermutation[0] = 1;
            directionPermutation[1] = 3;
        }
        else
        {
            directionPermutation[0] = 3;
            directionPermutation[1] = 1;
        }
        tabDirectory[1] = tabDirectory[2];
    }
    else
    {
        rDirectory = rand()%4;
        directionPermutation[0] = tabDirectory[rDirectory];
        if (rDirectory!=3) tabDirectory[rDirectory] = tabDirectory[3];
        rDirectory = rand()%3;
        directionPermutation[1] = tabDirectory[rDirectory];
        if (rDirectory!=2) tabDirectory[rDirectory] = tabDirectory[2];
    }

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
                        generateMaze_methodDFS_horizontal(y-1,x);
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
                        generateMaze_methodDFS_horizontal(y,x+1);
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
                        generateMaze_methodDFS_horizontal(y+1,x);
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
                        generateMaze_methodDFS_horizontal(y,x-1);
                    }
                }
                break;
            }
        }
    }
}

void Board::generateMaze_methodDFS_vertical(uint8_t y, uint8_t x)
{
    //-- set the cell as visited
    board[y][x].checkVisited();

    //-- random direction permutation
    uint8_t tabDirectory[4] = {0,1,2,3};
    uint8_t directionPermutation[4];

    //--- random vertical direction up/down in 50%
    if (rand()%2==0)
    {
        rDirectory = rand()%2;
        if (rDirectory==0)
        {
            directionPermutation[0] = 0;
            directionPermutation[1] = 2;
        }
        else
        {
            directionPermutation[0] = 2;
            directionPermutation[1] = 0;
        }
        tabDirectory[0] = tabDirectory[3];
    }
    else
    {
        rDirectory = rand()%4;
        directionPermutation[0] = tabDirectory[rDirectory];
        if (rDirectory!=3) tabDirectory[rDirectory] = tabDirectory[3];
        rDirectory = rand()%3;
        directionPermutation[1] = tabDirectory[rDirectory];
        if (rDirectory!=2) tabDirectory[rDirectory] = tabDirectory[2];
    }

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
                        generateMaze_methodDFS_vertical(y-1,x);
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
                        generateMaze_methodDFS_vertical(y,x+1);
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
                        generateMaze_methodDFS_vertical(y+1,x);
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
                        generateMaze_methodDFS_vertical(y,x-1);
                    }
                }
                break;
            }
        }
    }
}

void Board::generateMaze_methodDFS_spiral(uint8_t y, uint8_t x, int8_t directory, uint8_t l, uint8_t lmax)
{
    //-- set the cell as visited
    board[y][x].checkVisited();

    //-- random direction permutation
    uint8_t tabDirectory[4] = {0,1,2,3};
    uint8_t directionPermutation[4];

    if (rand()%40<37)
    {
        if (l<lmax)
        {
            l+=2;
            if (directory==1)
            {
                directionPermutation[0] = 0;
                directionPermutation[1] = 1;
                directionPermutation[2] = 2;
                directionPermutation[3] = 3;
            }
            else
            if (directory==2)
            {
                directionPermutation[0] = 1;
                directionPermutation[1] = 2;
                directionPermutation[2] = 3;
                directionPermutation[3] = 0;
            }
            else
            if (directory==3)
            {
                directionPermutation[0] = 2;
                directionPermutation[1] = 3;
                directionPermutation[2] = 0;
                directionPermutation[3] = 1;
            }
            else
            if (directory==4)
            {
                directionPermutation[0] = 3;
                directionPermutation[1] = 0;
                directionPermutation[2] = 1;
                directionPermutation[3] = 2;
            }
            else
            if (directory==-1)
            {
                directionPermutation[0] = 0;
                directionPermutation[1] = 3;
                directionPermutation[2] = 2;
                directionPermutation[3] = 1;
            }
            else
            if (directory==-2)
            {
                directionPermutation[0] = 1;
                directionPermutation[1] = 0;
                directionPermutation[2] = 3;
                directionPermutation[3] = 2;
            }
            else
            if (directory==-3)
            {
                directionPermutation[0] = 2;
                directionPermutation[1] = 1;
                directionPermutation[2] = 0;
                directionPermutation[3] = 3;
            }
            else
            if (directory==-4)
            {
                directionPermutation[0] = 3;
                directionPermutation[1] = 2;
                directionPermutation[2] = 1;
                directionPermutation[3] = 0;
            }

        }
        else
        {
            l=0;
            lmax-=2;
            if (lmax < 4)
            {
                lmax = 40;
                directory = rand()%2==0?-1:1;
                directory = directory * rand()%4;
            }
            if (directory==1)
            {
                directory = 2;
                directionPermutation[0] = 1;
                directionPermutation[1] = 2;
                directionPermutation[2] = 3;
                directionPermutation[3] = 0;
            }
            else
            if (directory==2)
            {
                directory = 3;
                directionPermutation[0] = 2;
                directionPermutation[1] = 3;
                directionPermutation[2] = 0;
                directionPermutation[3] = 1;
            }
            else
            if (directory==3)
            {
                directory = 4;
                directionPermutation[0] = 3;
                directionPermutation[1] = 0;
                directionPermutation[2] = 1;
                directionPermutation[3] = 2;
            }
            else
            if (directory==4)
            {
                directory = 1;
                directionPermutation[0] = 0;
                directionPermutation[1] = 1;
                directionPermutation[2] = 2;
                directionPermutation[3] = 3;
            }
            else
            if (directory==-1)
            {
                directory = -2;
                directionPermutation[0] = 3;
                directionPermutation[1] = 2;
                directionPermutation[2] = 1;
                directionPermutation[3] = 0;
            }
            else
            if (directory==-2)
            {
                directory = -3;
                directionPermutation[0] = 0;
                directionPermutation[1] = 3;
                directionPermutation[2] = 2;
                directionPermutation[3] = 1;
            }
            else
            if (directory==-3)
            {
                directory = -4;
                directionPermutation[0] = 1;
                directionPermutation[1] = 0;
                directionPermutation[2] = 3;
                directionPermutation[3] = 2;
            }
            else
            if (directory==-4)
            {
                directory = -1;
                directionPermutation[0] = 2;
                directionPermutation[1] = 1;
                directionPermutation[2] = 0;
                directionPermutation[3] = 3;
            }
        }
    }
    else
    {
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
    }

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
                        generateMaze_methodDFS_spiral(y-1,x,directory,l,lmax);
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
                        generateMaze_methodDFS_spiral(y,x+1,directory,l,lmax);
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
                        generateMaze_methodDFS_spiral(y+1,x,directory,l,lmax);
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
                        generateMaze_methodDFS_spiral(y,x-1,directory,l,lmax);
                    }
                }
                break;
            }
        }
    }
}

void Board::generateMaze_methodStraightLinesDivisionInHalf(uint8_t yStart, uint8_t xStart, uint8_t yEnd, uint8_t xEnd, bool direction)
{
    uint8_t hole;

     //split horizontally
    if (direction && xEnd - xStart > 0 && yEnd - yStart > 0)
    {
        uint8_t yHalf = (yEnd - yStart) / 2 + yStart;
        hole = rand()%(xEnd - xStart + 1) + xStart;

        //drawing lines
        for (uint8_t x = xStart; x < xEnd + 1; x++)
        {
            if (x == hole)
            {
                continue;
            }
            board[yHalf][x].setWall(Cell::DOWN);
            board[yHalf+1][x].setWall(Cell::UP);
        }
        generateMaze_methodStraightLinesDivisionInHalf(yStart, xStart, yHalf, xEnd, false);
        generateMaze_methodStraightLinesDivisionInHalf(yHalf + 1, xStart, yEnd, xEnd, false);
    }

    //split vertically
    if (!direction && yEnd - yStart > 0 && xEnd - xStart > 0)
    {
        uint8_t xHalf = (xEnd - xStart) / 2 + xStart;
        hole = rand()%(yEnd - yStart + 1) + yStart;

        //drawing lines
        for (uint8_t y = yStart; y < yEnd + 1; y++)
        {
            if (y == hole)
            {
                continue;
            }
            board[y][xHalf].setWall(Cell::RIGHT);
            board[y][xHalf+1].setWall(Cell::LEFT);
        }
        generateMaze_methodStraightLinesDivisionInHalf(yStart, xStart, yEnd, xHalf, true);
        generateMaze_methodStraightLinesDivisionInHalf(yStart, xHalf + 1, yEnd, xEnd, true);
    }
}

void Board::generateMaze_methodStraightLinesRandomSplit(uint8_t yStart, uint8_t xStart, uint8_t yEnd, uint8_t xEnd, bool direction)
{
    uint8_t hole;

     //split horizontally
    if (direction && xEnd - xStart > 0 && yEnd - yStart > 0)
    {
        uint8_t yHalf;
        if (yEnd - yStart > 6)
        {
            yHalf = rand()%(yEnd - yStart -2) + yStart + 2;
        }
        else
        {
            yHalf = (yEnd - yStart) / 2 + yStart;
        }
        hole = rand()%(xEnd - xStart + 1) + xStart;

        //drawing lines
        for (uint8_t x = xStart; x < xEnd + 1; x++)
        {
            if (x == hole)
            {
                continue;
            }
            board[yHalf][x].setWall(Cell::DOWN);
            board[yHalf+1][x].setWall(Cell::UP);
        }
        generateMaze_methodStraightLinesRandomSplit(yStart, xStart, yHalf, xEnd, false);
        generateMaze_methodStraightLinesRandomSplit(yHalf + 1, xStart, yEnd, xEnd, false);
    }

    //split vertically
    if (!direction && yEnd - yStart > 0 && xEnd - xStart > 0)
    {
        uint8_t xHalf;
        if (xEnd - xStart > 6)
        {
            xHalf = rand()%(xEnd - xStart - 2) + xStart + 2;
        }
        else
        {
            xHalf = (xEnd - xStart) / 2 + xStart;
        }
        hole = rand()%(yEnd - yStart + 1) + yStart;

        //drawing lines
        for (uint8_t y = yStart; y < yEnd + 1; y++)
        {
            if (y == hole)
            {
                continue;
            }
            board[y][xHalf].setWall(Cell::RIGHT);
            board[y][xHalf+1].setWall(Cell::LEFT);
        }
        generateMaze_methodStraightLinesRandomSplit(yStart, xStart, yEnd, xHalf, true);
        generateMaze_methodStraightLinesRandomSplit(yStart, xHalf + 1, yEnd, xEnd, true);
    }
}

void Board::generateMaze_methodZigzags(uint8_t y, uint8_t x, int8_t directory, uint8_t l, uint8_t lmax)
{
    //-- set the cell as visited
    board[y][x].checkVisited();

    //-- random direction permutation
    uint8_t tabDirectory[4] = {0,1,2,3};
    uint8_t directionPermutation[4];

    if (rand()%40<37)
    {
        if (l<lmax)
        {
            l+=2;
            if (directory==1)
            {
                directionPermutation[0] = 0;
                directionPermutation[1] = 1;
                directionPermutation[2] = 2;
                directionPermutation[3] = 3;
            }
            else
            if (directory==2)
            {
                directionPermutation[0] = 1;
                directionPermutation[1] = 2;
                directionPermutation[2] = 3;
                directionPermutation[3] = 0;
            }
            else
            if (directory==3)
            {
                directionPermutation[0] = 2;
                directionPermutation[1] = 3;
                directionPermutation[2] = 0;
                directionPermutation[3] = 1;
            }
            else
            if (directory==4)
            {
                directionPermutation[0] = 3;
                directionPermutation[1] = 0;
                directionPermutation[2] = 1;
                directionPermutation[3] = 2;
            }
            else
            if (directory==-1)
            {
                directionPermutation[0] = 0;
                directionPermutation[1] = 3;
                directionPermutation[2] = 2;
                directionPermutation[3] = 1;
            }
            else
            if (directory==-2)
            {
                directionPermutation[0] = 1;
                directionPermutation[1] = 0;
                directionPermutation[2] = 3;
                directionPermutation[3] = 2;
            }
            else
            if (directory==-3)
            {
                directionPermutation[0] = 2;
                directionPermutation[1] = 1;
                directionPermutation[2] = 0;
                directionPermutation[3] = 3;
            }
            else
            if (directory==-4)
            {
                directionPermutation[0] = 3;
                directionPermutation[1] = 2;
                directionPermutation[2] = 1;
                directionPermutation[3] = 0;
            }

        }
        else
        {
            l=0;
            lmax-=2;
            if (lmax < 4)
            {
                lmax = 40;
                directory = rand()%2==0?-1:1;
                directory = directory * rand()%4;
            }
            if (directory==1)
            {
                directory = 2;
                directionPermutation[0] = 1;
                directionPermutation[1] = 2;
                directionPermutation[2] = 3;
                directionPermutation[3] = 0;
            }
            else
            if (directory==2)
            {
                directory = 3;
                directionPermutation[0] = 2;
                directionPermutation[1] = 3;
                directionPermutation[2] = 0;
                directionPermutation[3] = 1;
            }
            else
            if (directory==3)
            {
                directory = 4;
                directionPermutation[0] = 3;
                directionPermutation[1] = 0;
                directionPermutation[2] = 1;
                directionPermutation[3] = 2;
            }
            else
            if (directory==4)
            {
                directory = 1;
                directionPermutation[0] = 0;
                directionPermutation[1] = 1;
                directionPermutation[2] = 2;
                directionPermutation[3] = 3;
            }
            else
            if (directory==-1)
            {
                directory = -2;
                directionPermutation[0] = 3;
                directionPermutation[1] = 2;
                directionPermutation[2] = 1;
                directionPermutation[3] = 0;
            }
            else
            if (directory==-2)
            {
                directory = -3;
                directionPermutation[0] = 0;
                directionPermutation[1] = 3;
                directionPermutation[2] = 2;
                directionPermutation[3] = 1;
            }
            else
            if (directory==-3)
            {
                directory = -4;
                directionPermutation[0] = 1;
                directionPermutation[1] = 0;
                directionPermutation[2] = 3;
                directionPermutation[3] = 2;
            }
            else
            if (directory==-4)
            {
                directory = -1;
                directionPermutation[0] = 2;
                directionPermutation[1] = 1;
                directionPermutation[2] = 0;
                directionPermutation[3] = 3;
            }
        }
    }
    else
    {
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
    }

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
                        generateMaze_methodZigzags(y-1,x,directory,l,lmax);
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
                        generateMaze_methodZigzags(y,x+1,directory,l,lmax);
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
                        generateMaze_methodZigzags(y+1,x,directory,l,lmax);
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
                        generateMaze_methodZigzags(y,x-1,directory,l,lmax);
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
