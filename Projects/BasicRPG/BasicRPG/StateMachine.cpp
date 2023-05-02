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


TextboxState::TextboxState(std::string text, StateStack* stateStackPtr, Textbox* textboxPtr)
    :WaitState(stateStackPtr)
{
    texts.push_back(text);
    tb = textboxPtr;
    currentState = subState::Enter;
}

TextboxState::TextboxState(std::string* textArray, int textCount, StateStack* stateStackPtr, Textbox* textboxPtr)
    :WaitState(stateStackPtr)
{
    for (int i = 0; i < textCount; i++)
    {
        texts.push_back(textArray[i]);
    }

    tb = textboxPtr;
    currentState = subState::Enter;
}

void TextboxState::runCurrentState()
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

void TextboxState::Enter()
{
    tb->NewText(texts.front());
    tb->ShowTB();
    currentState = subState::Wait;
}

void TextboxState::Wait()
{
    //const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    //if (currentKeyStates[SDL_SCANCODE_SPACE])

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
    tb->HideTB();
    stateStack->StateFinish();
}