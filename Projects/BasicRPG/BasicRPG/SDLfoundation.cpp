#include "SDLfoundation.h"
#include "MenuState.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "StateMachine.h"
#include "Texture.h"
#include "Textzone.h"

bool Initialize(DrawMaterials* drawMat)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Could not initialize properly. Error: " << SDL_GetError();
        return false;
    }
    else if (SDL_CreateWindowAndRenderer(drawMat->ScreenWidth, drawMat->ScreenHeight, NULL, &(drawMat->window), &(drawMat->renderer)) < 0)
    {
        std::cout << "Could not create window and renderer. Error: " << SDL_GetError();
        return false;
    }
    else if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cout << "Could not initialize IMG library. Error:" << IMG_GetError();
        return false;
    }
    else if (TTF_Init() < 0)
    {
        std::cout << "Could not initialize TTF library. Error: " << TTF_GetError();
        return false;
    }
    else if (SDL_SetRenderDrawColor(drawMat->renderer, 0, 0, 0, 0) < 0)
    {
        std::cout << "Could not set render draw color. Error: " << SDL_GetError();
        return false;
    }

    return true;
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
        enemySprite->Render(drawMat->renderer, nullptr, &(drawMat->enemyDestRect));
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

void CleanUp(Texture* bgTextures, Texture* enemySprites, DrawMaterials* drawMat)
{
    delete[] bgTextures;
    delete[] enemySprites;

    TTF_CloseFont(drawMat->font);
    SDL_DestroyRenderer(drawMat->renderer);
    SDL_DestroyWindow(drawMat->window);

    drawMat->font = nullptr;
    drawMat->renderer = nullptr;
    drawMat->window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}