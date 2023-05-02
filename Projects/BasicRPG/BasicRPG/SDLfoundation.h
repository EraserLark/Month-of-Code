#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "StateMachine.h"

int Initialize();
bool LoadMedia();
void Draw();
void CleanUp();

extern SDL_Window* globalWindow;
extern SDL_Renderer* globalRenderer;

extern const int ScreenWidth;
extern const int ScreenHeight;

extern bool isRunning;
extern SDL_Rect enemyDestRect;
extern SDL_Rect textRect;

class Texture {
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect dimensions = { 0,0,0,0 };
public:
    Texture() {}

    bool Load(std::string filePath, SDL_Renderer* renderer)
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

    bool LoadText(TTF_Font* font, std::string text, SDL_Color fontColor, SDL_Renderer* renderer)
    {
        DestroyTexture();

        surface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), fontColor, 400);
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

    void SetPosition(int x, int y)
    {
        dimensions.x = x;
        dimensions.y = y;
    }

    void Render(SDL_Renderer* renderer, SDL_Rect* source = nullptr, SDL_Rect* dest = nullptr)
    {
        SDL_RenderCopy(globalRenderer, texture, source, dest);
    }

    void RenderText(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &dimensions);
    }

    void DestroyTexture()
    {
        SDL_FreeSurface(surface);
        surface = nullptr;
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    ~Texture()
    {
        DestroyTexture();
    }
};

class Textbox{
    SDL_Renderer* renderer = nullptr;
    SDL_Rect textboxRect{ 25, ScreenHeight - 100, ScreenWidth - 50, 75 };
    Texture textTexture;
    TTF_Font* textFont = nullptr;
    SDL_Color fontColor = { 0,0,0,0 };

    bool hideTextbox = true;
public:
    //Setup/Rendering
    Textbox()
    {
        textTexture.SetPosition(textRect.x, textRect.y);
    }

    void SetRenderer(SDL_Renderer* mainRenderer)
    {
        renderer = mainRenderer;
    }

    void SetFont(TTF_Font* font)
    {
        textFont = font;
    }

    void NewText(std::string message)
    {
        textTexture.LoadText(textFont, message, fontColor, renderer);
    }

    void ShowTB()
    {
        hideTextbox = false;
    }

    void HideTB()
    {
        hideTextbox = true;
    }

    void RenderTB()
    {
        if (!hideTextbox)
        {
            //Draw textbox
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderFillRect(renderer, &textboxRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            //Render text
            textTexture.RenderText(renderer);
        }
    }

    //Destroy
    void DestroyTextbox()
    {
        textTexture.DestroyTexture();
        TTF_CloseFont(textFont);
        textFont = nullptr;
    }

    ~Textbox()
    {
        DestroyTextbox();
    }
};

extern Texture bgTexture;
extern Texture enemySprite;
extern Textbox textbox;