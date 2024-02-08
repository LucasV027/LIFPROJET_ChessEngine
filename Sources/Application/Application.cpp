#include "Application.h"

Application::Application(int screenWidth, int screenHeight)
{
    isRunning = true;
    screenWidth = screenWidth;
    screenHeight = screenHeight;
    depth = 3;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    mWindow = SDL_CreateWindow("Chess Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!mWindow)
    {
        printf("mWindow could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }
    // ---

    // Graphics initialisation
    mRenderer = new Renderer(mWindow);

    // Game logic initialisation
    mGame = new ChessGame();
    isOver = mGame->isOver();
    humanToPlay = !mGame->isItAITurns();

    // Resizing the renderer
    mRenderer->resize(screenWidth, screenHeight, *mGame);
}

void Application::helpMenu()
{
    std::cout << "--- HELP ---" << std::endl;
    std::cout << "** Commands : " << std::endl;
    std::cout << "1 - Count possible moves for this turn." << std::endl;
    std::cout << "2 - Apply a random move on the board." << std::endl;
    std::cout << "3 - Make the IA play for this turn (depth = " << depth << ")" << std::endl;
    std::cout << "4 - Evaluate this position for the person to whom it is the turn." << std::endl;
    std::cout << "5 - Count sub positions from this state (depth = " << depth << ")" << std::endl;
    std::cout << "6 - Undo last move made on the board." << std::endl;
    std::cout << "7 - Get the FEN format string of the current game." << std::endl;
    std::cout << "8 - Enter a new game with the FEN format." << std::endl;

    std::cout << std::endl;

    std::cout << "m - Multi-threaded mode." << std::endl;
    std::cout << "v - Verbose mode." << std::endl;
    std::cout << "z & s - Modulate the depth." << std::endl;

    std::cout << std::endl;

    std::cout << "** Parameters : " << std::endl;
    std::cout << "Multi-threaded mode : " << (multiThreadedMode ? "ON" : "OFF") << std::endl;
    std::cout << "Verbose mode : " << (verboseMode ? "ON" : "OFF") << std::endl;
    std::cout << "Depth : " << depth << std::endl;

    std::cout << "(Press q to quit)" << std::endl;
    std::cout << "------------" << std::endl;
}

void Application::handleEvents()
{
    while (SDL_PollEvent(&mEvent))
    {
        switch (mEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        // WINDOW EVENTS //
        case SDL_WINDOWEVENT:
            if (mEvent.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                mRenderer->resize(mEvent.window.data1, mEvent.window.data2, *mGame);
            }
            SDL_GetWindowSize(this->mWindow, &screenWidth, &screenHeight);
            break;

        // KEYBOARD EVENTS //
        case SDL_KEYDOWN:
            switch (mEvent.key.keysym.sym)
            {
            case SDLK_q:
                isRunning = false;
                break;

            case SDLK_1:
            case SDLK_KP_1:
                currentEvent = Events::COUNT_POSSIBLE_MOVES;
                break;

            case SDLK_2:
            case SDLK_KP_2:
                currentEvent = Events::RANDOM_MOVE;
                break;

            case SDLK_3:
            case SDLK_KP_3:
                currentEvent = Events::MAKE_IA_CHESSMOVE;
                break;

            case SDLK_4:
            case SDLK_KP_4:
                currentEvent = Events::EVALUATION;
                break;

            case SDLK_5:
            case SDLK_KP_5:
                currentEvent = Events::COUNT_SUB_POSITIONS;
                break;

            case SDLK_6:
            case SDLK_KP_6:
                currentEvent = Events::UNDO_LAST_MOVE;
                break;

            case SDLK_7:
            case SDLK_KP_7:
                currentEvent = Events::DISPLAY_FEN_STRING;
                break;

            case SDLK_8:
            case SDLK_KP_8:
                currentEvent = Events::NEW_GAME;
                break;

            case SDLK_h:
                helpMenu();
                break;

            case SDLK_m:
                multiThreadedMode = !multiThreadedMode;
                std::cout << "Multi-threaded mode : " << (multiThreadedMode ? "ON" : "OFF") << std::endl;
                break;

            case SDLK_v:
                verboseMode = !verboseMode;
                std::cout << "Verbose mode : " << (verboseMode ? "ON" : "OFF") << std::endl;
                break;

            case SDLK_s:
            case SDLK_DOWN:
                if (depth > 1)
                {
                    depth--;
                    std::cout << "Depth reduction (new depth = " << depth << ")" << std::endl;
                }
                else
                {
                    std::cout << "Can't reduce the depth : already at minimum (actual depth = " << depth << ")" << std::endl;
                }
                break;

            case SDLK_z:
            case SDLK_UP:
                depth++;
                std::cout << "Increasing depth (new depth = " << depth << ")" << std::endl;
                break;

            default:
                break;
            }

        // MOUSE EVENTS //
        case SDL_MOUSEBUTTONDOWN:
            if (mEvent.button.button == SDL_BUTTON_LEFT) // LEFT CLICK
            {
                int mouseX = mEvent.button.x;
                int mouseY = mEvent.button.y;

                if (mRenderer->getChessBoardBox().isInside(mouseX, mouseY) && !mGame->isItAITurns()) // Inside the chessBoardBox rendered and human turns
                {
                    currentEvent = Events::HUMAN_CLICK;

                    relativeX = (mouseX - mRenderer->getChessBoardBox().getXOffset()) / mRenderer->getSquareSizeX();
                    relativeY = (mouseY - mRenderer->getChessBoardBox().getYOffset()) / mRenderer->getSquareSizeY();
                }
            }
            break;

        default:
            break;
        }
    }
}

void Application::update()
{
    if (!mGame) // No current game = we cant update anything
    {
        return;
    }

    if (mGame->isOver())
    {
        if (!isOver) // Little trick to have the message only 1 time
        {
            std::cout << mGame->players[mGame->turnIndex].playerName << " has won the game !" << std::endl;
            std::cout << "This game is over, you can still undo the last move or create a new game ! " << std::endl;
        }

        isOver = true;

        // The game is over while we dont have Undo last move or new game event
        if (!(currentEvent == Events::UNDO_LAST_MOVE || currentEvent == Events::NEW_GAME))
        {
            return;
        }

        // If we arrive here it means that we have either undo the last move so the game is not over anymore
        // Or we're creating a new game
        isOver = false;
    }

    if (mGame->isItAITurns())
    {
        currentEvent = Events::IAS_TURN;
    }

    // Verbose mode timer start
    // We sort out Human click because it means nothing to times it
    if (currentEvent != Events::NONE && currentEvent != Events::HUMAN_CLICK && verboseMode)
    {
        verboseTimeCounterStart = std::chrono::high_resolution_clock::now();
    }

    switch (currentEvent)
    {
    case Events::COUNT_POSSIBLE_MOVES:
        std::cout << "Possible moves count : " << mGame->getAllPossibleMoves().size() << std::endl;
        break;

    case Events::COUNT_SUB_POSITIONS:
        std::cout << "Sub-positions count (depth=" << depth << "), processing... " << std::flush;
        std::cout << ChessIA::countSubPosition(*mGame, depth) << " positions found !" << std::endl;
        break;

    case Events::EVALUATION:
        std::cout << "Static evaluation of the game (for " << mGame->players[mGame->turnIndex].playerName << ") : " << std::flush;
        std::cout << ChessIA::evaluation(*mGame) << std::endl;
        break;

    case Events::UNDO_LAST_MOVE:
        if (this->mGame->moveHistory.empty())
        {
            std::cout << "No moves in the history." << std::endl;
        }
        else
        {
            std::cout << "Undoing last move. Move history size : " << this->mGame->moveHistory.size() - 1 << std::endl;
            mGame->undoMove();

            int safetyLimit = 5;
            while (mGame->isItAITurns() && safetyLimit > 0) // We need to undo multiple times when we play against IA because if we undo
                                                            // its will directly replay the same move
                                                            // The safety limit is here to prevent a infinite loop when
                                                            // 2 IA's are facing
            {
                std::cout << "Re-Undoing last move. (IA's turn) Move history size : " << this->mGame->moveHistory.size() - 1 << std::endl;
                mGame->undoMove();
                safetyLimit--;
            }
        }
        break;

    case Events::DISPLAY_FEN_STRING:
        std::cout << "FEN string of this game : " << this->mGame->toFENString() << std::endl;
        break;

    case Events::RANDOM_MOVE:
        std::cout << "Random move." << std::endl;
        mGame->randomMove();
        break;

    case Events::MAKE_IA_CHESSMOVE:
        std::cout << "Start of the research... ";
        mGame->makeAMove(ChessIA::bestMove(*mGame, depth, verboseMode), false);
        std::cout << "Done !" << std::endl;
        break;

    case Events::HUMAN_CLICK:
    {
        if (!weHaveASelectedPiece) // First of all we have no selected pieces
        {
            selectedPiece = mGame->chessBoard[relativeY][relativeX]; // So we take one (we dont care about the turn for now)

            if (selectedPiece && selectedPiece.playerIndex == mGame->turnIndex) // If we click on a real piece (not a blank case) + the color is good (according to the turn index)
            {
                weHaveASelectedPiece = true; // Then we notify our renderer to draw the piece possible moves
                mRenderer->setAPieceToDrawPossibleMoves(selectedPiece);
            }
        }
        else if (weHaveASelectedPiece && (mGame->chessBoard[relativeY][relativeX].playerIndex == mGame->turnIndex)) // If we click on an ally piece when  we already have a selected piece
                                                                                                                    // then we juste update the selected piece (we dont need to reset it as
                                                                                                                    // if we where clicking on a impossible move)
        {
            selectedPiece = mGame->chessBoard[relativeY][relativeX];
            mRenderer->setAPieceToDrawPossibleMoves(selectedPiece);
        }
        else // The last case is we have a selected pieces we just click on an non-ally pieces it means we can check if the move is valid or not
        {
            Vec2Int ourPiecePosition(selectedPiece.x, selectedPiece.y);
            Vec2Int ourMove(relativeX, relativeY);

            mGame->makeAMove(Move(ourPiecePosition, ourMove, MoveType::NONE), true); // The true means we apply verifications to this move

            // After trying to make a move either its valid or not we reset the piece to go back to our initial case
            selectedPiece = ChessPiece();
            weHaveASelectedPiece = false;
            mRenderer->setAPieceToDrawPossibleMoves(ChessPiece());
        }
    }
    break;

    case Events::IAS_TURN:
        std::cout << "IA's turn " << std::endl;
        mGame->makeAMove(ChessIA::bestMove(*mGame, depth, verboseMode), false);
        break;

    case Events::NEW_GAME:
    {
        std::cout << "Enter de new game code : ";
        std::string newGameString;
        std::getline(std::cin, newGameString);

        if (newGameString.empty()) // No string input -> we do nothing
        {
            return;
        }

        ////////////////// Only for the demo //////////////////
        if (newGameString[0] == 'd' && std::isdigit(newGameString[1]))
        {
            delete mGame;

            Demo::DemoGame dg = Demo::getDemoGame(newGameString[1] - '0');
            mGame = new ChessGame(dg.board, dg.players, dg.turnIndex);
            isOver = mGame->isOver();
            mRenderer->resize(screenWidth, screenHeight, *mGame);
        }
        ///////////////////////////////////////////////////////
        else if (validFEN(newGameString))
        {
            // To create / reallocate a new game
            // We firstly delete the old one
            // Then we recreate a new game on the heap
            // Finally we update the renderer & the isOver boolean witch is linked with application
            delete mGame;

            mGame = new ChessGame(newGameString);
            mRenderer->resize(screenWidth, screenHeight, *mGame);
            isOver = mGame->isOver();
        }
    }
    break;

    default:
        break;
    }

    // We are in verbose mode so we need to get the time passed in the update function
    // its the equivalent of what time was it when we ended the loop minus the time when we started the loop
    if (currentEvent != Events::NONE && currentEvent != Events::HUMAN_CLICK && verboseMode)
    {
        verboseTimeCounterEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> eventDuration = verboseTimeCounterEnd - verboseTimeCounterStart;
        double eventDurationSecond = eventDuration.count();

        // Theses 2 lines are basically to print the time in second or in ms according to the values (This is usefull to get rid of time with exposant)
        std::cout << "Event time :" << (eventDurationSecond >= 1. ? eventDurationSecond : eventDurationSecond * 1000)
                  << (eventDurationSecond >= 1. ? " second." : " ms.") << std::endl;
    }

    currentEvent = Events::NONE;
}

void Application::renderGraphics()
{
    if (mGame)
        mRenderer->display(*mGame);
}

void Application::run()
{
    while (isRunning)
    {
        handleEvents();
        update();
        renderGraphics();
    }

    printf("Closing...\n");
}

Application::~Application()
{
    delete mRenderer;
    delete mGame;
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
