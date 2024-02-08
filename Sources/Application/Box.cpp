#include "Box.h"

Box::Box(float _upMargin, float _downMargin, float _leftMargin, float _rightMargin, int _width, int _height)
    : upMargin(_upMargin),
      downMargin(_downMargin),
      leftMargin(_leftMargin),
      rightMargin(_rightMargin),
      screenWidth(_width),
      screenHeight(_height)
{
    positionX = leftMargin * screenWidth;
    positionY = upMargin * screenHeight;
    boxWidth = screenWidth - (rightMargin * screenWidth) - positionX;
    boxHeight = screenHeight - (downMargin * screenHeight) - positionY;
}

void Box::resize(int new_screen_width, int new_screen_height)
{
    positionX = leftMargin * new_screen_width;
    positionY = upMargin * new_screen_height;
    boxWidth = new_screen_width - (rightMargin * new_screen_width) - positionX;
    boxHeight = new_screen_height - (downMargin * new_screen_height) - positionY;

    // To make the box a square
    boxWidth = std::min(boxWidth, boxHeight);
    boxHeight = std::min(boxHeight, boxWidth);
}

int Box::getXOffset() const { return positionX; }
int Box::getYOffset() const { return positionY; }
int Box::getWidth() const { return boxWidth; }
int Box::getHeight() const { return boxHeight; }

bool Box::isInside(int x, int y) const
{
    return (x >= positionX && x <= (positionX + boxWidth) && y >= positionY && y <= (positionY + boxHeight));
}
