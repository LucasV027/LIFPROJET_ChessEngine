#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../Utils/Utils.h"
#include "ChessPiece.h"

class Player
{
public:
    // Constructors
    Player(std::string _playerName, unsigned int _playerIndex, Direction _playerDirection, Color _playerColor);
    Player(std::string _playerName, unsigned int _playerIndex, Direction _playerDirection, Color _playerColor, bool _isAlive);
    Player(std::string _playerName, unsigned int _playerIndex, Direction _playerDirection, Vec3Int _playerColor);
    Player(std::string _playerName, unsigned int _playerIndex, Direction _playerDirection, Vec3Int _playerColor, bool _isAlive);

    // Operators
    bool operator==(const Player &other) const;
    bool operator!=(const Player &other) const;

    // Debug
    void print() const;

public:
    std::string playerName;
    int playerIndex;

    Vec2Int playerDirection;
    Vec3Int playerColor;
    bool isAlive;
};
