#include "chessgame.h"

Player::Player(unsigned int index, std::string name, Direction dir, Color col) : playerIndex(index),
                                                                                 playerName(name),
                                                                                 playerDirection(dir),
                                                                                 playerColor(col)
{
}

const std::vector<std::vector<std::optional<ChessPiece>>> &ChessGame::getChessBoard() const { return chessBoard; }
unsigned int ChessGame::getWidth() const { return chessBoard[0].size(); }
unsigned int ChessGame::getHeight() const { return chessBoard.size(); }

std::optional<ChessPiece> ChessGame::getElement(int y, int x) const { return chessBoard[y][x]; }
void ChessGame::setElement(int y, int x, ChessPiece val) { chessBoard[y][x] = val; }

const std::vector<Player> &ChessGame::getPlayersVector() const { return players; }
unsigned int ChessGame::getPlayersNumber() const { return players.size(); }
Player ChessGame::getPlayer(int index) const { return players[index]; }
void ChessGame::setPlayer(int index, Player p) { players[index] = p; }

unsigned int ChessGame::getTurn() const { return turnIndex; }

ChessGame::ChessGame()
{
    const std::vector<std::string> terrain = {
        "R1 N1 B1 Q1 K1 B1 N1 R1",
        "P1 P1 P1 P1 P1 P1 P1 P1",
        "__ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __",
        "P0 P0 P0 P0 P0 P0 P0 P0",
        "R0 N0 B0 Q0 K0 B0 N0 R0"};

    int numCharOfACase = 3; // 3 chars are representing a single case

    players.push_back(Player(0, "J1", Direction::North, Color::Black));
    players.push_back(Player(1, "J2", Direction::South, Color::White));

    // Rezising the chessboard std::vector (to be the same size as the terrain)
    chessBoard.resize(terrain.size());
    for (int y = 0; y < terrain.size(); ++y)
        chessBoard[y].resize((terrain[0].size() + 1) / numCharOfACase);

    // Values assignment
    for (int y = 0; y < terrain.size(); y++)
    {
        for (int x = 0; x < terrain[y].size(); x++)
        {
            char p = terrain[y][x * 3];
            int playerIndex = terrain[y][(x * 3) + 1] - '0';

            switch (p)
            {
            case 'P':
                chessBoard[y][x] = std::optional(Pawn(x, y, playerIndex));
                break;

            case 'N':
                chessBoard[y][x] = std::optional(Knight(x, y, playerIndex));
                break;

            case 'B':
                chessBoard[y][x] = std::optional(Bishop(x, y, playerIndex));
                break;

            case 'R':
                chessBoard[y][x] = std::optional(Rook(x, y, playerIndex));
                break;

            case 'Q':
                chessBoard[y][x] = std::optional(Queen(x, y, playerIndex));
                break;

            case 'K':
                chessBoard[y][x] = std::optional(King(x, y, playerIndex));
                break;

            default:
                chessBoard[y][x] = std::nullopt;
                break;
            }
        }
    }

    // setAllValidMoves();
}

int ChessGame::setAllValidMoves()
{
    int sum = 0;

    for (auto &row : chessBoard)
        for (auto &chessCase : row)
        {
            if (chessCase.has_value())
            {
                if (chessCase->getPlayerIndex() == turnIndex)
                {
                    sum++;
                    chessCase->setValidMoves(*this);
                }
            }
        }

    return sum;
}

void ChessGame::clearAllMoves()
{
    for (auto &row : chessBoard)
        for (auto &chessCase : row)
        {
            if (chessCase.has_value())
            {
                if (chessCase->getPlayerIndex() == turnIndex)
                {
                    chessCase->getPossibleMoves().clear();
                }
            }
        }
}