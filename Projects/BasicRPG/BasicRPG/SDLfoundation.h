#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "StateMachine.h"

class Texture;

int Initialize();
bool LoadMedia();
void Draw(Textbox*, Menu*, Texture*, Texture*);
void CleanUp(Texture*, Texture*);

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


class TextZone {
public:
    void SetRenderer(SDL_Renderer* mainRenderer)
    {
        renderer = mainRenderer;
    }

    void SetFont(TTF_Font* font)
    {
        textFont = font;
    }

    void Show()
    {
        hideTextzone = false;
    }
    void Hide()
    {
        hideTextzone = true;
    }

    virtual void Render() = 0;


    void RenderTB() {
        //Draw textbox
        if (!hideTextzone)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderFillRect(renderer, &textboxRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        }
    }

    virtual void Destroy() = 0;

    virtual ~TextZone()
    {
        renderer = nullptr;
        textFont = nullptr;
    }

protected:
    SDL_Renderer* renderer = nullptr;
    SDL_Rect textboxRect{ 25, ScreenHeight - 100, ScreenWidth - 50, 75 };
    TTF_Font* textFont = nullptr;
    SDL_Color fontColor = { 0,0,0,0 };
    bool hideTextzone = true;

    TextZone(SDL_Renderer* renderer, TTF_Font* font)
    {
        SetRenderer(renderer);
        SetFont(font);
    }
};


class Textbox : public TextZone {
    Texture textTexture;

public:
    //Setup/Rendering
    Textbox(SDL_Renderer* renderer, TTF_Font* font)
        :TextZone(renderer, font)
    {
        textTexture.SetPosition(textRect.x, textRect.y);
    }

    void NewText(std::string message)
    {
        textTexture.LoadText(textFont, message, fontColor, renderer);
    }

    virtual void Render() override
    {
        if (!hideTextzone)
        {
            RenderTB();
            //Render text
            textTexture.RenderText(renderer);
        }
    }

    //Destroy
    virtual void Destroy() override
    {
        textTexture.DestroyTexture();
    }

    ~Textbox()
    {
        Destroy();
    }
};


class Menu : public TextZone {
    int playerChoice;
    SDL_Rect cursor{ 30, 30, 30, 30 };
    Texture textTexture1;
    Texture textTexture2;
    Texture textTexture3;
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font)
        :TextZone(renderer, font)
    {
        playerChoice = 0;

        textTexture1.LoadText(textFont, "Action1", fontColor, renderer);
        textTexture2.LoadText(textFont, "Action2", fontColor, renderer);
        textTexture3.LoadText(textFont, "Action3", fontColor, renderer);
    }

    void IncrementSelection()
    {
        playerChoice++;
        if (playerChoice > 2)
        {
            playerChoice = 0;
        }
    }

    void DecrementSelection()
    {
        playerChoice--;
        if (playerChoice < 0)
        {
            playerChoice = 2;
        }
    }

    int ConfirmSelection()
    {
        return playerChoice;
    }

    virtual void Render() override
    {
        if (!hideTextzone)
        {
            RenderTB();

            textTexture1.RenderText(renderer);
            textTexture2.RenderText(renderer);
            textTexture3.RenderText(renderer);

            SDL_SetRenderDrawColor(renderer, 66, 135, 245, 0);
            SDL_RenderFillRect(renderer, &cursor);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        }
    }

    virtual void Destroy() override
    {
        textTexture1.DestroyTexture();
        textTexture2.DestroyTexture();
        textTexture3.DestroyTexture();
    }

    ~Menu()
    {
        Destroy();
    }
};


extern Texture bgTexture;
extern Texture enemySprite;
//extern Textbox textbox;
extern TTF_Font* font;