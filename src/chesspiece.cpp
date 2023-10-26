#include "chesspiece.h"
#include "ChessGame.h"

std::vector<Vec2Int> &ChessPiece::getPossibleMoves() { return possibleMoves; }
unsigned int ChessPiece::getPlayerIndex() const { return playerIndex; }
unsigned int ChessPiece::getTextureIndex() const { return textureIndex; }
unsigned int ChessPiece::getPostionX() const { return positionX; }
unsigned int ChessPiece::getPostionY() const { return positionY; }

ChessPiece::ChessPiece(int initialX, int initialY, int playerIndex, int textureIndex) : positionX(initialX), positionY(initialY), playerIndex(playerIndex), textureIndex(textureIndex), hasMovedOnce(false) {}
Pawn::Pawn(int initialX, int initialY, int playerIndex) : ChessPiece(initialX, initialY, playerIndex, 0) {}
Knight::Knight(int initialX, int initialY, int playerIndex) : ChessPiece(initialX, initialY, playerIndex, 1) {}
Bishop::Bishop(int initialX, int initialY, int playerIndex) : ChessPiece(initialX, initialY, playerIndex, 2) {}
Rook::Rook(int initialX, int initialY, int playerIndex) : ChessPiece(initialX, initialY, playerIndex, 3) {}
Queen::Queen(int initialX, int initialY, int playerIndex) : ChessPiece(initialX, initialY, playerIndex, 4) {}
King::King(int initialX, int initialY, int playerIndex) : ChessPiece(initialX, initialY, playerIndex, 5) {}

void ChessPiece::moved() { hasMovedOnce = true; }

bool ChessPiece::isPiece(const ChessGame &game, int x, int y) const
{
    return bool(game.getElement(y, x));
}

bool ChessPiece::isEnemy(const ChessGame &game, int x, int y) const
{
    return (game.getElement(y, x) && game.getElement(y, x)->playerIndex != game.getTurn());
}

bool ChessPiece::isAlly(const ChessGame &game, int x, int y) const
{
    return (game.getElement(y, x) && game.getElement(y, x)->playerIndex != game.getTurn());
}

bool ChessPiece::outOfBounds(const ChessGame &game, int x, int y) const
{
    return (x < 0 || y < 0 || x >= game.getWidth() || y >= game.getHeight());
}

void ChessPiece::setValidMoves(const ChessGame &game) {}

void Pawn::setValidMoves(const ChessGame &game)
{
    bool front_is_open = false;
    Vec2Int dir = game.getPlayer(game.getTurn()).playerDirection;

    if (!outOfBounds(game, positionX + dir.x, positionY - dir.y) && !isPiece(game, positionX + dir.x, positionY - dir.y)) // 1 CASE FRONT
    {
        possibleMoves.push_back(Vec2Int(positionX + dir.x, positionY - dir.y));
        front_is_open = true;
    }
    if (!hasMovedOnce && front_is_open) // 2 CASES FRONT
    {
        if (!outOfBounds(game, positionX + dir.x * 2, positionY - dir.y * 2) && !isPiece(game, positionX + dir.x * 2, positionY - dir.y * 2))
        {
            possibleMoves.push_back(Vec2Int(positionX + dir.x * 2, positionY - dir.y * 2));
        }
    }

    // Diagonally opposite
    if (dir.x != 0) // The pawn front is on the x axis
    {
        if (!outOfBounds(game, positionX + dir.x, positionY - 1) && isEnemy(game, positionX + dir.x, positionY - 1)) // Right or Left up
        {
            possibleMoves.push_back(Vec2Int(positionX + dir.x, positionY - 1));
        }

        if (!outOfBounds(game, positionX + dir.x, positionY + 1) && isEnemy(game, positionX + dir.x, positionY + 1)) // Right or Left down
        {
            possibleMoves.push_back(Vec2Int(positionX + dir.x, positionY + 1));
        }
    }
    else // The pawn front is on the y axis
    {
        if (!outOfBounds(game, positionX + 1, positionY - dir.y) && isEnemy(game, positionX + 1, positionY - dir.y)) // Up or down right
        {
            possibleMoves.push_back(Vec2Int(positionX + 1, positionY - dir.y));
        }

        if (!outOfBounds(game, positionX - 1, positionY - dir.y) && isEnemy(game, positionX - 1, positionY - dir.y)) // Up or down left
        {
            possibleMoves.push_back(Vec2Int(positionX - 1, positionY - dir.y));
        }
    }
}

