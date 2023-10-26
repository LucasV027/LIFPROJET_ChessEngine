#pragma once

class Box
{
private:
    int screenWidth, screenHeight;
    int positionX, positionY, boxWidth, boxHeight;
    float leftMargin, rightMargin, upMargin, downMargin;

public:
    Box(float upMargin, float downMargin, float leftMargin, float rightMargin, int width, int height);

    void resize(int newScreenWidth, int newScreenHeight);

    int getXOffset() const;
    int getYOffset() const;
    int getWidth() const;
    int getHeight() const;

    bool isInside(int x, int y) const;
};