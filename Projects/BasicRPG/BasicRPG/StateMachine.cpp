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



//BattleState::BattleState(StateStack* stateStack, Player* playerPtr, Queue<Enemy>* dungeonQueue)
//    :State(stateStack)
//{
//    p = playerPtr;
//    e = dungeonQueue->GetHead();     //Set up enemy data
//    battleManager = new BattleManager(stateStack, p, e, &turnQueue);
//    currentState = subState::Start;
//}
//
//void BattleState::runCurrentState()
//{
//    std::string statsMessage;
//    Action* enemyAction;
//
//    switch (currentState)
//    {
//    case subState::Start:
//        Enter();
//        currentState = subState::PromptPhase;
//        break;
//    case subState::PromptPhase:
//        stateStack->PushState(new MenuState(stateStack, battleManager));
//
//        //Determine enemy action
//        enemyAction = e->GetAction(0);
//        turnQueue.Enqueue(enemyAction);
//
//        currentState = subState::ActionPhase;
//        break;
//    case subState::ActionPhase:
//        if (!turnQueue.IsEmpty())
//        {
//            Action* currentAction = turnQueue.GetHead();
//            currentAction->runAction();
//
//            statsMessage = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
//            std::string actionMessage = currentAction->GetSender()->name + " action: " + currentAction->name;
//            std::string messages[]{ actionMessage, statsMessage };
//            stateStack->PushState(new TextboxState(messages, 2, stateStack));
//
//            if (p->GetHP() <= 0 || e->GetHP() <= 0)
//            {
//                turnQueue.EmptyQueue(); //Empty queue to exit loop, check victory conditions
//            }
//            else
//            {
//                turnQueue.Dequeue();
//            }
//        }
//        else
//        {
//            if (p->GetHP() <= 0)
//            {
//                stateStack->PushState(new TextboxState("...you lost", stateStack));
//                //Empty dungeon queue
//                currentState = subState::Finish;
//            }
//            else if (e->GetHP() <= 0)
//            {
//                stateStack->PushState(new TextboxState("YOU WIN!!", stateStack));
//                //Keep moving through dungeon queue
//                currentState = subState::Finish;
//            }
//            else
//            {
//                currentState = subState::PromptPhase;
//            }
//        }
//        break;
//    case subState::Finish:
//        Exit();
//        break;
//    }
//}
//
//void BattleState::Enter()
//{
//    //Initialize actions
//    battleManager->InitializeActions();
//
//    std::string statsMessage = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
//    stateStack->PushState(new TextboxState(statsMessage, stateStack));
//
//    std::string message = e->name + " approaches!";
//    stateStack->PushState(new TextboxState(message, stateStack));
//}
//
//void BattleState::Exit()
//{
//    stateStack->StateFinish();
//}
//
//BattleState::~BattleState()
//{
//    delete battleManager;
//    battleManager = nullptr;
//    p = nullptr;
//    e = nullptr;
//}


TurnState::TurnState(StateStack* stateStack, BattleManager* bm)
    :State(stateStack)
{
    p = bm->GetPlayer();
    e = bm->GetEnemy();
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

        message = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
        stateStack->PushState(new TextboxState(message, stateStack, drawMaterials));

        currentState = subState::Check;
        break;
    case subState::Check:
        if (p->GetHP() <= 0 || e->GetHP() <= 0)
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


//BattleManager::BattleManager(StateStack* stateStackPtr, Player* playerPtr, Enemy* enemyPtr, Queue<Action>* turnQueuePtr)
//{
//    stateStack = stateStackPtr;
//    p = playerPtr;
//    e = enemyPtr;
//    turnQueue = turnQueuePtr;
//}
//
//void BattleManager::ShowHP()
//{
//    std::string message = "Player HP: " + std::to_string(p->GetHP()) + ", " + e->name + ": " + std::to_string(e->GetHP());
//    stateStack->PushState(new TextboxState(message, stateStack));
//}
//
//void BattleManager::InitializeActions()
//{
//    p->SetOpponent(e);
//    e->SetOpponent(p);
//}


//TextboxState::TextboxState(std::string text, StateStack* stateStackPtr)
//    :WaitState(stateStackPtr)
//{
//    texts.push_back(text);
//    tb = new Textbox(globalRenderer, font);
//    currentState = subState::Enter;
//}
//
//TextboxState::TextboxState(std::string* textArray, int textCount, StateStack* stateStackPtr)
//    :WaitState(stateStackPtr)
//{
//    for (int i = 0; i < textCount; i++)
//    {
//        texts.push_back(textArray[i]);
//    }
//
//    tb = new Textbox(globalRenderer, font);
//    currentState = subState::Enter;
//}
//
//void TextboxState::runCurrentState()
//{
//    currentTB = tb;
//
//    switch (currentState)
//    {
//    case subState::Enter:
//        Enter();
//        break;
//    case subState::Wait:
//        Wait();
//        break;
//    case subState::Exit:
//        Exit();
//        break;
//    }
//}
//
//void TextboxState::Enter()
//{
//    tb->NewText(texts.front());
//    tb->Show();
//    currentState = subState::Wait;
//}
//
//void TextboxState::Wait()
//{
//    SDL_Event e;
//    SDL_WaitEvent(&e);
//
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)     //Avoid repeated key inputs
//    {
//        if(e.key.keysym.sym == SDLK_SPACE)
//        {
//            texts.erase(texts.begin());
//
//            if (texts.empty())
//            {
//                currentState = subState::Exit;
//                //Just run Exit() here instead?
//            }
//            else
//            {
//                tb->NewText(texts.front());
//                currentState = subState::Wait;
//            }
//        }
//    }
//}
//
//void TextboxState::Exit()
//{
//    tb->Hide();
//    stateStack->StateFinish();
//}
//
//TextboxState::~TextboxState()
//{
//    delete tb;
//    tb = nullptr;
//}


//MenuState::MenuState(StateStack* stateStack, BattleManager* bm)
//    :WaitState(stateStack)
//{
//    player = bm->GetPlayer();
//    turnQueue = bm->GetTurnQueue();
//
//    std::string optionText[]{ player->GetAction(0)->name, player->GetAction(1)->name, player->GetAction(2)->name };
//
//    menu = new Menu(globalRenderer, font, optionText);
//    currentState = subState::Enter;
//}
//
//void MenuState::runCurrentState()
//{
//    switch (currentState)
//    {
//    case subState::Enter:
//        Enter();
//        break;
//    case subState::Wait:
//        Wait();
//        break;
//    case subState::Exit:
//        Exit();
//        break;
//    }
//}
//
//void MenuState::Enter()
//{
//    menu->Show();
//    currentState = subState::Wait;
//}
//
//void MenuState::Wait()
//{
//    int selection;
//
//    SDL_Event e;
//    SDL_WaitEvent(&e);
//
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)     //Avoid repeated key inputs
//    {
//        switch (e.key.keysym.sym)
//        {
//        case SDLK_SPACE:
//            selection = menu->ConfirmSelection();
//
//            //Enqueue action into turnQueue
//            turnQueue->Enqueue(player->GetAction(selection));
//
//            currentState = subState::Exit;
//            break;
//        case SDLK_LEFT:
//            menu->DecrementSelection();
//            break;
//        case SDLK_RIGHT:
//            menu->IncrementSelection();
//            break;
//        }
//    }
//}
//
//void MenuState::Exit()
//{
//    menu->Hide();
//    stateStack->StateFinish();
//}
//
//MenuState::~MenuState()
//{
//    delete menu;
//    menu = nullptr;
//}