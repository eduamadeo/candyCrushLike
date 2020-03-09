#include "GameScene.h"
#include <stdlib.h>
#include <math.h>

USING_NS_CC;
using namespace std;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    InitGridSprites();
    /* Grid spaces are used to test if the player has clicked in a square and, if he did,
       get which one. */
    InitGridSpaces();

    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // Adding a scheduler to make the countdown timer of the game.
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::UpdateTimer),1.0f);
    time = 120;
    string strTime = timeToString(time);
    auto label = Label::createWithSystemFont(strTime, "Arial", 96);
    label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
    label->setPosition(350, 520);
    label->setName("Timer");
    this->addChild(label, 1);

    score = 0;
    auto scoreLabel = Label::createWithSystemFont(to_string(score), "Arial", 60);
    scoreLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
    scoreLabel->setPosition(550, 300);
    scoreLabel->setName("Score");
    this->addChild(scoreLabel, 1);
    
    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
  //  cocos2d::log("touch began");
   return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
  checkIfIsSquare( touch );
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
  //  cocos2d::log("touch moved");
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
  //  cocos2d::log("touch cancelled");
}

void GameScene::InitGridSprites() {
  
  for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        addSquare(i, j);
      }
    }
}

void GameScene::InitGridSpaces( )
{
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        gridSpaces[i][j] = Rect(65*i+15,
                                (595 - 65*j+15), 
                                50, 
                                50);
      }
    }
}

void GameScene::checkIfIsSquare( cocos2d::Touch *touch ){
  Point touchPoint = touch->getLocationInView( );
  int numConsecutiveSquares = 0;
  int nodesToDestroy[8][8] = {0};

  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if ( gridSpaces[i][j].containsPoint( touchPoint ) ) {
        numConsecutiveSquares = squaresGrid.getNumberOfConsecutiveSquares(i, j, nodesToDestroy);
        updateScoreAndTime(numConsecutiveSquares);
        cocos2d::log("Number with same color near: %i", numConsecutiveSquares);
        destroyAndUpdateNodes(nodesToDestroy);
        break;
      }
    }
  }
}

void GameScene::destroyAndUpdateNodes(int nodesToDestroy[8][8]){
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if(nodesToDestroy[i][j] == 1){
        squaresGrid.deleteSquareClass(i, j);
        gridSprites[i][j]->removeFromParent();

        addSquare(i, j);
      }
    }
  }

  // Test if there is a solution in the grid. If there isn't, the game will restart.
  if(!squaresGrid.testIfThereIsSolution()){
    auto newScene = GameScene::createScene();
    Director::getInstance()->replaceScene(newScene);
  }
}

void GameScene::addSquare(int i, int j){
  Color3B colors[6];
  colors[0] = Color3B(255, 0, 0);
  colors[1] = Color3B(0, 0, 255);
  colors[2] = Color3B(0, 255, 0);
  colors[3] = Color3B(255, 255, 0);
  colors[4] = Color3B(255, 145, 0);
  colors[5] = Color3B(255, 0, 255);

  int colorIndex = rand() % 6;
  gridSprites[i][j] = Sprite::create("white-square.jpg");
  
  gridSprites[i][j]->setAnchorPoint(Vec2(0, 0));
  gridSprites[i][j]->setPosition(65*i+15, 65*j+15);
  gridSprites[i][j]->setScale(0.1);
  gridSprites[i][j]->setColor(colors[colorIndex]);

  this->addChild(gridSprites[i][j], 0);

  squaresGrid.addNewSquare(i, j, 65*i+15, 65*j+15, colorIndex);
}

void GameScene::UpdateTimer(float dt){
  time --;

  // Test if the time has ended. If it has, the game will restart.
  if(time == 0){
    auto newScene = GameScene::createScene();
    Director::getInstance()->replaceScene(newScene);
  }
  
  string strTime = timeToString(time);
  auto labelNode = dynamic_cast<cocos2d::Label*>(this->getChildByName("Timer"));
  if(labelNode != nullptr)
  {
      labelNode->setString(strTime);
  }
  else
  {
      CCLOGERROR("Failed to find label!");
  }
}

string GameScene::timeToString(int time){
  int minutes = time / 60;
  int seconds = time % 60;
  string strMinutes;
  string strSeconds;
  
  if(minutes < 10){
    strMinutes = "0" + to_string(minutes);
  } else {
    strMinutes = "" + to_string(minutes);
  }

  if(seconds < 10){
    strSeconds = "0" + to_string(seconds);
  } else {
    strSeconds = "" + to_string(seconds);
  }

  return strMinutes + ":" + strSeconds;
}

void GameScene::updateScoreAndTime(int numberSquares){
  if(numberSquares != 0){
    score += (int)(numberSquares - 1) * 80 + pow((numberSquares - 2) / 5, 2);
    time += (int)(pow((numberSquares - 2) / 3, 2) * 20) + 10;

    auto labelNode = dynamic_cast<cocos2d::Label*>(this->getChildByName("Score"));
    if(labelNode != nullptr)
    {
        labelNode->setString(to_string(score));
    }
    else
    {
        CCLOGERROR("Failed to find label!");
    }
  }
}