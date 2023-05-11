#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDLfoundation.h"
#include "StateMachine.h"
#include "MenuState.h"
#include "Textzone.h"

const int ScreenWidth = 640;
const int ScreenHeight = 480;

bool isRunning = true;
SDL_Rect enemyDestRect{ (ScreenWidth / 2) - 100, (ScreenHeight / 2) - 100, 200, 200 };
SDL_Rect textRect{ 50, ScreenHeight - 95, 50, 200 };    //w and h here are not used, just x and y

int Initialize(DrawMaterials* drawMat)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Could not initialize properly. Error: " << SDL_GetError();
        return -1;
    }
    else if (SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, NULL, &(drawMat->window), &(drawMat->renderer)) < 0)
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
    else if (SDL_SetRenderDrawColor(drawMat->renderer, 0, 0, 0, 0) < 0)
    {
        std::cout << "Could not set render draw color. Error: " << SDL_GetError();
        return -5;
    }

    return 0;
}

bool LoadMedia(Texture* bgTextures, Texture* enemySprites, DrawMaterials* drawMat)
{
    drawMat->font = TTF_OpenFont("Assets/Fonts/dogicapixel.ttf", 18);
    SDL_Renderer* renderer = drawMat->renderer;

    if (!bgTextures[0].Load("Assets/BG/BasicRPG_PlantBG.png", renderer))
        return false;
    if (!bgTextures[1].Load("Assets/BG/BasicRPG_IceBG.png", renderer))
        return false;
    if (!bgTextures[2].Load("Assets/BG/BasicRPG_FireBG.png", renderer))
        return false;
    if (!bgTextures[3].Load("Assets/BG/BasicRPG_FinalBG.png", renderer))
        return false;

    if (!enemySprites[0].Load("Assets/Enemy/Enemy_Bush.png", renderer))
        return false;
    if (!enemySprites[1].Load("Assets/Enemy/Enemy_Ice.png", renderer))
        return false;
    if (!enemySprites[2].Load("Assets/Enemy/Enemy_Fire.png", renderer))
        return false;
    if (!enemySprites[3].Load("Assets/Enemy/Enemy_Final.png", renderer))
        return false;

    return true;
}

void Draw(DrawMaterials* drawMat)
{
    Texture* bgTexture = drawMat->bgTexture;
    Texture* enemySprite = drawMat->enemySprite;
    Textbox* textbox = drawMat->currentTB;
    Menu* menu = drawMat->currentMenu;

    SDL_RenderClear(drawMat->renderer);

    //Render sprites
    if (bgTexture != nullptr)
    {
        bgTexture->Render(drawMat->renderer);
    }
    if (enemySprite != nullptr)
    {
        enemySprite->Render(drawMat->renderer, nullptr, &enemyDestRect);
    }
    if (textbox != nullptr)
    {
        textbox->Render();
    }
    if (menu != nullptr)
    {
        menu->Render();
    }

    //Update back buffer
    SDL_RenderPresent(drawMat->renderer);

    //Front buffer
    SDL_UpdateWindowSurface(drawMat->window); //Call after all blits/rendering is done
}

void CleanUp(DrawMaterials* drawMat)
{
    SDL_DestroyWindow(drawMat->window);
    SDL_DestroyRenderer(drawMat->renderer);

    drawMat->bgTexture->DestroyTexture();
    drawMat->enemySprite->DestroyTexture();
    TTF_CloseFont(drawMat->font);

    drawMat->font = nullptr;
    drawMat->window = nullptr;
    drawMat->renderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}