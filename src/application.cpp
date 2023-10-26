#include "application.h"

Application::Application(int screenWidth, int screenHeight) : isRunning(true),
                                                              screenWidth(screenWidth),
                                                              screenHeight(screenHeight)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    mWindow = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!mWindow)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    mRenderer = new Renderer(mWindow);
    mGame = new ChessGame();
    mRenderer->resize(screenWidth, screenHeight, *mGame);
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

        case SDL_WINDOWEVENT:

            if (mEvent.window.event == SDL_WINDOWEVENT_RESIZED)
                resizeWindow(mEvent.window.data1, mEvent.window.data2);
            break;

        case SDL_KEYDOWN:
            switch (mEvent.key.keysym.sym)
            {
            case SDLK_q:
                isRunning = false;
                break;

            default:
                break;
            }

        case SDL_MOUSEBUTTONDOWN:
            if (mEvent.button.button == SDL_BUTTON_LEFT)
            {
                mouseX = mEvent.button.x;
                mouseY = mEvent.button.y;

                if (mRenderer->chessBoardBox.isInside(mouseX, mouseY)) // Inside the chessBoardBox rendered
                {
                    int relativeX = (mouseX - mRenderer->chessBoardBox.getXOffset()) / mRenderer->squareSizeX;
                    int relativeY = (mouseY - mRenderer->chessBoardBox.getYOffset()) / mRenderer->squareSizeY;
                    // std::cout << "X : " << relativeX << " | Y : " << relativeY << "\n" << std::flush;
                }
            }

            break;
        case SDL_MOUSEMOTION:

            break;
        case SDL_MOUSEBUTTONUP:

            break;

        default:
            break;
        }
    }
}

void Application::renderGraphics() { mRenderer->display(*mGame); }
void Application::resizeWindow(int newWidth, int newHeight) { mRenderer->resize(newWidth, newHeight, *mGame); }

void Application::run()
{
    while (isRunning)
    {
        handleEvents();
        //  renderGraphics();
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
