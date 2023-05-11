#include "BattleState.h"
#include "MenuState.h"
#include "TextboxState.h"
#include "DungeonState.h"

BattleState::BattleState(StateStack* stateStack, Player* playerPtr, Queue<Level>* dungeonQueue, DrawMaterials* drawMat)
    :State(stateStack)
{
    player = playerPtr;
    enemy = dungeonQueue->GetHead()->enemy;     //Set up enemy data
    this->dungeonQueue = dungeonQueue;
    drawMaterials = drawMat;
    battleManager = new BattleManager(stateStack, player, enemy, &turnQueue, drawMat);
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
        stateStack->PushState(new MenuState(stateStack, battleManager, drawMaterials));

        //Determine enemy action
        enemyAction = enemy->GetAction(0);
        turnQueue.Enqueue(enemyAction);

        currentState = subState::ActionPhase;
        break;
    case subState::ActionPhase:
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
                turnQueue.EmptyQueue(); //Empty queue to exit loop, check victory conditions
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
                stateStack->PushState(new TextboxState("...you lost", stateStack, drawMaterials));
                //Empty dungeon queue
                dungeonQueue->EmptyQueue();
                currentState = subState::Finish;
            }
            else if (enemy->GetHP() <= 0)
            {
                stateStack->PushState(new TextboxState("YOU WIN!!", stateStack, drawMaterials));
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