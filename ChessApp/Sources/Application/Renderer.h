#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <vector>

#include "Utils/Utils.h"
#include "Core/ChessPiece.h"
#include "Core/ChessGame.h"
#include "Box.h"


class Renderer
{
public:
    Renderer(SDL_Window *window);
    ~Renderer();

    Box getChessBoardBox() const;
    int getSquareSizeX() const;
    int getSquareSizeY() const;

    void setAPieceToDrawPossibleMoves(const ChessPiece &piece);
    void resize(int newScreenX, int newScreenY, const ChessGame &game);
    void display(const ChessGame &game);

private:
    void drawBackground(const ChessGame &game);
    void drawGrid(const ChessGame &game);
    void drawPieces(const ChessGame &game);
    void drawPossibleMoves(const ChessGame &game);
    void drawColorToPlay(const ChessGame &game);

    Box chessBoardBox;
    int squareSizeX;
    int squareSizeY;

private:
    ChessPiece pieceToDrawPossibleMoves;

    SDL_Renderer *mRenderer = nullptr;

    SDL_Texture *circleTexture;
    SDL_Texture *circleOnPieceTexture;
    SDL_Texture *chessPiecesTexture;

    int spriteSizeY;
    int spriteSizeX;
    SDL_Rect pawnSprite;
    SDL_Rect rookSprite;
    SDL_Rect knightSprite;
    SDL_Rect bishopSprite;
    SDL_Rect queenSprite;
    SDL_Rect kingSprite;
};
