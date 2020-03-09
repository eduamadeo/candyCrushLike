#pragma once

#include "cocos2d.h"
#include "SquaresGrid.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

private:
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    void InitGridSpaces( );
    void InitGridSprites( );

    void checkIfIsSquare( cocos2d::Touch *touch );
    void destroyAndUpdateNodes(int nodesToDestroy[8][8]);
    void addSquare(int i, int j);
    void UpdateTimer(float dt);
    std::string timeToString(int time);
    void updateScoreAndTime(int numberSquares);

    cocos2d::Sprite * gridSprites[8][8];
    cocos2d::Rect gridSpaces[8][8];
    SquaresGrid squaresGrid;
    int time;
    int score;

};