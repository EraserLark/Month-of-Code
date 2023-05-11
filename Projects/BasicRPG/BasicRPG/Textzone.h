#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"

class TextZone {
public:
    void SetRenderer(SDL_Renderer* mainRenderer) { tzRenderer = mainRenderer; }
    void SetFont(TTF_Font* font) { tzFont = font; }

    void Show() { hideTextzone = false; }
    void Hide() { hideTextzone = true; }

    void RenderTZ();
    virtual void Render() = 0;
    virtual void Destroy() = 0;

    virtual ~TextZone();
protected:
    TextZone(SDL_Renderer* renderer, TTF_Font* font);

    SDL_Renderer* tzRenderer;
    TTF_Font* tzFont;
    SDL_Rect tzRect;
    SDL_Color fontColor;
    bool hideTextzone;
};


class Textbox : public TextZone {
public:
    Textbox(SDL_Renderer* renderer, TTF_Font* font);

    void NewText(std::string message);

    virtual void Render() override;
    virtual void Destroy() override;

    ~Textbox();
private:
    Texture textTexture;
};


class Menu : public TextZone {
public:
    Menu(SDL_Renderer*, TTF_Font*, std::string*);

    void IncrementSelection();
    void DecrementSelection();
    int ConfirmSelection();
    void MoveCursor();

    virtual void Render() override;
    virtual void Destroy() override;

    ~Menu();
private:
    const int choiceCount = 3;
    Texture choiceTextures[3];
    int playerChoice;
    SDL_Rect cursor;
};