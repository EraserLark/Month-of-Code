#include "SDLfoundation.h"
#include "StateMachine.h"

void StateStack::PushState(State* newState)
{
    states.push(newState);
}

State* StateStack::TopState()
{
    if (states.top() != nullptr)
    {
        return states.top();
    }
}

void StateStack::StateFinish()
{
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


TextboxState::TextboxState()
{
    currentState = subState::Enter;
}

void TextboxState::SetTextbox(Textbox* textboxPtr)
{
    tb = textboxPtr;
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
}