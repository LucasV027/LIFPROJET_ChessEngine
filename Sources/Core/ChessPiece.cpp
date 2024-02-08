#include "ChessPiece.h"
#include "ChessGame.h"

ChessPiece::ChessPiece() : caseType(PieceType::NONE), x(0), y(0), playerIndex(0), hasMovedOnce(false) {}
ChessPiece::ChessPiece(PieceType _type, int initialX, int initialY, int playerIndex) : caseType(_type), x(initialX), y(initialY), playerIndex(playerIndex), hasMovedOnce(false) {}
ChessPiece::ChessPiece(PieceType _type, int initialX, int initialY, int playerIndex, bool _hasMovedOnce) : caseType(_type), x(initialX), y(initialY), playerIndex(playerIndex), hasMovedOnce(_hasMovedOnce) {}

void ChessPiece::setNull()
{
    this->caseType = PieceType::NONE;
    this->playerIndex = -1;
}

int ChessPiece::getValue() const
{
    switch (this->caseType)
    {
    case PieceType::PAWN:
        return 100;
    case PieceType::KNIGHT:
    case PieceType::BISHOP:
        return 300;
    case PieceType::ROOK:
        return 500;
    case PieceType::QUEEN:
        return 900;
    case PieceType::KING:
        return 2000;
    default:
        return 0;
        break;
    }
}

bool ChessPiece::isPiece(const ChessGame &game, int x, int y) const
{
    return bool(game.chessBoard[y][x]);
}

bool ChessPiece::isEnemy(const ChessGame &game, int x, int y) const
{
    return (isPiece(game, x, y) && this->playerIndex != game.chessBoard[y][x].playerIndex);
}

bool ChessPiece::isAlly(const ChessGame &game, int x, int y) const
{
    return (isPiece(game, x, y) && this->playerIndex == game.chessBoard[y][x].playerIndex);
}

bool ChessPiece::outOfBounds(const ChessGame &game, int x, int y) const
{
    return (x < 0 || y < 0 || x >= game.getWidth() || y >= game.getHeight());
}

void ChessPiece::returnValidMoves(const ChessGame &game, std::vector<Move> &moves) const
{
    switch (this->caseType)
    {
    case PieceType::PAWN:
        return pawnMovesLogic(game, moves);
    case PieceType::KNIGHT:
        return knightMovesLogic(game, moves);
    case PieceType::BISHOP:
        return bishopMovesLogic(game, moves);
    case PieceType::ROOK:
        return rookMovesLogic(game, moves);
    case PieceType::QUEEN:
        return queenMovesLogic(game, moves);
    case PieceType::KING:
        return kingMovesLogic(game, moves);
    default:
        break;
    }
}

void ChessPiece::moved() { hasMovedOnce = true; }

