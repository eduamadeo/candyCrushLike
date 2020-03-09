#include "SquaresGrid.h"

using namespace std;

void SquaresGrid::addNewSquare(int xIndex, int yIndex, float x, float y, int c){
  squaresGrid[xIndex][yIndex] = new SquareClass();
  squaresGrid[xIndex][yIndex]->setColor(c);
  squaresGrid[xIndex][yIndex]->setPositionX(x);
  squaresGrid[xIndex][yIndex]->setPositionY(y);
}

void SquaresGrid::deleteSquareClass(int x, int y){
  delete squaresGrid[x][y];
}

void SquaresGrid::printSquare(int i, int j){
  cocos2d::log("Color: %i", squaresGrid[i][j]->getColor());
}

int SquaresGrid::getNumberOfConsecutiveSquares(int i, int j, int (&nodesToDestroy)[8][8]){
  int numberSquares = 0;
  int alreadyVisited[8][8] = {0};
  int x = 0;
  int y = 0;
  vector<int> queueWithSameColor;
  queueWithSameColor.push_back(i*10 + j);

  while(queueWithSameColor.size() > 0){
    int currentSquare = queueWithSameColor.at(queueWithSameColor.size() - 1);
    queueWithSameColor.pop_back();
    x = currentSquare / 10;
    y = currentSquare % 10;

    if(alreadyVisited[x][y] != 1){
      alreadyVisited[x][y] = 1;
      nodesToDestroy[x][y] = 1;
      cocos2d::log("X: %d, Y: %d, current: %i", x, y, currentSquare);
      if(x+1 < 8){
        if(squaresGrid[x+1][y]->getColor() == squaresGrid[x][y]->getColor() && alreadyVisited[x+1][y] != 1){
          queueWithSameColor.push_back(((x+1) * 10) + y);
          numberSquares++;
        }
      }
      if(x-1 >= 0){
        if(squaresGrid[x-1][y]->getColor() == squaresGrid[x][y]->getColor() && alreadyVisited[x-1][y] != 1){
          queueWithSameColor.push_back(((x-1) * 10) + y);
          numberSquares++;
        }
      }
      if(y+1 < 8){
        if(squaresGrid[x][y+1]->getColor() == squaresGrid[x][y]->getColor() && alreadyVisited[x][y+1] != 1){
          queueWithSameColor.push_back((x * 10) + y + 1);
          numberSquares++;
        }
      }
      if(y-1 >= 0){
        if(squaresGrid[x][y-1]->getColor() == squaresGrid[x][y]->getColor() && alreadyVisited[x][y-1] != 1){
          queueWithSameColor.push_back((x * 10) + y - 1);
          numberSquares++;
        }
      }
    } else {
      numberSquares--;
    }
  }

  if(numberSquares != 0){
    numberSquares++;
  } else {
    nodesToDestroy[x][y] = 0;
  }

  return numberSquares;
}

bool SquaresGrid::testIfThereIsSolution(){
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if(i+1 < 8){
        if(squaresGrid[i+1][j]->getColor() == squaresGrid[i][j]->getColor()){
          return true;
        }
      }
      if(i-1 >= 0){
        if(squaresGrid[i-1][j]->getColor() == squaresGrid[i][j]->getColor()){
          return true;
        }
      }
      if(j+1 < 8){
        if(squaresGrid[i][j+1]->getColor() == squaresGrid[i][j]->getColor()){
          return true;
        }
      }
      if(j-1 >= 0){
        if(squaresGrid[i][j-1]->getColor() == squaresGrid[i][j]->getColor()){
          return true;
        }
      }
    }
  }

  return false;
}