#pragma once

#include <vector>
#include <memory>

#include "utils.h"

class ChessGame;

class ChessPiece
{
public:
    ChessPiece(int initialX, int initialY, int playerIndex, int textureIndex);

    virtual void setValidMoves(const ChessGame &game);

    bool isEnemy(const ChessGame &game, int x, int y) const;
    bool isAlly(const ChessGame &game, int x, int y) const;
    bool outOfBounds(const ChessGame &game, int x, int y) const;
    bool isPiece(const ChessGame &game, int x, int y) const;

    void moved();

public:
    std::vector<Vec2Int> &getPossibleMoves();
    unsigned int getPlayerIndex() const;
    unsigned int getTextureIndex() const;
    unsigned int getPostionX() const;
    unsigned int getPostionY() const;

public:
    int positionX, positionY;
    bool hasMovedOnce;
    std::vector<Vec2Int> possibleMoves;

private:
    int textureIndex;
    int playerIndex;
};

class Pawn : public ChessPiece
{
public:
    Pawn(int initialX, int initialY, int playerIndex);
    virtual void setValidMoves(const ChessGame &game) override;
};

class Knight : public ChessPiece
{
public:
    Knight(int initialX, int initialY, int playerIndex);
    virtual void setValidMoves(const ChessGame &game) override;
};

class Bishop : public ChessPiece
{
public:
    Bishop(int initialX, int initialY, int playerIndex);
    virtual void setValidMoves(const ChessGame &game) override;
};

class Rook : public ChessPiece
{
public:
    Rook(int initialX, int initialY, int playerIndex);
    virtual void setValidMoves(const ChessGame &game) override;
};

class Queen : public ChessPiece
{
public:
    Queen(int initialX, int initialY, int playerIndex);
    virtual void setValidMoves(const ChessGame &game) override;
};

class King : public ChessPiece
{
public:
    King(int initialX, int initialY, int playerIndex);
    virtual void setValidMoves(const ChessGame &game) override;
};
