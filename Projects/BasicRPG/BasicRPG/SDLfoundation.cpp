#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDLfoundation.h"
#include "StateMachine.h"

SDL_Window* globalWindow = nullptr;
SDL_Renderer* globalRenderer = nullptr;

const int ScreenWidth = 640;
const int ScreenHeight = 480;

bool isRunning = true;
SDL_Rect enemyDestRect{ (ScreenWidth / 2) - 100, (ScreenHeight / 2) - 100, 200, 200 };
SDL_Rect textRect{ 50, ScreenHeight - 95, 50, 200 };    //w and h here are not used, just x and y

Texture bgTexture;
Texture enemySprite;

TTF_Font* font;

int Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)   //SDL_INIT_EVENTS as well?
    {
        std::cout << "Could not initialize properly. Error: " << SDL_GetError();
        return -1;
    }
    else if (SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, NULL, &globalWindow, &globalRenderer) < 0)
    {
        std::cout << "Could not create window and renderer. Error: " << SDL_GetError();
        return -2;
    }
    else if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cout << "Could not initialize IMG library. Error:" << IMG_GetError();
        return -3;
    }
    else if (TTF_Init() < 0)
    {
        std::cout << "Could not initialize TTF library. Error: " << TTF_GetError();
        return -4;
    }
    else if (SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 0) < 0)
    {
        std::cout << "Could not set render draw color. Error: " << SDL_GetError();
        return -5;
    }

    return 0;
}

bool LoadMedia()
{
    font = TTF_OpenFont("Assets/Fonts/dogicapixel.ttf", 18);

    if (!bgTexture.Load("Assets/BG/BasicRPG_PlantBG.png", globalRenderer))
        return false;
    if (!enemySprite.Load("Assets/Enemy/Enemy_Bush.png", globalRenderer))
        return false;
    else
        return true;
}

void Draw(Textbox* textbox, Menu* menu, Texture* bgTexture, Texture* enemySprite)
{
    SDL_RenderClear(globalRenderer);

    //Render sprites
    bgTexture->Render(globalRenderer);
    enemySprite->Render(globalRenderer, nullptr, &enemyDestRect);

    //Render textbox
    textbox->Render();
    menu->Render();

    //Update back buffer
    SDL_RenderPresent(globalRenderer);

    //Front buffer
    SDL_UpdateWindowSurface(globalWindow); //Call after all blits/rendering is done
}

void CleanUp(Texture* bgTexture, Texture* enemySprite)
{
    SDL_DestroyWindow(globalWindow);
    SDL_DestroyRenderer(globalRenderer);

    bgTexture->DestroyTexture();
    enemySprite->DestroyTexture();
    //textbox->DestroyTextbox();
    TTF_CloseFont(font);
    font = nullptr;

    globalWindow = nullptr;
    globalRenderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}