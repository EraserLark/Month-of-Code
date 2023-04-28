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
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect dimensions = { 0,0,0,0 };
public:
    Texture() {}

    bool Load(string filePath)
    {
        surface = IMG_Load(filePath.c_str());
        if (surface == nullptr)
        {
            cout << "Could not load surface. Error: " << IMG_GetError();
            return false;
        }

        dimensions.w = surface->w;
        dimensions.h = surface->h;

        return true;
    }

    bool LoadText(TTF_Font* font, string text, SDL_Color fontColor)
    {
        DestroyTexture();

        surface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), fontColor, 400);
        if (surface == nullptr)
        {
            cout << "Could not load surface. Error: " << IMG_GetError();
            return false;
        }

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
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(globalRenderer, texture, source, dest);
    }

    void RenderText(SDL_Renderer* renderer)
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
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

const int ScreenWidth = 640;
const int ScreenHeight = 480;
bool isRunning = true;
SDL_Rect enemyDestRect{ (ScreenWidth / 2) - 100, (ScreenHeight / 2) - 100, 200, 200 };
SDL_Rect textboxRect{ 25, ScreenHeight - 100, ScreenWidth - 50, 75 };
SDL_Rect textRect{ 100, ScreenHeight - 100, 50, 200 };

Texture bgTexture;
Texture enemySprite;
Texture textTexture;
TTF_Font* textFont;
SDL_Color fontColor = { 0,0,0,0 };

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
        //Update
        while (isRunning)
        {
            //Event Handling
            SDL_Event event;

            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
            if (currentKeyStates[SDL_SCANCODE_SPACE])
            {
                textTexture.LoadText(textFont, "You pressed space!!", fontColor);
            }
            else if (currentKeyStates[SDL_SCANCODE_LEFT])
            {
                textTexture.LoadText(textFont, "You pressed left!", fontColor);
            }
            else if (currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                textTexture.LoadText(textFont, "You pressed right :)", fontColor);
            }

            SDL_RenderClear(globalRenderer);

            //Render sprites
            bgTexture.Render(globalRenderer);
            enemySprite.Render(globalRenderer, nullptr, &enemyDestRect);

            //Draw textbox
            SDL_SetRenderDrawColor(globalRenderer, 255, 255, 255, 0);
            SDL_RenderFillRect(globalRenderer, &textboxRect);
            SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 0);

            //Render text
            textTexture.RenderText(globalRenderer);

            //Update back buffer
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
    textTexture.SetPosition(textRect.x, textRect.y);
    textTexture.LoadText(textFont, "This is a test string", fontColor);

    if (!bgTexture.Load("Assets/BG/BasicRPG_PlantBG.png"))
        return false;
    if (!enemySprite.Load("Assets/Enemy/Enemy_Bush.png"))
        return false;
    else
        return true;
}

void CleanUp()
{
    SDL_DestroyWindow(globalWindow);
    SDL_DestroyRenderer(globalRenderer);

    bgTexture.DestroyTexture();
    enemySprite.DestroyTexture();

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