void Knight::setValidMoves(const ChessGame &game)
{
    if (!outOfBounds(game, positionX + 2, positionY + 1) && !isAlly(game, positionX + 2, positionY + 1)) // Right down
        possibleMoves.push_back(Vec2Int(positionX + 2, positionY + 1));

    if (!outOfBounds(game, positionX + 2, positionY - 1) && !isAlly(game, positionX + 2, positionY - 1)) // Right up
        possibleMoves.push_back(Vec2Int(positionX + 2, positionY - 1));

    if (!outOfBounds(game, positionX - 2, positionY + 1) && !isAlly(game, positionX - 2, positionY + 1)) // Left down
        possibleMoves.push_back(Vec2Int(positionX - 2, positionY + 1));

    if (!outOfBounds(game, positionX - 2, positionY - 1) && !isAlly(game, positionX - 2, positionY - 1)) // Left up
        possibleMoves.push_back(Vec2Int(positionX - 2, positionY - 1));

    if (!outOfBounds(game, positionX + 1, positionY - 2) && !isAlly(game, positionX + 1, positionY - 2)) // Up right
        possibleMoves.push_back(Vec2Int(positionX + 1, positionY - 2));

    if (!outOfBounds(game, positionX - 1, positionY - 2) && !isAlly(game, positionX - 1, positionY - 2)) // Up left
        possibleMoves.push_back(Vec2Int(positionX - 1, positionY - 2));

    if (!outOfBounds(game, positionX + 1, positionY + 2) && !isAlly(game, positionX + 1, positionY + 2)) // Down right
        possibleMoves.push_back(Vec2Int(positionX + 1, positionY + 2));

    if (!outOfBounds(game, positionX - 1, positionY + 2) && !isAlly(game, positionX - 1, positionY + 2)) // Down left
        possibleMoves.push_back(Vec2Int(positionX - 1, positionY + 2));
}

