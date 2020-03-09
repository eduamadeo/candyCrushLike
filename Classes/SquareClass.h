#pragma once

class SquareClass
{
public:

    void setColor(int c);
    int getColor();

    void setPositionX(float x);
    float getPositionX();

    void setPositionY(float y);
    float getPositionY();



private:
    int color;
    float positionX;
    float positionY;
};