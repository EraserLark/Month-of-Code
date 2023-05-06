#pragma once
//#include "SDLfoundation.h"
#include "entity.h"

class Texture {
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect dimensions = { 0,0,0,0 };
public:
    Texture() {}

    bool Load(std::string filePath, SDL_Renderer* renderer);
    bool LoadText(TTF_Font* font, std::string text, SDL_Color fontColor, SDL_Renderer* renderer);

    void SetPosition(int x, int y);
    int GetHeight();
    int GetWidth();

    void Render(SDL_Renderer* renderer, SDL_Rect* source = nullptr, SDL_Rect* dest = nullptr);
    void RenderText(SDL_Renderer* renderer);

    void DestroyTexture();
    ~Texture();
};