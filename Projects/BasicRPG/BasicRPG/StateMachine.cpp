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


TextboxState::TextboxState(StateStack* stateStackPtr, Textbox* textboxPtr)
    :WaitState(stateStackPtr)
{
    tb = textboxPtr;
    currentState = subState::Enter;
}

void TextboxState::runCurrentState()
{
    switch (currentState)
    {
    case subState::Enter:
        Enter();
        currentState = subState::Wait;
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
    tb->NewText("The state stack is running!");
    tb->ShowTB();
}

void TextboxState::Wait()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        currentState = subState::Exit;
        //Just run Exit() here instead?
    }
}

void TextboxState::Exit()
{
    tb->HideTB();
    stateStack->StateFinish();
}