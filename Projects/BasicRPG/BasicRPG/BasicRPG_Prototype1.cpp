#include "main.h"

using namespace std;

void InitializeActions(Player*, Enemy*);
void PromptPlayer(Player*);
void PromptEnemy(Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();

Queue<Action> turnQueue;
//Queue<Enemy> dungeonQueue;

int main(int argc, char* argv[])
{
    Texture* bgTextures = new Texture[4];
    Texture* enemySprites = new Texture[4];
    DrawMaterials drawMaterials;
    drawMaterials.currentMenu = nullptr;
    drawMaterials.currentTB = nullptr;

    if (Initialize() != 0)
    {
        return -1;
    }
    else if(!LoadMedia(bgTextures, enemySprites))
    {
        return -1;
    }
    else
    {
        //currentTB = nullptr;
        //currentMenu = nullptr;

        Player* p = new Player();
        Enemy* e = nullptr;

        StateStack stateStack;

        TextboxState* tbState = new TextboxState("Thanks for playing!", &stateStack, &drawMaterials);
        stateStack.PushState(tbState);

        DungeonState* dungeonState = new DungeonState(&stateStack, p, bgTextures, enemySprites, &drawMaterials);
        stateStack.PushState(dungeonState);

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

            //State Stack
            if (stateStack.TopState() != nullptr)
            {
                stateStack.TopState()->runCurrentState();
            }
            else
            {
                isRunning = false;
            }

            if (stateStack.TopState() != nullptr)
            {
                //bgTexture = *(dungeonState->GetBGTexture());
                //enemySprite = *(dungeonState->GetEnemySprite());
            }

            Draw(&drawMaterials);
        }
    }

    CleanUp(&drawMaterials);

    return 0;
}

#pragma region "Battle Code"
//int main(int argc, char* argv[])
void TempBattleHolder()
{
    //dungeonQueue.Enqueue(new Goblin());
    //dungeonQueue.Enqueue(new Wizard());

    std::cout << "Welcome to BASIC RPG!" << endl << endl;

    Player* p = new Player();
    Enemy* e = nullptr;

    //while(!dungeonQueue.IsEmpty())
    //{
    //    e = dungeonQueue.GetHead();
    //    InitializeActions(p, e);

    //    cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
    //    
    //    //Battle loop
    //    while(p->GetHP() > 0 && e->GetHP() > 0)
    //    {
    //        //Prompt phase
    //        PromptPlayer(p);
    //        PromptEnemy(e);

    //        //Action phase
    //        BattleActions(p, e);
    //    }

    //    if(p->GetHP() <= 0)
    //    {
    //        Defeat();
    //        dungeonQueue.EmptyQueue();
    //    }
    //    else if (e->GetHP() <= 0)
    //    {
    //        Victory();
    //        dungeonQueue.Dequeue();
    //    }
    //    delete e;
    //}

    //cout << "Thanks for playing!" << endl;
    //delete p;
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

    std::cout << endl;
    std::cout << "Available actions: "<< endl
    << "0 - " << p->GetAction(0)->name << endl
    << "1 - " << p->GetAction(1)->name << endl
    << "2 - " << p->GetAction(2)->name << endl
    << "3 - " << p->GetAction(3)->name << endl;
    do
    {
        std::cout << "Enter next action: ";
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
        std::cout << endl;
        action = turnQueue.GetHead();
        std::cout << action->GetSender()->name << " Action: " << action->name << endl;
        action->runAction();
        std::cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;

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
    std::cout << "----------" << endl;
    std::cout << "YOU WIN!" << endl;
    std::cout << "----------" << endl;
}

void Defeat()
{
    std::cout << "----------" << endl;
    std::cout << "...you lose." << endl;
    std::cout << "----------" << endl;
}
#pragma endregion "Battle Code"