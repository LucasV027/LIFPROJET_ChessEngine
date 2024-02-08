#include "Player.h"

Player::Player(std::string _playerName, unsigned int _playerIndex, Direction _playerDirection, Color _playerColor) : playerName(_playerName),
                                                                                                                     playerIndex(_playerIndex),
                                                                                                                     playerDirection(_playerDirection),
                                                                                                                     playerColor(_playerColor),
                                                                                                                     isAlive(true) {}

Player::Player(std::string _playerName, unsigned int _playerIndex, Direction _playerDirection, Vec3Int _playerColor) : playerName(_playerName),
                                                                                                                       playerIndex(_playerIndex),
                                                                                                                       playerDirection(_playerDirection),
                                                                                                                       playerColor(_playerColor),
                                                                                                                       isAlive(true) {}

bool Player::operator==(const Player &other) const
{
    return (this->isAlive == other.isAlive) &&
           (this->playerColor == other.playerColor) &&
           (this->playerDirection == other.playerDirection) &&
           (this->playerName == other.playerName) &&
           (this->playerIndex == other.playerIndex);
}

bool Player::operator!=(const Player &other) const
{
    return !(*this == other);
}

void Player::print() const
{
    std::cout << "Name : " << this->playerName << " | Index : " << this->playerIndex << "\n";
}
