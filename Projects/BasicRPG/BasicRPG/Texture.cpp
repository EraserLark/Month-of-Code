#include "SDLfoundation.h"
#include <SDL_image.h>
#include "Texture.h"

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
    SDL_RenderCopy(renderer, texture, source, dest);
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