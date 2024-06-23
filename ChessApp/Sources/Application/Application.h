#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <iostream>

// Only for the demo
#include "Utils/Demo.h"
/////////////////

#include "IA/ChessIA.h"
#include "Renderer.h"

enum class Events
{
    NONE,
    NEW_GAME,
    IAS_TURN,
    EVALUATION,
    RANDOM_MOVE,
    HUMAN_CLICK,
    UNDO_LAST_MOVE,
    MAKE_IA_CHESSMOVE,
    DISPLAY_FEN_STRING,
    COUNT_SUB_POSITIONS,
    COUNT_POSSIBLE_MOVES,
};

class Application
{
public:
    Application(int screenWidth, int screenHeight);
    void run();
    ~Application();

private:
    void helpMenu();

    void update();
    void handleEvents();
    void renderGraphics();

private:
    // SDL Application variables
    SDL_Window *mWindow = nullptr;
    Renderer *mRenderer = nullptr;
    SDL_Event mEvent;

    // Window parameters
    bool isRunning;
    int screenWidth;
    int screenHeight;

    // Our current game
    // on the heap -> not really optimised
    ChessGame *mGame;
    bool isOver;

    // Variable to communicate beetween handleEvents and update functions
    // Basically in handle events we just recover the event and its in the update function that we actually do it
    Events currentEvent = Events::NONE;

    // Modes
    // We actually use handle them in the handle events function because they dont have anything to do with the game
    // they are only parameters
    bool multiThreadedMode = false;
    bool verboseMode = false;
    int depth;

    // The 2 chronos for the verbose mode
    std::chrono::high_resolution_clock::time_point verboseTimeCounterStart;
    std::chrono::high_resolution_clock::time_point verboseTimeCounterEnd;

    // For human to make a move

    // Relative position (example (800, 800) in a click mean (7,7) in tab coordinates)
    int relativeX;
    int relativeY;

    bool humanToPlay;
    ChessPiece selectedPiece;
    bool weHaveASelectedPiece;
};