#include "BattleState.h"
#include "MenuState.h"
#include "TextboxState.h"
#include "DungeonState.h"

BattleState::BattleState(StateStack* stateStack, Player* playerPtr, Queue<Level>* dungeonQueue, DrawMaterials* drawMat)
    :State(stateStack)
{
    player = playerPtr;
    enemy = dungeonQueue->GetHead()->enemy;     //Set up enemy data
    enemyAction = nullptr;
    this->dungeonQueue = dungeonQueue;
    drawMaterials = drawMat;
    battleManager = new BattleManager(stateStack, player, enemy, &turnQueue, drawMat);
    currentState = subState::Start;
}

void BattleState::runCurrentState()
{
    std::string statsMessage;

    switch (currentState)
    {
    case subState::Start:
        Enter();
        currentState = subState::PromptPhase;
        break;

    case subState::PromptPhase:
        stateStack->PushState(new MenuState(stateStack, battleManager, drawMaterials));
        currentState = subState::ActionPhase;
        break;

    case subState::ActionPhase:
        if (enemyAction == nullptr)
        {
            enemyAction = enemy->GetAction(0);
            turnQueue.Enqueue(enemyAction);
        }

        if (!turnQueue.IsEmpty())
        {
            Action* currentAction = turnQueue.GetHead();
            currentAction->runAction();

            statsMessage = "Player HP: " + std::to_string(player->GetHP()) + ", " + enemy->name + ": " + std::to_string(enemy->GetHP());
            std::string actionMessage = currentAction->GetSender()->name + " action: " + currentAction->name;
            std::string messages[]{ actionMessage, statsMessage };
            stateStack->PushState(new TextboxState(messages, 2, stateStack, drawMaterials));

            if (player->GetHP() <= 0 || enemy->GetHP() <= 0)
            {
                turnQueue.EmptyQueue(); //Exit loop, check victory conditions
            }
            else
            {
                turnQueue.Dequeue();
            }
        }
        else
        {
            if (player->GetHP() <= 0)
            {
                dungeonQueue->EmptyQueue();
                currentState = subState::Finish;
                stateStack->PushState(new TextboxState("...you lost", stateStack, drawMaterials));
            }
            else if (enemy->GetHP() <= 0)
            {
                //Keep moving through dungeon queue
                currentState = subState::Finish;
                stateStack->PushState(new TextboxState("YOU WIN!!", stateStack, drawMaterials));
            }
            else
            {
                enemyAction = nullptr;
                player->ResetDEF();
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
    battleManager->InitializeActions();

    std::string statsMessage = "Player HP: " + std::to_string(player->GetHP()) + ", " + enemy->name + ": " + std::to_string(enemy->GetHP());
    stateStack->PushState(new TextboxState(statsMessage, stateStack, drawMaterials));

    std::string message = enemy->name + " approaches!";
    stateStack->PushState(new TextboxState(message, stateStack, drawMaterials));
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
    player = nullptr;
    enemy = nullptr;
}


BattleManager::BattleManager(StateStack* stateStackPtr, Player* playerPtr, Enemy* enemyPtr, Queue<Action>* turnQueuePtr, DrawMaterials* drawMat)
{
    stateStack = stateStackPtr;
    player = playerPtr;
    enemy = enemyPtr;
    turnQueue = turnQueuePtr;
    drawMaterials = drawMat;
}

void BattleManager::ShowHP()
{
    std::string message = "Player HP: " + std::to_string(player->GetHP()) + ", " + enemy->name + ": " + std::to_string(enemy->GetHP());
    stateStack->PushState(new TextboxState(message, stateStack, drawMaterials));
}

void BattleManager::InitializeActions()
{
    player->SetOpponent(enemy);
    enemy->SetOpponent(player);
}