void Bishop::setValidMoves(const ChessGame &game)
{
    int i = 1;
    while (!outOfBounds(game, positionX - i, positionY - i) && !isAlly(game, positionX - i, positionY - i)) // Up Left
    {
        possibleMoves.push_back(Vec2Int(positionX - i, positionY - i));

        if (isEnemy(game, positionX - i, positionY - i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX + i, positionY + i) && !isAlly(game, positionX + i, positionY + i)) // Down Right
    {
        possibleMoves.push_back(Vec2Int(positionX + i, positionY + i));

        if (isEnemy(game, positionX + i, positionY + i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX - i, positionY + i) && !isAlly(game, positionX - i, positionY + i)) // Down Left
    {
        possibleMoves.push_back(Vec2Int(positionX - i, positionY + i));

        if (isEnemy(game, positionX - i, positionY + i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX + i, positionY - i) && !isAlly(game, positionX + i, positionY - i)) // Up Right
    {
        possibleMoves.push_back(Vec2Int(positionX + i, positionY - i));

        if (isEnemy(game, positionX + i, positionY - i))
            break;
        i++;
    }
}

void Rook::setValidMoves(const ChessGame &game)
{
    int i = 1;
    while (!outOfBounds(game, positionX - i, positionY) && !isAlly(game, positionX - i, positionY)) // Left
    {
        possibleMoves.push_back(Vec2Int(positionX - i, positionY));

        if (isEnemy(game, positionX - i, positionY))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX, positionY + i) && !isAlly(game, positionX, positionY + i)) // Down
    {
        possibleMoves.push_back(Vec2Int(positionX, positionY + i));

        if (isEnemy(game, positionX, positionY + i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX + i, positionY) && !isAlly(game, positionX + i, positionY)) // Right
    {
        possibleMoves.push_back(Vec2Int(positionX + i, positionY));

        if (isEnemy(game, positionX + i, positionY))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX, positionY - i) && !isAlly(game, positionX, positionY - i)) // Up
    {
        possibleMoves.push_back(Vec2Int(positionX, positionY - i));

        if (isEnemy(game, positionX, positionY - i))
            break;
        i++;
    }
}

void Queen::setValidMoves(const ChessGame &game)
{
    int i = 1;
    while (!outOfBounds(game, positionX - i, positionY - i) && !isAlly(game, positionX - i, positionY - i)) // Up Left
    {
        possibleMoves.push_back(Vec2Int(positionX - i, positionY - i));

        if (isEnemy(game, positionX - i, positionY - i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX + i, positionY + i) && !isAlly(game, positionX + i, positionY + i)) // Down Right
    {
        possibleMoves.push_back(Vec2Int(positionX + i, positionY + i));

        if (isEnemy(game, positionX + i, positionY + i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX - i, positionY + i) && !isAlly(game, positionX - i, positionY + i)) // Down Left
    {
        possibleMoves.push_back(Vec2Int(positionX - i, positionY + i));

        if (isEnemy(game, positionX - i, positionY + i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX + i, positionY - i) && !isAlly(game, positionX + i, positionY - i)) // Up Right
    {
        possibleMoves.push_back(Vec2Int(positionX + i, positionY - i));

        if (isEnemy(game, positionX + i, positionY - i))
            break;
        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX - i, positionY) && !isAlly(game, positionX - i, positionY)) // Left
    {
        possibleMoves.push_back(Vec2Int(positionX - i, positionY));

        if (isEnemy(game, positionX - i, positionY))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX, positionY + i) && !isAlly(game, positionX, positionY + i)) // Down
    {
        possibleMoves.push_back(Vec2Int(positionX, positionY + i));

        if (isEnemy(game, positionX, positionY + i))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX + i, positionY) && !isAlly(game, positionX + i, positionY)) // Right
    {
        possibleMoves.push_back(Vec2Int(positionX + i, positionY));

        if (isEnemy(game, positionX + i, positionY))
            break;

        i++;
    }

    i = 1;
    while (!outOfBounds(game, positionX, positionY - i) && !isAlly(game, positionX, positionY - i)) // Up
    {
        possibleMoves.push_back(Vec2Int(positionX, positionY - i));

        if (isEnemy(game, positionX, positionY - i))
            break;
        i++;
    }
}

void King::setValidMoves(const ChessGame &game)
{

    // Need Castle implementation //

    if (!outOfBounds(game, positionX + 1, positionY) && !isAlly(game, positionX + 1, positionY)) // Right
        possibleMoves.push_back(Vec2Int(positionX + 1, positionY));

    if (!outOfBounds(game, positionX - 1, positionY) && !isAlly(game, positionX - 1, positionY)) // Left
        possibleMoves.push_back(Vec2Int(positionX - 1, positionY));

    if (!outOfBounds(game, positionX, positionY - 1) && !isAlly(game, positionX, positionY - 1)) // Up
        possibleMoves.push_back(Vec2Int(positionX, positionY - 1));

    if (!outOfBounds(game, positionX, positionY + 1) && !isAlly(game, positionX, positionY + 1)) // Down
        possibleMoves.push_back(Vec2Int(positionX, positionY + 1));

    if (!outOfBounds(game, positionX - 1, positionY - 1) && !isAlly(game, positionX - 1, positionY - 1)) // Left up corner
        possibleMoves.push_back(Vec2Int(positionX - 1, positionY - 1));

    if (!outOfBounds(game, positionX - 1, positionY + 1) && !isAlly(game, positionX - 1, positionY + 1)) // Left down corner
        possibleMoves.push_back(Vec2Int(positionX - 1, positionY + 1));

    if (!outOfBounds(game, positionX + 1, positionY - 1) && !isAlly(game, positionX + 1, positionY - 1)) // Right up corner
        possibleMoves.push_back(Vec2Int(positionX + 1, positionY - 1));

    if (!outOfBounds(game, positionX + 1, positionY + 1) && !isAlly(game, positionX + 1, positionY + 1)) // Right down corner
        possibleMoves.push_back(Vec2Int(positionX + 1, positionY + 1));
}
