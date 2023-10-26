#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>

#include "renderer.h"

class Application
{
public:
    Application(int screenWidth, int screenHeight);
    void run();
    ~Application();

private:
    void update();
    void handleEvents();
    void renderGraphics();

    void resizeWindow(int newWidth, int newHeight);

private:
    SDL_Window *mWindow = nullptr;
    Renderer *mRenderer = nullptr;
    SDL_Event mEvent;

    bool isRunning;

    int screenWidth;
    int screenHeight;

    int mouseX, mouseY;

    ChessGame *mGame;
};