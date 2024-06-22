#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Utils/Utils.h"

class ChessGame;

class ChessPiece
{
public:
    // Constructors
    ChessPiece();
    ChessPiece(PieceType _type, int initialX, int initialY, int playerIndex);
    ChessPiece(PieceType _type, int initialX, int initialY, int playerIndex, bool hasMovedOnce);

    // Game logic

    // This methode reset a piece by making it blank (it just change the caseType to NONE & the player index to -1)
    // Made to make the code more readable
    void setNull();

    // Used to manipulate the hasMovedOnce boolean
    // Useful for en castling & pawn being able to move 2 square for their first move
    void moved();

    // Evaluation
    // Returns the value of each pieces useful for the evaluation function in ChessIA
    int getValue() const;

    // Take a vector in entry & fills it with all the possible moves from the player who it is his turn
    void returnValidMoves(const ChessGame &game, std::vector<Move> &moves) const;

    // Debug (printing with std::cout)
    void print() const;
    void printInfos() const;

    // Operators
    // Returns true if the case is blank (because a case in our code is a ChessPiece with certain values)
    operator bool() const;

private:
    // Move logic
    void slidingPiecesLogic(std::vector<Move> &moves, const ChessGame &game, int dirX, int dirY) const;

    // Calculating moves
    void pawnMovesLogic(const ChessGame &game, std::vector<Move> &moves) const;
    void knightMovesLogic(const ChessGame &game, std::vector<Move> &moves) const;
    void bishopMovesLogic(const ChessGame &game, std::vector<Move> &moves) const;
    void rookMovesLogic(const ChessGame &game, std::vector<Move> &moves) const;
    void queenMovesLogic(const ChessGame &game, std::vector<Move> &moves) const;
    void kingMovesLogic(const ChessGame &game, std::vector<Move> &moves) const;

    // Private logic for evaluating possible moves

    // To check either its an enemy or an ally we just compare the playerindex associated with each pieces involved
    bool isEnemy(const ChessGame &game, int x, int y) const;
    bool isAlly(const ChessGame &game, int x, int y) const;
    bool outOfBounds(const ChessGame &game, int x, int y) const;
    bool isPiece(const ChessGame &game, int x, int y) const;

public:
    PieceType caseType;
    int x;
    int y;
    int playerIndex;
    bool hasMovedOnce;
};

struct SavedMove
{
    ChessPiece savedFrom;
    ChessPiece savedTo;

    MoveType moveType;

    SavedMove(ChessPiece _savedFrom, ChessPiece _savedTo, MoveType _moveType) : savedFrom(_savedFrom), savedTo(_savedTo), moveType(_moveType) {}
};