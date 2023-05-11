#pragma once
#include <string>
#include <iostream>
//#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "StateMachine.h"
//#include "entity.h"
#include "Texture.h"

class Texture;
class Textbox;
class Menu;

extern const int ScreenWidth;
extern const int ScreenHeight;

struct DrawMaterials {
    TTF_Font* font = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    Texture* bgTexture = nullptr;
    Texture* enemySprite = nullptr;
    Textbox* currentTB = nullptr;
    Menu* currentMenu = nullptr;

    SDL_Rect enemyDestRect{ (ScreenWidth / 2) - 100, (ScreenHeight / 2) - 100, 200, 200 };
    SDL_Rect textRect{ 50, ScreenHeight - 95, 50, 200 }; //w and h here are not used, just x and y
};

bool Initialize(DrawMaterials*);
bool LoadMedia(Texture*, Texture*, DrawMaterials*);
void Draw(DrawMaterials*);
void CleanUp(Texture*, Texture*, DrawMaterials*);