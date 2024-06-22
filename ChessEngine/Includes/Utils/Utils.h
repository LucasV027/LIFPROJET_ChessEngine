#pragma once

#include <iostream>
#include <math.h>

enum class Direction
{
    North,
    South,
    Est,
    West,
    None
};

enum class Color
{
    Black,
    White,
    Blue,
    Red,
    Yellow,
    Green,
    None,

};

enum class MoveType
{
    NONE,
    NORMAL,
    CAPTURE,
    PROMOTION,
    PAWN2,
    CAPTURE_PROMOTION,
};

enum class PieceType
{
    NONE,
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    KING,
    QUEEN,
};

struct Vec2Int
{
    int x, y;
    Vec2Int();
    Vec2Int(int _x, int _y);
    Vec2Int(Direction d);

    bool operator==(const Vec2Int &other) const;
    bool operator!=(const Vec2Int &other) const;

    Vec2Int operator-(const Vec2Int &other) const;
    int length() const;

    void print() const;
};

struct Move
{
    Vec2Int from;
    Vec2Int to;
    MoveType moveType;

    Move();
    Move(Vec2Int _from, Vec2Int _to, MoveType _moveType);
    Move(int x0, int y0, int x1, int y1, MoveType _moveType);
};

PieceType charToPieceType(char c);
void printColor(Color c);
void printDirection(Direction d);
char toChar(PieceType pt, int playerindex);

struct Vec3Int
{
    int r, g, b;

    Vec3Int();
    Vec3Int(int _r, int _g, int _b);

    Vec3Int(Color c);

    bool operator==(const Vec3Int &other) const;
    bool operator!=(const Vec3Int &other) const;
    void print() const;
};

struct Vec4Int
{
    int x1;
    int y1;
    int x2;
    int y2;

    Vec4Int();
    Vec4Int(int _x1, int _y1, int _x2, int _y2);
    Vec4Int(const Vec4Int &other);

    Vec2Int getFrom() const;

    Vec2Int getTo() const;

    void print() const;
};

bool validFEN(std::string s);
