#pragma once

#include "ChessPiece.h"
#include "Player.h"
#include "Utils/Utils.h"

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <deque>

class ChessGame
{
public:
    // Constructors :
    ChessGame(const std::vector<std::string> &terrain, const std::vector<Player> &players, int _turnIndex);
    ChessGame(const std::string &FEN); // Forsyth-Edwards Notation (Modified)
    ChessGame();

    // Getters :
    size_t getHeight() const;
    size_t getWidth() const;
    bool isOver() const;
    std::string toFENString() const;
    bool isItAITurns() const;

    // Game logic :
    const std::vector<Move> getAllPossibleMoves() const;
    bool makeAMove(Move move, bool verifications);
    void undoMove();
    void randomMove();

    // Debug :
    void print() const;
    void printAll() const;
    void printPieceInfos(int x, int y) const;

private:
    // Moving a piece logic :

    // Returns a MoveType because we use this function when we need to verify is the move is valid
    // When we have to verify its means we only have as information the from & the to of the move so we need
    // to recoverer the MoveType
    // PS : if the recovered movetype is NONE then the move is not valid
    MoveType isMoveAllowed(ChessPiece piece, Vec2Int move) const;
    void handleSpecialMoves(Vec2Int from, Vec2Int to, MoveType _moveType);
    void moveAPiece(Vec2Int from, Vec2Int to);
    void didWeCaptureTheKing(Vec2Int to, MoveType _moveType);
    // ---

    // We choose the amount (1 frontwards or -1 for backwards)
    void updatePlayerTurn(int amount);

public:
    std::vector<std::vector<ChessPiece>> chessBoard;
    std::vector<Player> players;

    unsigned int turnIndex;

    std::deque<SavedMove> moveHistory;
};
