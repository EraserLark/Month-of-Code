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


bool Texture::Load(std::string filePath, SDL_Renderer* renderer)
{
    surface = IMG_Load(filePath.c_str());
    if (surface == nullptr)
    {
        std::cout << "Could not load surface. Error: " << IMG_GetError();
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    dimensions.w = surface->w;
    dimensions.h = surface->h;

    return true;
}

bool Texture::LoadText(TTF_Font* font, std::string text, SDL_Color fontColor, SDL_Renderer* renderer)
{
    DestroyTexture();

    surface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), fontColor, 550);
    if (surface == nullptr)
    {
        std::cout << "Could not load surface. Error: " << IMG_GetError();
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    dimensions.w = surface->w;
    dimensions.h = surface->h;

    return true;
}

void Texture::SetPosition(int x, int y)
{
    dimensions.x = x;
    dimensions.y = y;
}

int Texture::GetHeight() { return dimensions.h; }
int Texture::GetWidth() { return dimensions.w; }

void Texture::Render(SDL_Renderer* renderer, SDL_Rect* source, SDL_Rect* dest)
{
    SDL_RenderCopy(globalRenderer, texture, source, dest);
}

void Texture::RenderText(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &dimensions);
}

void Texture::DestroyTexture()
{
    SDL_FreeSurface(surface);
    surface = nullptr;
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

Texture::~Texture()
{
    DestroyTexture();
}


TextZone::TextZone(SDL_Renderer* renderer, TTF_Font* font)
{
    SetRenderer(renderer);
    SetFont(font);
}

void TextZone::RenderTB() {
    if (!hideTextzone)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderFillRect(renderer, &textboxRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
}

TextZone::~TextZone()
{
    renderer = nullptr;
    textFont = nullptr;
}


Textbox::Textbox(SDL_Renderer* renderer, TTF_Font* font)
    :TextZone(renderer, font)
{
    textTexture.SetPosition(textRect.x, textRect.y);
}

void Textbox::NewText(std::string message)
{
    textTexture.LoadText(textFont, message, fontColor, renderer);
}

void Textbox::Render()
{
    if (!hideTextzone)
    {
        RenderTB();
        textTexture.RenderText(renderer);
    }
}

void Textbox::Destroy()
{
    textTexture.DestroyTexture();
}

Textbox::~Textbox()
{
    Destroy();
}


Menu::Menu(SDL_Renderer* renderer, TTF_Font* font)
    :TextZone(renderer, font)
{
    playerChoice = 0;

    int tbWidth = textboxRect.w / 3;
    int tbHeight = textboxRect.h;

    cursor.y = textboxRect.y + 5;
    cursor.w = tbWidth;
    cursor.h = tbHeight - 10;
    MoveCursor();

    for (int i = 0; i < choiceCount; i++)
    {
        choiceTextures[i].LoadText(textFont, "Action", fontColor, renderer);

        int textWidth = choiceTextures[i].GetWidth();
        int textHeight = choiceTextures[i].GetHeight();

        int newx = textboxRect.x + (tbWidth * i) + ((tbWidth / 2) - (textWidth / 2));
        int newy = textboxRect.y + (tbHeight / 2) - (textHeight / 2);

        choiceTextures[i].SetPosition(newx, newy);
    }
}

void Menu::IncrementSelection()
{
    playerChoice++;
    if (playerChoice > 2)
    {
        playerChoice = 0;
    }

    MoveCursor();
}
void Menu::DecrementSelection()
{
    playerChoice--;
    if (playerChoice < 0)
    {
        playerChoice = 2;
    }

    MoveCursor();
}
int Menu::ConfirmSelection()
{
    return playerChoice;
}

void Menu::MoveCursor()
{
    int moveAmt = playerChoice;
    cursor.x = textboxRect.x + (cursor.w * moveAmt);
}

void Menu::Render()
{
    if (!hideTextzone)
    {
        RenderTB();

        for (int i = 0; i < choiceCount; i++)
        {
            choiceTextures[i].RenderText(renderer);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawRect(renderer, &cursor);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
}

void Menu::Destroy()
{
    for (int i = 0; i < choiceCount; i++)
    {
        choiceTextures[i].DestroyTexture();
    }
}

Menu::~Menu()
{
    Destroy();
}