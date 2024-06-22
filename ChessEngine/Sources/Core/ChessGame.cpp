#include "Core/ChessGame.h"

ChessGame::ChessGame() : ChessGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w") {}

ChessGame::ChessGame(const std::vector<std::string> &terrain, const std::vector<Player> &players, int _turnIndex)
{

    this->players = players;

    turnIndex = _turnIndex;
    int numCharOfACase = 3; // 3 chars are representing a single case

    // Rezising the chessboard std::vector (to be the same size as the terrain)
    chessBoard.resize(terrain.size());
    for (size_t y = 0; y < terrain.size(); ++y)
        chessBoard[y].resize((terrain[0].size() + 1) / numCharOfACase);

    // Setting all the pieces on the board
    for (size_t y = 0; y < terrain.size(); y++)
    {
        for (size_t x = 0; x < chessBoard[y].size(); x++)
        {
            PieceType pt = charToPieceType(terrain[y][x * numCharOfACase]);
            int playerIndex = (pt != PieceType::NONE ? terrain[y][(x * numCharOfACase) + 1] - '0' : -1);
            bool hasAlreadyMove = (terrain[y][(x * numCharOfACase) + 2] != ' ');

            chessBoard[y][x] = ChessPiece(pt, x, y, playerIndex);
        }
    }
}

ChessGame::ChessGame(const std::string &FEN)
{

    players.push_back(Player("W0", 0, Direction::North, Color::White));
    players.push_back(Player("B1", 1, Direction::South, Color::Black));

    // 1 - Chessboard

    int height = 1;
    for (size_t i = 0; i < FEN.size(); i++)
    {
        if (FEN[i] == '/')
            height++;
    }

    int witdth = 0;
    size_t index = 0;

    while (FEN[index] != '/')
    {
        if (std::isdigit(FEN[index]))
            witdth += (int)(FEN[index] - '0');
        else
            witdth++;
        index++;
    }

    chessBoard.resize(height);
    for (size_t y = 0; y < height; ++y)
        chessBoard[y].resize(witdth);

    index = 0;
    int x = 0;
    int y = 0;

    while (FEN[index] != ' ')
    {
        char c = FEN[index];

        if (std::isdigit(c))
        {
            int emptyCaseNumber = c - '0';

            for (size_t i = 0; i < emptyCaseNumber; i++)
            {
                chessBoard[y][x] = ChessPiece(PieceType::NONE, x, y, -1);
                x++;
            }
        }
        else if (c == '/')
        {
            y++;
            x = 0;
        }
        else
        {
            bool hasMovedOnce = true;

            if (height == 8 && witdth == 8) // If we are in a regular game (8 by 8)
            {
                // The is upper verification to prevent the case where a white pawn being at the place of a blackpawn or inverse
                if ((y == 1 && !std::isupper(c)) || (y == 6 && std::isupper(c))) // To allow pawn moving 2 when they are in an allowed position two (2nd line or 5th line)
                {
                    hasMovedOnce = false;
                }
            }

            chessBoard[y][x] = ChessPiece(charToPieceType(c), x, y, (std::isupper(c) ? 0 : 1), hasMovedOnce); // White pieces are majs & black are mins
            x++;
        }
        index++;
    }
    //

    // 2 - Color to play
    index++;
    turnIndex = (FEN[index] == 'w' ? 0 : 1);
    //
}

size_t ChessGame::getHeight() const { return (chessBoard.size()); }
size_t ChessGame::getWidth() const { return (chessBoard[0].size()); }

bool ChessGame::isOver() const
{
    int remainingPlayers = 0;
    for (const auto &p : players)
    {
        if (p.isAlive)
        {
            remainingPlayers++;
        }
    }

    return (remainingPlayers < 2);
}

std::string ChessGame::toFENString() const
{
    std::string ret;

    int sumEmptyCase = 0;
    for (size_t y = 0; y < this->getHeight(); y++)
    {
        for (size_t x = 0; x < this->getWidth(); x++)
        {
            if (this->chessBoard[y][x].caseType == PieceType::NONE)
            {
                sumEmptyCase++;
            }
            else
            {
                if (sumEmptyCase > 0)
                {
                    ret += std::to_string(sumEmptyCase);
                    sumEmptyCase = 0;
                }
                ret += toChar(this->chessBoard[y][x].caseType, this->chessBoard[y][x].playerIndex);
            }
        }

        if (sumEmptyCase > 0)
        {
            ret += std::to_string(sumEmptyCase);
            sumEmptyCase = 0;
        }

        if (y < this->getWidth() - 1)
        {
            ret += '/';
        }
    }

    ret += ' ';
    ret += (this->turnIndex == 0 ? 'w' : 'b');

    return ret;
}

bool ChessGame::isItAITurns() const { players[turnIndex].playerName == "IA"; }

const std::vector<Move> ChessGame::getAllPossibleMoves() const
{
    std::vector<Move> res;
    res.reserve(40); // Arbitrairy number (Move generation is usually around 20 to 30 so we take 40 we will never need to resize the vector)

    for (const std::vector<ChessPiece> &row : chessBoard)
        for (const ChessPiece &piece : row)
        {
            if (piece && piece.playerIndex == turnIndex)
            {
                piece.returnValidMoves(*this, res);
            }
        }

    return res;
}

