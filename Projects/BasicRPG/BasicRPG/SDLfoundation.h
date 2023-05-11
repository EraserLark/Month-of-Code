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

struct DrawMaterials {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    Texture* bgTexture = nullptr;
    Texture* enemySprite = nullptr;
    Textbox* currentTB = nullptr;
    Menu* currentMenu = nullptr;
};

int Initialize(DrawMaterials*);
bool LoadMedia(Texture*, Texture*, DrawMaterials*);
void Draw(DrawMaterials*);
void CleanUp(DrawMaterials*);

extern const int ScreenWidth;
extern const int ScreenHeight;

extern bool isRunning;
extern SDL_Rect enemyDestRect;
extern SDL_Rect textRect;