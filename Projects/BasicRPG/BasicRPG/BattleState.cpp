#include "BattleState.h"
#include "MenuState.h"
#include "TextboxState.h"
#include "DungeonState.h"

BattleState::BattleState(StateStack* stateStack, Player* playerPtr, Queue<Level>* dungeonQueue)
    :State(stateStack)
{
    p = playerPtr;
    e = dungeonQueue->GetHead()->enemy;     //Set up enemy data
    this->dungeonQueue = dungeonQueue;
    battleManager = new BattleManager(stateStack, p, e, &turnQueue);
    currentState = subState::Start;
}

void BattleState::runCurrentState()
{
    std::string statsMessage;
    Action* enemyAction;

    switch (currentState)
    {
    case subState::Start:
        Enter();
        currentState = subState::PromptPhase;
        break;
    case subState::PromptPhase:
        stateStack->PushState(new MenuState(stateStack, battleManager));

        //Determine enemy action
        enemyAction = e->GetAction(0);
        turnQueue.Enqueue(enemyAction);

        currentState = subState::ActionPhase;
        break;
    case subState::ActionPhase:
        if (!turnQueue.IsEmpty())
        {
            Action* currentAction = turnQueue.GetHead();
            currentAction->runAction();

            statsMessage = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
            std::string actionMessage = currentAction->GetSender()->name + " action: " + currentAction->name;
            std::string messages[]{ actionMessage, statsMessage };
            stateStack->PushState(new TextboxState(messages, 2, stateStack));

            if (p->GetHP() <= 0 || e->GetHP() <= 0)
            {
                turnQueue.EmptyQueue(); //Empty queue to exit loop, check victory conditions
            }
            else
            {
                turnQueue.Dequeue();
            }
        }
        else
        {
            if (p->GetHP() <= 0)
            {
                stateStack->PushState(new TextboxState("...you lost", stateStack));
                //Empty dungeon queue
                currentState = subState::Finish;
            }
            else if (e->GetHP() <= 0)
            {
                stateStack->PushState(new TextboxState("YOU WIN!!", stateStack));
                //Keep moving through dungeon queue
                currentState = subState::Finish;
            }
            else
            {
                currentState = subState::PromptPhase;
            }
        }
        break;
    case subState::Finish:
        Exit();
        break;
    }
}

void BattleState::Enter()
{
    //Initialize actions
    battleManager->InitializeActions();

    std::string statsMessage = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
    stateStack->PushState(new TextboxState(statsMessage, stateStack));

    std::string message = e->name + " approaches!";
    stateStack->PushState(new TextboxState(message, stateStack));
}

void BattleState::Exit()
{
    dungeonQueue->Dequeue();
    stateStack->StateFinish();
}

BattleState::~BattleState()
{
    delete battleManager;
    battleManager = nullptr;
    p = nullptr;
    e = nullptr;
}


BattleManager::BattleManager(StateStack* stateStackPtr, Player* playerPtr, Enemy* enemyPtr, Queue<Action>* turnQueuePtr)
{
    stateStack = stateStackPtr;
    p = playerPtr;
    e = enemyPtr;
    turnQueue = turnQueuePtr;
}

void BattleManager::ShowHP()
{
    std::string message = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
    stateStack->PushState(new TextboxState(message, stateStack));
}

void BattleManager::InitializeActions()
{
    p->SetOpponent(e);
    e->SetOpponent(p);
}