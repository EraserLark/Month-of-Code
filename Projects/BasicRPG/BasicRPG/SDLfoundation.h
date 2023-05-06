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

extern TTF_Font* font;