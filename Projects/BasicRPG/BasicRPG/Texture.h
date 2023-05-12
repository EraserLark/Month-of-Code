#pragma once
#include "SDLfoundation.h"

class Texture {
public:
    Texture();

    bool Load(std::string filePath, SDL_Renderer* renderer);
    bool LoadText(TTF_Font* font, std::string text, SDL_Color fontColor, SDL_Renderer* renderer);

    void SetPosition(int x, int y);
    int GetHeight();
    int GetWidth();

    void Render(SDL_Renderer* renderer, SDL_Rect* source = nullptr, SDL_Rect* dest = nullptr);
    void RenderText(SDL_Renderer* renderer);

    void DestroyTexture();
    ~Texture();
private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect dimensions;
};