void ChessPiece::pawnMovesLogic(const ChessGame &game, std::vector<Move> &moves) const
{

    bool front_is_open = false;
    Vec2Int dir = game.players[playerIndex].playerDirection;

    if (!outOfBounds(game, x + dir.x, y - dir.y) && !isPiece(game, x + dir.x, y - dir.y)) // 1 CASE FRONT
    {
        moves.push_back(Move(this->x, this->y, x + dir.x, y - dir.y, (outOfBounds(game, x + dir.x * 2, y - dir.y * 2) ? MoveType::PROMOTION : MoveType::NORMAL)));
        front_is_open = true;
    }
    if (!hasMovedOnce && front_is_open) // 2 CASES FRONT
    {
        if (!outOfBounds(game, x + dir.x * 2, y - dir.y * 2) && !isPiece(game, x + dir.x * 2, y - dir.y * 2))
        {
            moves.push_back(Move(this->x, this->y, x + dir.x * 2, y - dir.y * 2, MoveType::PAWN2));
        }
    }

    // Diagonally opposite
    if (dir.x != 0) // The pawn front is on the x axis
    {
        if (!outOfBounds(game, x + dir.x, y - 1) && isEnemy(game, x + dir.x, y - 1)) // Right or Left up
        {
            moves.push_back(Move(this->x, this->y, x + dir.x, y - 1, (outOfBounds(game, x + dir.x * 2, y - 1) ? MoveType::CAPTURE_PROMOTION : MoveType::CAPTURE)));
        }

        if (!outOfBounds(game, x + dir.x, y + 1) && isEnemy(game, x + dir.x, y + 1)) // Right or Left down
        {
            moves.push_back(Move(this->x, this->y, x + dir.x, y + 1, (outOfBounds(game, x + dir.x * 2, y + 1) ? MoveType::CAPTURE_PROMOTION : MoveType::CAPTURE)));
        }
    }
    else // The pawn front is on the y axis
    {
        if (!outOfBounds(game, x + 1, y - dir.y) && isEnemy(game, x + 1, y - dir.y)) // Up or down right
        {
            moves.push_back(Move(this->x, this->y, x + 1, y - dir.y, (outOfBounds(game, x + 1, y - dir.y * 2) ? MoveType::CAPTURE_PROMOTION : MoveType::CAPTURE)));
        }

        if (!outOfBounds(game, x - 1, y - dir.y) && isEnemy(game, x - 1, y - dir.y)) // Up or down left
        {
            moves.push_back(Move(this->x, this->y, x - 1, y - dir.y, (outOfBounds(game, x - 1, y - dir.y * 2) ? MoveType::CAPTURE_PROMOTION : MoveType::CAPTURE)));
        }
    }
}

