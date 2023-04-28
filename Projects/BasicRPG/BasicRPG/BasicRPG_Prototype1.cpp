#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <Windows.h>
#include "action.h"
#include "entity.h"
#include "queue.h"

using namespace std;

void InitializeActions(Player*, Enemy*);
void PromptPlayer(Player*);
void PromptEnemy(Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();

Queue<Action> turnQueue;
Queue<Enemy> dungeonQueue;


//SDL
int initialize();
bool loadMedia();
void CleanUp();

SDL_Window* globalWindow = nullptr;
SDL_Renderer* globalRenderer = nullptr;

class Texture {
    SDL_Texture* texture = nullptr;
    int x;
    int y;
    int w;
    int h;
public:
    Texture() {}

    bool QuickLoad(SDL_Renderer* renderer, string filePath)
    {
        texture = IMG_LoadTexture(renderer, filePath.c_str());
        if (texture == nullptr)
        {
            cout << "Could not load texture. Error: " << IMG_GetError();
        }

        if (texture != NULL) return true;
        else return false;
    }

    void renderTexture(SDL_Rect* source = nullptr, SDL_Rect* dest = nullptr)
    {
        SDL_RenderCopy(globalRenderer, texture, source, dest);
    }

    void destroyTexture()
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    ~Texture()
    {
        destroyTexture();
    }
};

const int ScreenWidth = 640;
const int ScreenHeight = 480;
bool isRunning = true;

Texture bgTexture;
Texture enemySprite;

TTF_Font* textFont;

int main(int argc, char* argv[])
{
    if (initialize() != 0)
    {
        return -1;
    }
    else if(!loadMedia())
    {
        return -1;
    }
    else
    {
        SDL_Rect enemyDestRect{ (ScreenWidth / 2) - 100, (ScreenHeight / 2) - 100, 200, 200 };
        SDL_Rect textRect{ 100, ScreenHeight - 100, 180, 54 };

        SDL_Color fontColor = { 255,255,255,0 };
        SDL_Surface* textTestSurface = TTF_RenderUTF8_Solid_Wrapped(textFont, "Test 2", fontColor, 400);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(globalRenderer, textTestSurface);

        //Event Handling
        SDL_Event event;

        //Update
        while (isRunning)
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            SDL_RenderClear(globalRenderer);

            bgTexture.renderTexture();
            enemySprite.renderTexture(nullptr, &enemyDestRect);
            SDL_RenderCopy(globalRenderer, textTexture, nullptr, &textRect);

            SDL_RenderPresent(globalRenderer);

            //Front buffer
            SDL_UpdateWindowSurface(globalWindow); //Call after all blits/rendering is done
        }
    }

    CleanUp();

    return 0;
}

int initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)   //SDL_INIT_EVENTS as well?
    {
        cout << "Could not initialize properly. Error: " << SDL_GetError();
        return -1;
    }
    else if (SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, NULL, &globalWindow, &globalRenderer) < 0)
    {
        cout << "Could not create window and renderer. Error: " << SDL_GetError();
        return -2;
    }
    else if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        cout << "Could not initialize IMG library. Error:" << IMG_GetError();
        return -3;
    }
    else if (TTF_Init() < 0)
    {
        cout << "Could not initialize TTF library. Error: " << TTF_GetError();
        return -4;
    }
    else if (SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 0) < 0)
    {
        cout << "Could not set render draw color. Error: " << SDL_GetError();
        return -5;
    }
    return 0;
}

bool loadMedia()
{
    textFont = TTF_OpenFont("Assets/Fonts/dogicapixel.ttf", 18);

    if (!bgTexture.QuickLoad(globalRenderer, "Assets/BG/BasicRPG_PlantBG.png"))
        return false;
    if (!enemySprite.QuickLoad(globalRenderer, "Assets/Enemy/Enemy_Bush.png"))
        return false;
    else
        return true;
}

void CleanUp()
{
    SDL_DestroyWindow(globalWindow);
    SDL_DestroyRenderer(globalRenderer);

    bgTexture.destroyTexture();
    enemySprite.destroyTexture();

    TTF_CloseFont(textFont);
    textFont = nullptr;

    globalWindow = nullptr;
    globalRenderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


#pragma region "Battle Code"
//int main(int argc, char* argv[])
void TempBattleHolder()
{
    dungeonQueue.Enqueue(new Goblin());
    dungeonQueue.Enqueue(new Wizard());

    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "What is your name: ";
    string playerName;
    cin >> playerName;
    cout << endl;

    Player* p = new Player(playerName);
    Enemy* e = nullptr;

    while(!dungeonQueue.IsEmpty())
    {
        e = dungeonQueue.GetHead();
        InitializeActions(p, e);

        cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
        
        //Battle loop
        while(p->GetHP() > 0 && e->GetHP() > 0)
        {
            //Prompt phase
            PromptPlayer(p);
            PromptEnemy(e);

            //Action phase
            BattleActions(p, e);
        }

        if(p->GetHP() <= 0)
        {
            Defeat();
            dungeonQueue.EmptyQueue();
        }
        else if (e->GetHP() <= 0)
        {
            Victory();
            dungeonQueue.Dequeue();
        }
        delete e;
    }

    cout << "Thanks for playing!" << endl;
    delete p;
}

void InitializeActions(Player* p, Enemy* e)
{
    p->SetOpponent(e);
    e->SetOpponent(p);
}

//Move within player?
void PromptPlayer(Player* p)
{
    int playerActionChoice;
    Action* playerAction = nullptr;

    cout << endl;
    cout << "Available actions: "<< endl
    << "0 - " << p->GetAction(0)->name << endl
    << "1 - " << p->GetAction(1)->name << endl
    << "2 - " << p->GetAction(2)->name << endl
    << "3 - " << p->GetAction(3)->name << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerActionChoice;
    } while (playerActionChoice < 0 || playerActionChoice > 3);

    playerAction = p->GetAction(playerActionChoice);

    //Check if playerAction is null
    turnQueue.Enqueue(playerAction);
}

void PromptEnemy(Enemy* e)
{
    Action* enemyAction = e->GetAction(0);
    turnQueue.Enqueue(enemyAction);
}

void BattleActions(Player* p, Enemy* e)
{ 
    Action* action = nullptr;

    while(!turnQueue.IsEmpty())
    {
        cout << endl;
        action = turnQueue.GetHead();
        cout << action->GetSender()->name << " Action: " << action->name << endl;
        action->runAction();
        cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;

        if(p->GetHP() <= 0 || e->GetHP() <= 0)
        {
            turnQueue.EmptyQueue(); //Empty queue to exit loop, check victory conditions
        }
        else
        {
            turnQueue.Dequeue();
        }
    }
}

int RandomNum()
{
    srand(time(nullptr));
    int randNum = (rand() % 7) - 3;    //Number between -3 and 3
    return randNum;
}

void Victory()
{
    cout << "----------" << endl;
    cout << "YOU WIN!" << endl;
    cout << "----------" << endl;
}

void Defeat()
{
    cout << "----------" << endl;
    cout << "...you lose." << endl;
    cout << "----------" << endl;
}
#pragma endregion "Battle Code"