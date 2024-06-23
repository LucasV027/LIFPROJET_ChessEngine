#include "Renderer.h"

Renderer::Renderer(SDL_Window *window) : chessBoardBox(0.1f, 0.1f, 0.1f, 0.1f, 800, 800)
{
    mRenderer = SDL_CreateRenderer(window, NULL);
    if (!mRenderer)
        printf("mRenderer could not be created! SDL_Error: %s\n", SDL_GetError());

    chessPiecesTexture = IMG_LoadTexture(mRenderer, ASSETS_PATH "/Textures/chess.png");
    if (!chessPiecesTexture)
        printf("The renderer could not load Assets/Textures/chess.png ! SDL_Error: %s\n", SDL_GetError());

    circleTexture = IMG_LoadTexture(mRenderer, ASSETS_PATH "/Textures/Circle.png");
    if (!circleTexture)
        printf("The renderer could not load Assets/Textures/Circle.png ! SDL_Error: %s\n", SDL_GetError());

    circleOnPieceTexture = IMG_LoadTexture(mRenderer, ASSETS_PATH "/Textures/CircleOnPiece.png");
    if (!circleOnPieceTexture)
        printf("The renderer could not load Assets/Textures/CircleOnPiece.png ! SDL_Error: %s\n", SDL_GetError());

    float chessPiecesTextureWidth, chessPiecesTextureHeight;
    SDL_GetTextureSize(chessPiecesTexture, &chessPiecesTextureWidth, &chessPiecesTextureHeight);
    spriteSizeY = chessPiecesTextureHeight / 2;
    spriteSizeX = chessPiecesTextureWidth / 6;

    pawnSprite = SDL_FRect{0, 0, (float)spriteSizeX, (float)spriteSizeY};
    rookSprite = SDL_FRect{(float)spriteSizeX * 3, 0, (float)spriteSizeX, (float)spriteSizeY};
    knightSprite = SDL_FRect{(float)spriteSizeX, 0, (float)spriteSizeX, (float)spriteSizeY};
    bishopSprite = SDL_FRect{(float)spriteSizeX * 2, 0, (float)spriteSizeX, (float)spriteSizeY};
    queenSprite = SDL_FRect{(float)spriteSizeX * 4, 0, (float)spriteSizeX, (float)spriteSizeY};
    kingSprite = SDL_FRect{(float)spriteSizeX * 5, 0, (float)spriteSizeX, (float)spriteSizeY};
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(mRenderer);

    SDL_DestroyTexture(chessPiecesTexture);
    SDL_DestroyTexture(circleOnPieceTexture);
    SDL_DestroyTexture(circleTexture);
}

Box Renderer::getChessBoardBox() const { return chessBoardBox; }
int Renderer::getSquareSizeX() const { return squareSizeX; }
int Renderer::getSquareSizeY() const { return squareSizeY; }

void Renderer::setAPieceToDrawPossibleMoves(const ChessPiece &piece) { pieceToDrawPossibleMoves = piece; }

void Renderer::resize(int new_screen_x, int new_screen_y, const ChessGame &game)
{
    chessBoardBox.resize(new_screen_x, new_screen_y);
    squareSizeX = chessBoardBox.getWidth() / game.getWidth();
    squareSizeY = chessBoardBox.getHeight() / game.getHeight();
}

void Renderer::display(const ChessGame &game)
{
    SDL_SetRenderDrawColor(mRenderer, 48, 46, 43, 255);
    SDL_RenderClear(mRenderer);

    drawBackground(game);
    drawGrid(game);
    drawPossibleMoves(game);
    drawPieces(game);
    drawColorToPlay(game);

    SDL_RenderPresent(mRenderer);
}

void Renderer::drawBackground(const ChessGame &game)
{
    SDL_FRect rect;
    rect.x = chessBoardBox.getXOffset();
    rect.y = chessBoardBox.getYOffset();
    rect.w = squareSizeX * game.getWidth();
    rect.h = squareSizeY * game.getHeight();
    SDL_SetRenderDrawColor(mRenderer, 119, 149, 86, 255);
    SDL_RenderFillRect(mRenderer, &rect);
}

void Renderer::drawGrid(const ChessGame &game)
{
    SDL_FRect rect;

    SDL_SetRenderDrawColor(mRenderer, 235, 236, 208, 25);
    for (size_t y = 0; y < game.getHeight(); y++)
    {
        for (size_t x = 0; x < game.getWidth(); x++)
        {
            if ((x + y) % 2)
            {
                rect.x = chessBoardBox.getXOffset() + x * (chessBoardBox.getWidth() / game.getWidth());
                rect.y = chessBoardBox.getYOffset() + y * (chessBoardBox.getHeight() / game.getHeight());
                rect.w = squareSizeX;
                rect.h = squareSizeY;

                SDL_RenderFillRect(mRenderer, &rect);
            }
        }
    }
}

