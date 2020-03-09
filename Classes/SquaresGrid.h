#pragma once
#include "SquareClass.h"
#include "cocos2d.h"

class SquaresGrid
{
public:

    bool checkIfHasPossiblePlay();
    void addNewSquare(int xIndex, int yIndex, float x, float y, int color);
    void deleteSquareClass(int x, int y);
    void printSquare(int i, int j);
    int getNumberOfConsecutiveSquares(int i, int j, int (&nodesToDestroy)[8][8]);
    bool testIfThereIsSolution();

private:
    SquareClass * squaresGrid[8][8];
};