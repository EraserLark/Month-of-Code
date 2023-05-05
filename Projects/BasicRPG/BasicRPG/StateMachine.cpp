#include "SDLfoundation.h"
#include "StateMachine.h"

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



BattleState::BattleState(StateStack* stateStack, Player* playerPtr)
    :State(stateStack)
{
    p = playerPtr;
    e = nullptr;
    currentState = subState::Start;
}

void BattleState::Enter()
{
    //Set up enemy data
    //Initialize actions
}

void BattleState::runCurrentState()
{
    switch (currentState)
    {
    case subState::Start:
        Enter();
        currentState = subState::Prompt;
        break;
    case subState::Prompt:
        stateStack->PushState(new MenuState(stateStack, p, &turnQueue));
        stateStack->PushState(new TextboxState("An enemy approaches!", stateStack));
        //Determine enemy action
        currentState = subState::Action;
        break;
    case subState::Action:
        if (!turnQueue.IsEmpty())
        {
            std::string actionMessage = "Player action: " + turnQueue.GetHead()->name;
            stateStack->PushState(new TextboxState(actionMessage, stateStack));
             turnQueue.Dequeue();
        }
        else
        {
            currentState = subState::Finish;
        }
        //Run all actions in turnQueue
        break;
    case subState::Finish:
        Exit();
        //Other?
        break;
    }
}

void BattleState::Exit()
{
    p = nullptr;
    e = nullptr;
    stateStack->StateFinish();
}


TextboxState::TextboxState(std::string text, StateStack* stateStackPtr)
    :WaitState(stateStackPtr)
{
    texts.push_back(text);
    tb = new Textbox(globalRenderer, font);
    currentState = subState::Enter;
}

TextboxState::TextboxState(std::string* textArray, int textCount, StateStack* stateStackPtr)
    :WaitState(stateStackPtr)
{
    for (int i = 0; i < textCount; i++)
    {
        texts.push_back(textArray[i]);
    }

    tb = new Textbox(globalRenderer, font);
    currentState = subState::Enter;
}

void TextboxState::runCurrentState()
{
    currentTB = tb;

    switch (currentState)
    {
    case subState::Enter:
        Enter();
        break;
    case subState::Wait:
        Wait();
        break;
    case subState::Exit:
        Exit();
        break;
    }
}

void TextboxState::Enter()
{
    tb->NewText(texts.front());
    tb->Show();
    currentState = subState::Wait;
}

void TextboxState::Wait()
{
    SDL_Event e;
    SDL_WaitEvent(&e);

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)     //Avoid repeated key inputs
    {
        if(e.key.keysym.sym == SDLK_SPACE)
        {
            texts.erase(texts.begin());

            if (texts.empty())
            {
                currentState = subState::Exit;
                //Just run Exit() here instead?
            }
            else
            {
                tb->NewText(texts.front());
                currentState = subState::Wait;
            }
        }
    }
}

void TextboxState::Exit()
{
    tb->Hide();
    stateStack->StateFinish();
}

TextboxState::~TextboxState()
{
    delete tb;
    tb = nullptr;
}


MenuState::MenuState(StateStack* stateStack, Player* playerPtr, Queue<Action>* turnQueuePtr)
    :WaitState(stateStack)
{
    player = playerPtr;
    turnQueue = turnQueuePtr;

    std::string optionText[]{ player->GetAction(0)->name, player->GetAction(1)->name, player->GetAction(2)->name };

    menu = new Menu(globalRenderer, font, optionText);
    currentState = subState::Enter;
}

void MenuState::runCurrentState()
{
    switch (currentState)
    {
    case subState::Enter:
        Enter();
        break;
    case subState::Wait:
        Wait();
        break;
    case subState::Exit:
        Exit();
        break;
    }
}

void MenuState::Enter()
{
    menu->Show();
    currentState = subState::Wait;
}

void MenuState::Wait()
{
    int selection;

    SDL_Event e;
    SDL_WaitEvent(&e);

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)     //Avoid repeated key inputs
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            selection = menu->ConfirmSelection();
            //Enqueue action into turnQueue
            turnQueue->Enqueue(player->GetAction(selection));

            currentState = subState::Exit;
            break;
        case SDLK_LEFT:
            menu->DecrementSelection();
            break;
        case SDLK_RIGHT:
            menu->IncrementSelection();
            break;
        }
    }
}

void MenuState::Exit()
{
    menu->Hide();
    stateStack->StateFinish();
}

MenuState::~MenuState()
{
    delete menu;
    menu = nullptr;
}