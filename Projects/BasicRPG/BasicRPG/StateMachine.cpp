#include "SDLfoundation.h"
#include "entity.h"
#include "StateMachine.h"
#include "MenuState.h"
#include "BattleState.h"
#include "TextboxState.h"
#include "Texture.h"

void StateStack::PushState(State* newState)
{
    states.push(newState);
}

State* StateStack::TopState()
{
    if (states.size() <= 0)
    {
        return nullptr;
    }
    else
    {
        return states.top();
    }
}

void StateStack::StateFinish()
{
    State* temp = states.top();
    delete temp;
    states.pop();
}

StateStack::~StateStack()
{
    while (states.size() > 0)
    {
        State* temp = states.top();
        delete temp;
        states.pop();
    }
}

TurnState::TurnState(StateStack* stateStack, BattleManager* bm)
    :State(stateStack)
{
    player = bm->GetPlayer();
    enemy = bm->GetEnemy();
    turnQueue = bm->GetTurnQueue();
    drawMaterials = nullptr;
    currentState = subState::Start;
}

void TurnState::runCurrentState()
{
    Action* currentAction;
    std::string message;

    switch (currentState)
    {
    case subState::Start:
        Enter();
        currentState = subState::Action;
        break;
    case subState::Action:
        currentAction = turnQueue->GetHead();
        currentAction->runAction();

        message = "Player HP: " + std::to_string(player->GetHP()) + ", " + enemy->name + ": " + std::to_string(enemy->GetHP());
        stateStack->PushState(new TextboxState(message, stateStack, drawMaterials));

        currentState = subState::Check;
        break;
    case subState::Check:
        if (player->GetHP() <= 0 || enemy->GetHP() <= 0)
        {
            turnQueue->EmptyQueue();
        }
        else
        {
            turnQueue->Dequeue();
        }

        if(turnQueue->IsEmpty())
        {
            currentState = subState::Finish;
        }
        else
        {
            currentState = subState::Action;
        }
        break;
    case subState::Finish:
        Exit();
        break;
    }
}

void TurnState::Enter()
{

}

void TurnState::Exit()
{

}