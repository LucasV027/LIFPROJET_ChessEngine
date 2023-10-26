#pragma once

enum class Direction
{
    North,
    South,
    Est,
    West
};

enum class Color
{
    Black,
    White,
    Blue,
    Red,

};

struct Vec2Int
{
    int x, y;
    Vec2Int() : x(0), y(0) {}
    Vec2Int(int _x, int _y) : x(_x), y(_y) {}
    Vec2Int(Direction d)
    {
        switch (d)
        {
        case Direction::North:
            x = 0;
            y = 1;
            break;

        case Direction::South:
            x = 0;
            y = -1;
            break;

        case Direction::Est:
            x = 1;
            y = 0;
            break;

        case Direction::West:
            x = -1;
            y = 0;
            break;

        default:
            break;
        }
    }

    bool operator==(const Vec2Int &other) const { return x == other.x && y == other.y; }
};

struct Vec3Int
{
    int r, g, b;

    Vec3Int() : r(0), g(0), b(0) {}
    Vec3Int(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

    Vec3Int(Color c)
    {
        switch (c)
        {
        case Color::Black:
            r = 0;
            g = 0;
            b = 0;
            break;
        case Color::White:
            r = 255;
            g = 255;
            b = 255;
            break;
        case Color::Blue:
            r = 0;
            g = 0;
            b = 255;
            break;
        case Color::Red:
            r = 255;
            g = 0;
            b = 0;
            break;
        default:
            r = 0;
            g = 0;
            b = 0;
            break;
        }
    }
};

