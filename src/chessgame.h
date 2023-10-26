#pragma once

#include <string>
#include <vector>
#include <optional>

#include "utils.h"
#include "chesspiece.h"

struct Player
{
    std::string playerName;
    unsigned int playerIndex;
    Vec2Int playerDirection;
    Vec3Int playerColor;

    Player(unsigned int index, std::string name, Direction dir, Color col);
};

class ChessGame
{
public:
    ChessGame();

    int setAllValidMoves();
    void clearAllMoves();

public:
    const std::vector<std::vector<std::optional<ChessPiece>>> &getChessBoard() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    std::optional<ChessPiece> getElement(int y, int x) const;
    void setElement(int y, int x, ChessPiece val);

    const std::vector<Player> &getPlayersVector() const;
    unsigned int getPlayersNumber() const;
    Player getPlayer(int index) const;
    void setPlayer(int index, Player p);

    unsigned int getTurn() const;

private:
    std::vector<std::vector<std::optional<ChessPiece>>> chessBoard;
    std::vector<Player> players;
    unsigned int turnIndex;
};
