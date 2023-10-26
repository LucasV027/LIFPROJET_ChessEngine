#include "renderer.h"

Renderer::Renderer(SDL_Window *window) : chessBoardBox(0.f, 0.f, 0.f, 0.f, 800, 800)
{
    mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!mRenderer)
    {
        printf("mRenderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    pawnTexture = IMG_LoadTexture(mRenderer, "data/Pawn.png");
    textures.push_back(pawnTexture);

    knightTexture = IMG_LoadTexture(mRenderer, "data/Knight.png");
    textures.push_back(knightTexture);

    bishopTexture = IMG_LoadTexture(mRenderer, "data/Bishop.png");
    textures.push_back(bishopTexture);

    rookTexture = IMG_LoadTexture(mRenderer, "data/Rook.png");
    textures.push_back(rookTexture);

    queenTexture = IMG_LoadTexture(mRenderer, "data/Queen.png");
    textures.push_back(queenTexture);

    kingTexture = IMG_LoadTexture(mRenderer, "data/King.png");
    textures.push_back(kingTexture);
}

void Renderer::resize(int new_screen_x, int new_screen_y, const ChessGame &ChessGame)
{
    chessBoardBox.resize(new_screen_x, new_screen_y);
    squareSizeX = chessBoardBox.getWidth() / ChessGame.getWidth();
    squareSizeY = chessBoardBox.getHeight() / ChessGame.getHeight();
}

void Renderer::drawBackground()
{
    SDL_Rect rect;
    rect.x = chessBoardBox.getXOffset();
    rect.y = chessBoardBox.getYOffset();
    rect.w = chessBoardBox.getWidth();
    rect.h = chessBoardBox.getHeight();
    SDL_SetRenderDrawColor(mRenderer, 119, 149, 86, 255);
    SDL_RenderFillRect(mRenderer, &rect);
}

void Renderer::drawGrid(const ChessGame &ChessGame)
{
    SDL_Rect rect;

    SDL_SetRenderDrawColor(mRenderer, 235, 236, 208, 25);
    for (int y = 0; y < ChessGame.getHeight(); y++)
    {
        for (int x = 0; x < ChessGame.getWidth(); x++)
        {
            if ((x + y) % 2)
            {
                rect.x = chessBoardBox.getXOffset() + x * (chessBoardBox.getWidth() / ChessGame.getWidth());
                rect.y = chessBoardBox.getYOffset() + y * (chessBoardBox.getHeight() / ChessGame.getHeight());
                rect.w = squareSizeX;
                rect.h = squareSizeY;

                SDL_RenderFillRect(mRenderer, &rect);
            }
        }
    }
}

/*
void Renderer::drawPossibleMoves(const ChessGame &ChessGame)
{
    if (ChessGame.selectedPiece && !ChessGame.selectedPiece->possibleMoves.empty())
    {
        SDL_Rect rect;
        for (const auto &move : ChessGame.selectedPiece->possibleMoves)
        {
            SDL_SetRenderDrawColor(mRenderer, 100, 100, 100, 255);
            rect.x = chessBoardBox.getXOffset() + move.x * (chessBoardBox.getWidth()() / ChessGame.getWidth());
            rect.y = chessBoardBox.getYOffset() + move.y * (chessBoardBox.getHeight() / ChessGame.getHeight());
            rect.w = squareSizeX;
            rect.h = squareSizeY;
            SDL_RenderFillRect(mRenderer, &rect);
        }
    }
}*/

void Renderer::drawPieces(const ChessGame &ChessGame)
{
    SDL_Rect rect;

    for (const auto &row : ChessGame.getChessBoard())
    {
        for (const auto &_case : row)
        {
            if (_case.has_value())
            {
                rect.x = chessBoardBox.getXOffset() + (_case->getPostionX() * squareSizeX);
                rect.y = chessBoardBox.getYOffset() + (_case->getPostionY() * squareSizeY);
                rect.w = chessBoardBox.getWidth() / ChessGame.getWidth();
                rect.h = chessBoardBox.getHeight() / ChessGame.getWidth();

                Vec3Int color = ChessGame.getPlayer(_case->getPlayerIndex()).playerColor;
                SDL_SetTextureColorMod(textures[_case->getTextureIndex()], color.r, color.g, color.b);

                SDL_RenderCopy(mRenderer, textures[_case->getTextureIndex()], NULL, &rect);
            }
        }
    }
}

void Renderer::drawColorToPlay(const ChessGame &ChessGame)
{
    SDL_Rect rect;
    rect.x = chessBoardBox.getXOffset() + chessBoardBox.getWidth() + 10;
    rect.y = chessBoardBox.getYOffset() - 10;
    rect.w = 30;
    rect.h = 30;
    SDL_SetRenderDrawColor(mRenderer, 115, 115, 115, 255);
    SDL_RenderFillRect(mRenderer, &rect);

    rect.x = chessBoardBox.getXOffset() + chessBoardBox.getWidth() + 15;
    rect.y = chessBoardBox.getYOffset() - 5;
    rect.w = 20;
    rect.h = 20;
    Vec3Int color = ChessGame.getPlayer(ChessGame.getTurn()).playerColor;
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(mRenderer, &rect);
}

void Renderer::display(const ChessGame &ChessGame)
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    drawBackground();
    drawGrid(ChessGame);
    // drawPossibleMoves(ChessGame);
    drawPieces(ChessGame);
    drawColorToPlay(ChessGame);

    SDL_RenderPresent(mRenderer);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(mRenderer);
    for (auto &texture : textures)
    {
        SDL_DestroyTexture(texture);
    }
}
