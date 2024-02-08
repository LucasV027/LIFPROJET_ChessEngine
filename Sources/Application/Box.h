#pragma once

#include <algorithm>

class Box
{
private:
    float upMargin;
    float downMargin;
    float leftMargin;
    float rightMargin;

    int screenWidth;
    int screenHeight;

    int boxWidth;
    int boxHeight;

    int positionX;
    int positionY;

public:
    Box(float upMargin, float downMargin, float leftMargin, float rightMargin, int width, int height);

    void resize(int newScreenWidth, int newScreenHeight);

    int getXOffset() const;
    int getYOffset() const;
    int getWidth() const;
    int getHeight() const;

    bool isInside(int x, int y) const;
};