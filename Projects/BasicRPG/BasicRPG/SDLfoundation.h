#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "StateMachine.h"
#include "entity.h"
#include "Texture.h"

class Texture;
class Textbox;
class Menu;

struct DrawMaterials {
    Texture* bgTexture;
    Texture* enemySprite;
    Textbox* currentTB;
    Menu* currentMenu;
};

int Initialize();
bool LoadMedia(Texture*, Texture*);
void Draw(DrawMaterials*);
void CleanUp(DrawMaterials*);

extern SDL_Window* globalWindow;
extern SDL_Renderer* globalRenderer;

extern const int ScreenWidth;
extern const int ScreenHeight;

extern bool isRunning;
extern SDL_Rect enemyDestRect;
extern SDL_Rect textRect;

//extern Textbox* currentTB;
//extern Menu* currentMenu;

//class Texture {
//    SDL_Surface* surface = nullptr;
//    SDL_Texture* texture = nullptr;
//    SDL_Rect dimensions = { 0,0,0,0 };
//public:
//    Texture() {}
//
//    bool Load(std::string filePath, SDL_Renderer* renderer);
//    bool LoadText(TTF_Font* font, std::string text, SDL_Color fontColor, SDL_Renderer* renderer);
//
//    void SetPosition(int x, int y);
//    int GetHeight();
//    int GetWidth();
//
//    void Render(SDL_Renderer* renderer, SDL_Rect* source = nullptr, SDL_Rect* dest = nullptr);
//    void RenderText(SDL_Renderer* renderer);
//
//    void DestroyTexture();
//    ~Texture();
//};


class TextZone {
public:
    void SetRenderer(SDL_Renderer* mainRenderer) { renderer = mainRenderer; }
    void SetFont(TTF_Font* font) { textFont = font; }

    void Show() { hideTextzone = false; }
    void Hide() { hideTextzone = true; }

    void RenderTB();
    virtual void Render() = 0;
    virtual void Destroy() = 0;

    virtual ~TextZone();
protected:
    SDL_Renderer* renderer = nullptr;
    SDL_Rect textboxRect{ 25, ScreenHeight - 100, ScreenWidth - 50, 75 };
    TTF_Font* textFont = nullptr;
    SDL_Color fontColor = { 0,0,0,0 };
    bool hideTextzone = true;

    TextZone(SDL_Renderer* renderer, TTF_Font* font);
};


class Textbox : public TextZone {
    Texture textTexture;

public:
    Textbox(SDL_Renderer* renderer, TTF_Font* font);

    void NewText(std::string message);

    virtual void Render() override;
    virtual void Destroy() override;

    ~Textbox();
};


class Menu : public TextZone {
    const int choiceCount = 3;
    int playerChoice;
    SDL_Rect cursor{0,0,0,0};
    Texture choiceTextures[3];
public:
    Menu(SDL_Renderer*, TTF_Font*, std::string*);

    void IncrementSelection();
    void DecrementSelection();
    int ConfirmSelection();
    void MoveCursor();

    virtual void Render() override;
    virtual void Destroy() override;

    ~Menu();
};


//extern Texture bgTexture;
//extern Texture enemySprite;
//extern Textbox textbox;
extern TTF_Font* font;