bool ChessGame::makeAMove(Move move, bool verifications)
{
    MoveType recoverMoveType = MoveType::NONE;

    if (verifications)
    {
        if (chessBoard[move.from.y][move.from.x].playerIndex != turnIndex)
            return false;

        recoverMoveType = isMoveAllowed(chessBoard[move.from.y][move.from.x], move.to);

        if (recoverMoveType == MoveType::NONE)
        {
            return false;
        }
    }

    // Saving pieces before moving
    moveHistory.push_front(SavedMove(chessBoard[move.from.y][move.from.x], chessBoard[move.to.y][move.to.x], move.moveType));

    // If we did proceed to verifications then we need to use the recovered moveType
    // Else the move comes directly from the vector of moves so we already have his moveType
    didWeCaptureTheKing(move.to, (verifications ? recoverMoveType : move.moveType));

    moveAPiece(move.from, move.to);

    // Same thing for the recovered moveType than in didWeCaptureTheKing
    handleSpecialMoves(move.from, move.to, (verifications ? recoverMoveType : move.moveType));

    updatePlayerTurn(1);
}

void ChessGame::undoMove()
{
    if (moveHistory.empty())
        return;

    ChessPiece savedFrom = moveHistory.front().savedFrom;
    ChessPiece savedTo = moveHistory.front().savedTo;
    // MoveType saveMoveType = moveHistory.front().moveType;

    chessBoard[savedFrom.y][savedFrom.x] = savedFrom;
    chessBoard[savedTo.y][savedTo.x] = savedTo;

    updatePlayerTurn(-1);

    // We could put this in a function like undoSpecialMoves() but we have only one case for now so its kinda useless
    if (savedTo.caseType == PieceType::KING) // Undoing capturing the king
    {
        players[savedTo.playerIndex].isAlive = true;
    }

    moveHistory.pop_front();
}

void ChessGame::handleSpecialMoves(Vec2Int from, Vec2Int to, MoveType _moveType)
{
    // For now we use a if statement because its quicker but we could update it to a switch statement if we have more special moves
    if (_moveType == MoveType::PROMOTION || _moveType == MoveType::CAPTURE_PROMOTION) // To check if a pawn reaches the end
    {
        chessBoard[to.y][to.x].caseType = PieceType::QUEEN;
    }
}

MoveType ChessGame::isMoveAllowed(ChessPiece piece, Vec2Int move) const
{
    std::vector<Move> moves;
    piece.returnValidMoves(*this, moves);
    for (const Move &moveAllowed : moves)
    {
        if (moveAllowed.to == move)
        {
            return moveAllowed.moveType;
        }
    }
    return MoveType::NONE;
}

void ChessGame::moveAPiece(Vec2Int from, Vec2Int to)
{
    ChessPiece &oldPos = chessBoard[from.y][from.x];
    ChessPiece &newPos = chessBoard[to.y][to.x];

    newPos = oldPos;
    newPos.x = to.x;
    newPos.y = to.y;

    oldPos = ChessPiece(PieceType::NONE, oldPos.x, oldPos.y, -1);

    newPos.moved();
}

void ChessGame::didWeCaptureTheKing(Vec2Int to, MoveType _moveType)
{
    if (_moveType == MoveType::CAPTURE || _moveType == MoveType::CAPTURE_PROMOTION) // We only check if its a capture
    {
        if (chessBoard[to.y][to.x].caseType == PieceType::KING) // If its a king :
        {
            players[chessBoard[to.y][to.x].playerIndex].isAlive = false; // We make the player of this king stop playing
        }
    }
}

void ChessGame::randomMove()
{
    std::vector<Move> moves = this->getAllPossibleMoves();
    if (moves.size() == 0)
        return;

    srand(time(NULL));
    int randMove = rand() % moves.size();
    auto move = moves[randMove];
    this->makeAMove(move, false);
}

void ChessGame::updatePlayerTurn(int amount)
{
    do
    {
        turnIndex += amount;
        turnIndex = turnIndex % players.size();

    } while (!players[turnIndex].isAlive); // The while loop is cause of the multiples players, we basically turn the player index 1 by 1 until one is valid to play
}

void ChessGame::print() const
{
    for (size_t i = 0; i < this->getWidth(); i++)
        std::cout << "--";
    std::cout << "\n";

    for (const std::vector<ChessPiece> &row : chessBoard)
    {
        for (const ChessPiece &chessCase : row)
        {
            if (chessCase)
                chessCase.print();
            else
                std::cout << "  ";
        }
        std::cout << "\n";
    }

    for (size_t i = 0; i < this->getWidth(); i++)
        std::cout << "--";

    std::cout << "\n";
}

void ChessGame::printAll() const
{
    this->print();

    for (const Player &player : this->players)
        player.print();
}

void ChessGame::printPieceInfos(int x, int y) const
{
    if (ChessPiece piece = chessBoard[y][x])
    {
        piece.printInfos();
        std::cout << std::endl;
    }
    else
        std::cout << "No piece at (" << x << ";" << y << ")" << std::endl;
}
