#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <iostream>

#include "utils.h"
#include "chesspiece.h"
#include "chessgame.h"
#include "box.h"

class Renderer
{
public:
    Renderer(SDL_Window *window);

    void resize(int newScreenX, int newScreenY, const ChessGame &ChessGame);

    void display(const ChessGame &ChessGame);

    ~Renderer();

private:
    void drawBackground();
    void drawGrid(const ChessGame &ChessGame);
    void drawPieces(const ChessGame &ChessGame);
  //  void drawPossibleMoves(const ChessGame &ChessGame);
    void drawColorToPlay(const ChessGame &ChessGame);

public:
    Box chessBoardBox;
    int squareSizeX;
    int squareSizeY;

private:
    SDL_Renderer *mRenderer = nullptr;

    std::vector<SDL_Texture *> textures;

    SDL_Texture *pawnTexture = nullptr;
    SDL_Texture *knightTexture = nullptr;
    SDL_Texture *bishopTexture = nullptr;
    SDL_Texture *rookTexture = nullptr;
    SDL_Texture *queenTexture = nullptr;
    SDL_Texture *kingTexture = nullptr;
};
