#include "TextboxState.h"

TextboxState::TextboxState(std::string text, StateStack* stateStackPtr, DrawMaterials* drawMat)
    :WaitState(stateStackPtr)
{
    texts.push_back(text);
    tb = new Textbox(globalRenderer, font);
    drawMaterials = drawMat;
    currentState = subState::Enter;
}

TextboxState::TextboxState(std::string* textArray, int textCount, StateStack* stateStackPtr, DrawMaterials* drawMat)
    :WaitState(stateStackPtr)
{
    for (int i = 0; i < textCount; i++)
    {
        texts.push_back(textArray[i]);
    }

    tb = new Textbox(globalRenderer, font);
    drawMaterials = drawMat;
    currentState = subState::Enter;
}

void TextboxState::runCurrentState()
{
    //currentTB = tb;

    drawMaterials->currentTB = tb;

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
        if (e.key.keysym.sym == SDLK_SPACE)
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
    drawMaterials->currentTB = nullptr;
    stateStack->StateFinish();
}

TextboxState::~TextboxState()
{
    delete tb;
    tb = nullptr;
}