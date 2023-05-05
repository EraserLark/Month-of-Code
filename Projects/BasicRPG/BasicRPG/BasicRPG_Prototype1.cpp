#include "main.h"

using namespace std;

void InitializeActions(Player*, Enemy*);
void PromptPlayer(Player*);
void PromptEnemy(Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();

Queue<Action> turnQueue;
Queue<Enemy> dungeonQueue;

int main(int argc, char* argv[])
{
    if (Initialize() != 0)
    {
        return -1;
    }
    else if(!LoadMedia())
    {
        return -1;
    }
    else
    {
        //Textbox textbox(globalRenderer, font);
        //Menu menu(globalRenderer, font);

        currentTB = nullptr;
        currentMenu = nullptr;

        //Game vars
        dungeonQueue.Enqueue(new Goblin());
        dungeonQueue.Enqueue(new Wizard());

        Player* p = new Player();
        Enemy* e = nullptr;

        StateStack stateStack;

        //string messages[] { "Thanks for playing!", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"};
        TextboxState* tbState = new TextboxState("Thanks for playing!", &stateStack);
        stateStack.PushState(tbState);
        //MenuState* menuState = new MenuState(&stateStack, p);
        //stateStack.PushState(menuState);
        BattleState* battleState = new BattleState(&stateStack, p);
        stateStack.PushState(battleState);

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

            Draw(currentTB, currentMenu, &bgTexture, &enemySprite);
        }
    }

    CleanUp(&bgTexture, &enemySprite);

    return 0;
}

#pragma region "Battle Code"
//int main(int argc, char* argv[])
void TempBattleHolder()
{
    dungeonQueue.Enqueue(new Goblin());
    dungeonQueue.Enqueue(new Wizard());

    cout << "Welcome to BASIC RPG!" << endl << endl;

    Player* p = new Player();
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