void ChessPiece::knightMovesLogic(const ChessGame &game, std::vector<Move> &moves) const
{

    if (!outOfBounds(game, x + 2, y + 1) && !isAlly(game, x + 2, y + 1)) // Right down
        moves.push_back(Move(this->x, this->y, x + 2, y + 1, (isEnemy(game, x + 2, y + 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x + 2, y - 1) && !isAlly(game, x + 2, y - 1)) // Right up
        moves.push_back(Move(this->x, this->y, x + 2, y - 1, (isEnemy(game, x + 2, y - 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 2, y + 1) && !isAlly(game, x - 2, y + 1)) // Left down
        moves.push_back(Move(this->x, this->y, x - 2, y + 1, (isEnemy(game, x - 2, y + 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 2, y - 1) && !isAlly(game, x - 2, y - 1)) // Left up
        moves.push_back(Move(this->x, this->y, x - 2, y - 1, (isEnemy(game, x - 2, y - 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x + 1, y - 2) && !isAlly(game, x + 1, y - 2)) // Up right
        moves.push_back(Move(this->x, this->y, x + 1, y - 2, (isEnemy(game, x + 1, y - 2) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 1, y - 2) && !isAlly(game, x - 1, y - 2)) // Up left
        moves.push_back(Move(this->x, this->y, x - 1, y - 2, (isEnemy(game, x - 1, y - 2) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x + 1, y + 2) && !isAlly(game, x + 1, y + 2)) // Down right
        moves.push_back(Move(this->x, this->y, x + 1, y + 2, (isEnemy(game, x + 1, y + 2) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 1, y + 2) && !isAlly(game, x - 1, y + 2)) // Down left
        moves.push_back(Move(this->x, this->y, x - 1, y + 2, (isEnemy(game, x - 1, y + 2) ? MoveType::CAPTURE : MoveType::NORMAL)));
}

void ChessPiece::bishopMovesLogic(const ChessGame &game, std::vector<Move> &moves) const
{

    slidingPiecesLogic(moves, game, 1, 1);
    slidingPiecesLogic(moves, game, -1, -1);
    slidingPiecesLogic(moves, game, -1, 1);
    slidingPiecesLogic(moves, game, 1, -1);
}

void ChessPiece::rookMovesLogic(const ChessGame &game, std::vector<Move> &moves) const
{

    slidingPiecesLogic(moves, game, 1, 0);
    slidingPiecesLogic(moves, game, 0, 1);
    slidingPiecesLogic(moves, game, -1, 0);
    slidingPiecesLogic(moves, game, 0, -1);
}

void ChessPiece::queenMovesLogic(const ChessGame &game, std::vector<Move> &moves) const
{

    slidingPiecesLogic(moves, game, 1, 0);
    slidingPiecesLogic(moves, game, 0, 1);
    slidingPiecesLogic(moves, game, -1, 0);
    slidingPiecesLogic(moves, game, 0, -1);
    slidingPiecesLogic(moves, game, 1, 1);
    slidingPiecesLogic(moves, game, 1, -1);
    slidingPiecesLogic(moves, game, -1, 1);
    slidingPiecesLogic(moves, game, -1, -1);
}

void ChessPiece::kingMovesLogic(const ChessGame &game, std::vector<Move> &moves) const
{

    if (!outOfBounds(game, x + 1, y) && !isAlly(game, x + 1, y)) // Right
        moves.push_back(Move(this->x, this->y, x + 1, y, (isEnemy(game, x + 1, y) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 1, y) && !isAlly(game, x - 1, y)) // Left
        moves.push_back(Move(this->x, this->y, x - 1, y, (isEnemy(game, x - 1, y) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x, y - 1) && !isAlly(game, x, y - 1)) // Up
        moves.push_back(Move(this->x, this->y, x, y - 1, (isEnemy(game, x, y - 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x, y + 1) && !isAlly(game, x, y + 1)) // Down
        moves.push_back(Move(this->x, this->y, x, y + 1, (isEnemy(game, x, y + 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 1, y - 1) && !isAlly(game, x - 1, y - 1)) // Left up corner
        moves.push_back(Move(this->x, this->y, x - 1, y - 1, (isEnemy(game, x - 1, y - 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x - 1, y + 1) && !isAlly(game, x - 1, y + 1)) // Left down corner
        moves.push_back(Move(this->x, this->y, x - 1, y + 1, (isEnemy(game, x - 1, y + 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x + 1, y - 1) && !isAlly(game, x + 1, y - 1)) // Right up corner
        moves.push_back(Move(this->x, this->y, x + 1, y - 1, (isEnemy(game, x + 1, y - 1) ? MoveType::CAPTURE : MoveType::NORMAL)));

    if (!outOfBounds(game, x + 1, y + 1) && !isAlly(game, x + 1, y + 1)) // Right down corner
        moves.push_back(Move(this->x, this->y, x + 1, y + 1, (isEnemy(game, x + 1, y + 1) ? MoveType::CAPTURE : MoveType::NORMAL)));
}

void ChessPiece::slidingPiecesLogic(std::vector<Move> &moves, const ChessGame &game, int dirX, int dirY) const
{
    int i = 1;
    while (!outOfBounds(game, x + i * dirX, y + i * dirY) && !isAlly(game, x + i * dirX, y + i * dirY))
    {
        if (isEnemy(game, x + i * dirX, y + i * dirY))
        {
            moves.push_back(Move(this->x, this->y, x + i * dirX, y + i * dirY, MoveType::CAPTURE));
            break;
        }

        moves.push_back(Move(this->x, this->y, x + i * dirX, y + i * dirY, MoveType::NORMAL));

        i++;
    }
}

void ChessPiece::print() const
{
    switch (this->caseType)
    {
    case PieceType::PAWN:
        std::cout << "P" << this->playerIndex;
        break;
    case PieceType::KNIGHT:
        std::cout << "N" << this->playerIndex;
        break;
    case PieceType::BISHOP:
        std::cout << "B" << this->playerIndex;
        break;
    case PieceType::ROOK:
        std::cout << "R" << this->playerIndex;
        break;
    case PieceType::QUEEN:
        std::cout << "Q" << this->playerIndex;
        break;
    case PieceType::KING:
        std::cout << "K" << this->playerIndex;
        break;
    default:
        std::cout << "XX";
        break;
    }
}

void ChessPiece::printInfos() const
{
    this->print();
    std::cout << "(" << x << ";" << y << ") ";
}

ChessPiece::operator bool() const
{
    return (this->caseType != PieceType::NONE);
}