void Renderer::drawPossibleMoves(const ChessGame &game)
{
    if (pieceToDrawPossibleMoves)
    {
        // Draw the colored square under the piece that we selected
        SDL_FRect rect;
        rect.x = chessBoardBox.getXOffset() + (pieceToDrawPossibleMoves.x * squareSizeX);
        rect.y = chessBoardBox.getYOffset() + (pieceToDrawPossibleMoves.y * squareSizeY);
        rect.w = chessBoardBox.getWidth() / game.getWidth();
        rect.h = chessBoardBox.getHeight() / game.getWidth();
        SDL_SetRenderDrawColor(mRenderer, 176, 213, 230, 0); // Light blue
        SDL_RenderFillRect(mRenderer, &rect);

        // Draw possible moves for all the pieces
        std::vector<Move> movesForAPieces;
        pieceToDrawPossibleMoves.returnValidMoves(game, movesForAPieces);
        for (const Move &move : movesForAPieces)
        {
            SDL_FRect rect;
            if (game.chessBoard[move.to.y][move.to.x]) // There is a piece one the "to" of the move so we take the circle png
            {
                rect.x = chessBoardBox.getXOffset() + move.to.x * (chessBoardBox.getWidth() / game.getWidth());
                rect.y = chessBoardBox.getYOffset() + move.to.y * (chessBoardBox.getHeight() / game.getHeight());
                rect.w = squareSizeX;
                rect.h = squareSizeY;
                SDL_RenderTexture(mRenderer, circleOnPieceTexture, NULL, &rect);
            }
            else // The is no pieces so we draw the transparent circle
            {
                rect.x = chessBoardBox.getXOffset() + move.to.x * (chessBoardBox.getWidth() / game.getWidth()) + (squareSizeX / 2) - (squareSizeX / (2 * 2.5));
                rect.y = chessBoardBox.getYOffset() + move.to.y * (chessBoardBox.getHeight() / game.getHeight()) + (squareSizeY / 2) - (squareSizeY / (2 * 2.5));
                rect.w = squareSizeX / 2.5;
                rect.h = squareSizeY / 2.5;
                SDL_RenderTexture(mRenderer, circleTexture, NULL, &rect);
            }
        }
    }
}

void Renderer::drawPieces(const ChessGame &game)
{
    SDL_FRect rect;

    for (const auto &pieces : game.chessBoard)
    {
        for (const auto &piece : pieces)
        {
            if (piece)
            {
                rect.x = chessBoardBox.getXOffset() + (piece.x * squareSizeX);
                rect.y = chessBoardBox.getYOffset() + (piece.y * squareSizeY);
                rect.w = chessBoardBox.getWidth() / game.getWidth();
                rect.h = chessBoardBox.getHeight() / game.getWidth();

                SDL_FRect sprite;

                switch (piece.caseType)
                {
                case PieceType::PAWN:
                    sprite = pawnSprite;
                    break;
                case PieceType::KNIGHT:
                    sprite = knightSprite;
                    break;
                case PieceType::BISHOP:
                    sprite = bishopSprite;
                    break;
                case PieceType::ROOK:
                    sprite = rookSprite;
                    break;
                case PieceType::QUEEN:
                    sprite = queenSprite;
                    break;
                case PieceType::KING:
                    sprite = kingSprite;
                    break;

                default:
                    sprite = bishopSprite;
                    break;
                }

                Vec3Int pieceColor = game.players[piece.playerIndex].playerColor;
                bool aliveStatus = game.players[piece.playerIndex].isAlive;

                if (aliveStatus)
                {
                    SDL_SetTextureColorMod(chessPiecesTexture, 255, 255, 255); // Reseting

                    if (pieceColor == Vec3Int(Color::White))
                    {
                        sprite.y = (float)spriteSizeY;
                    }

                    if ((pieceColor != Vec3Int(Color::Black)) && (pieceColor != Vec3Int(Color::White)))
                    {
                        sprite.y = (float)spriteSizeY;
                        SDL_SetTextureColorMod(chessPiecesTexture, pieceColor.r, pieceColor.g, pieceColor.b);
                    }
                }
                else
                {
                    SDL_SetTextureColorMod(chessPiecesTexture, 35, 35, 0);
                }

                SDL_RenderTexture(mRenderer, chessPiecesTexture, &sprite, &rect);
            }
        }
    }
}

void Renderer::drawColorToPlay(const ChessGame &game)
{
    SDL_FRect rect;
    rect.x = chessBoardBox.getXOffset() + chessBoardBox.getWidth() + 10;
    rect.y = chessBoardBox.getYOffset() - 10;
    rect.w = 30;
    rect.h = 30;
    SDL_SetRenderDrawColor(mRenderer, 38, 37, 34, 255);
    SDL_RenderFillRect(mRenderer, &rect);

    rect.x = chessBoardBox.getXOffset() + chessBoardBox.getWidth() + 15;
    rect.y = chessBoardBox.getYOffset() - 5;
    rect.w = 20;
    rect.h = 20;
    Vec3Int piece_color(game.players[game.turnIndex].playerColor);
    SDL_SetRenderDrawColor(mRenderer, piece_color.r, piece_color.g, piece_color.b, 255);
    SDL_RenderFillRect(mRenderer, &rect);
}
