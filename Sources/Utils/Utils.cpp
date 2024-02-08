#include "Utils.h"
#include "../Core/ChessPiece.h"

PieceType charToPieceType(char c)
{
    PieceType ret;

    switch (c)
    {
    case 'p':
    case 'P':
        ret = PieceType::PAWN;
        break;

    case 'r':
    case 'R':
        ret = PieceType::ROOK;
        break;

    case 'n':
    case 'N':
        ret = PieceType::KNIGHT;
        break;

    case 'b':
    case 'B':
        ret = PieceType::BISHOP;
        break;

    case 'q':
    case 'Q':
        ret = PieceType::QUEEN;
        break;

    case 'k':
    case 'K':
        ret = PieceType::KING;
        break;

    default:
        ret = PieceType::NONE;
        break;
    }

    return ret;
}

void printDirection(Direction d)
{
    switch (d)
    {
    case Direction::North:
        std::cout << "North";
        break;
    case Direction::South:
        std::cout << "South";
        break;
    case Direction::West:
        std::cout << "West";
        break;
    case Direction::Est:
        std::cout << "Est";
        break;
    default:
        std::cout << "None";
    }
}

char toChar(PieceType pt, int playerindex)
{
    char c = ' ';

    switch (pt)
    {
    case PieceType::PAWN:
        c = 'p';
        break;

    case PieceType::ROOK:
        c = 'r';
        break;

    case PieceType::KNIGHT:
        c = 'n';
        break;

    case PieceType::BISHOP:
        c = 'b';
        break;

    case PieceType::QUEEN:
        c = 'q';
        break;

    case PieceType::KING:
        c = 'k';
        break;

    default:
        break;
    }

    return (playerindex == 0 ? std::toupper(c) : std::tolower(c));
}

void printColor(Color c)
{
    switch (c)
    {
    case Color::Black:
        std::cout << "Black";
        break;
    case Color::White:
        std::cout << "White";
        break;
    case Color::Blue:
        std::cout << "Blue";
        break;
    case Color::Red:
        std::cout << "Red";
        break;
    case Color::None:
        std::cout << "None";
        break;
    default:
        std::cout << "UNKNOWN";
    }
}

///////////////////////////////////////////////// Vec2Int /////////////////////////////////////////////////

Vec2Int::Vec2Int() : x(0), y(0) {}
Vec2Int::Vec2Int(int _x, int _y) : x(_x), y(_y) {}
Vec2Int::Vec2Int(Direction d)
{
    switch (d)
    {
    case Direction::North:
        x = 0;
        y = 1;
        break;

    case Direction::South:
        x = 0;
        y = -1;
        break;

    case Direction::Est:
        x = 1;
        y = 0;
        break;

    case Direction::West:
        x = -1;
        y = 0;
        break;

    default: // Should not happen abritral values
        x = -7;
        y = -7;
        break;
    }
}

bool Vec2Int::operator==(const Vec2Int &other) const
{
    return x == other.x && y == other.y;
}

bool Vec2Int::operator!=(const Vec2Int &other) const
{
    return x != other.x || y != other.y;
}

Vec2Int Vec2Int::operator-(const Vec2Int &other) const
{
    Vec2Int result;
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    return result;
}

int Vec2Int::length() const { return sqrt(pow(x, 2) + pow(y, 2)); }

void Vec2Int::print() const
{
    std::cout << "(" << x << ";" << y << ")" << std::flush;
}

///////////////////////////////////////////////// Move /////////////////////////////////////////////////

Move::Move() : from(Vec2Int(0, 0)), to(Vec2Int(0, 0)), moveType(MoveType::NONE) {}
Move::Move(Vec2Int _from, Vec2Int _to, MoveType _moveType) : from(_from), to(_to), moveType(_moveType) {}
Move::Move(int x0, int y0, int x1, int y1, MoveType _moveType) : from(Vec2Int(x0, y0)), to(Vec2Int(x1, y1)), moveType(_moveType) {}

///////////////////////////////////////////////// Vec3Int /////////////////////////////////////////////////

Vec3Int::Vec3Int() : r(0), g(0), b(0) {}
Vec3Int::Vec3Int(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

Vec3Int::Vec3Int(Color c)
{
    switch (c)
    {
    case Color::Black:
        r = 0;
        g = 0;
        b = 0;
        break;
    case Color::White:
        r = 255;
        g = 255;
        b = 255;
        break;
    case Color::Blue:
        r = 0;
        g = 0;
        b = 255;
        break;
    case Color::Red:
        r = 255;
        g = 0;
        b = 0;
        break;

    case Color::Yellow:
        r = 255;
        g = 255;
        b = 0;
        break;

    case Color::Green:
        r = 0;
        g = 255;
        b = 0;
        break;

    default:
        r = 0;
        g = 0;
        b = 0;
        break;
    }
}

bool Vec3Int::operator==(const Vec3Int &other) const { return (this->r == other.r && this->g == other.g && this->r == other.r); }

bool Vec3Int::operator!=(const Vec3Int &other) const
{
    return !(this->r != other.r && this->g != other.g && this->b != other.b);
}

void Vec3Int::print() const { std::cout << this->r << " " << this->g << " " << this->b; }

///////////////////////////////////////////////// Vec4Int /////////////////////////////////////////////////

Vec4Int::Vec4Int() : x1(0), y1(0), x2(0), y2(0) {}

Vec4Int::Vec4Int(int _x1, int _y1, int _x2, int _y2)
    : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

Vec4Int::Vec4Int(const Vec4Int &other)
    : x1(other.x1), y1(other.y1), x2(other.x2), y2(other.y2) {}

Vec2Int Vec4Int::getFrom() const
{
    return {x1, y1};
}

Vec2Int Vec4Int::getTo() const
{
    return {x2, y2};
}

void Vec4Int::print() const
{
    std::cout << "(" << x1 << ";" << y1 << "|" << x2 << ";" << y2 << ")" << std::flush;
}

bool validFEN(std::string s)
{
    return true;

    std::string{"20/20/20/p19"};
}
