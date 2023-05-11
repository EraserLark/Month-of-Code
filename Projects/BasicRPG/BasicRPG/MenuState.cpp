#include "BattleState.h"
#include "MenuState.h"
#include "SDLfoundation.h"
#include "StateMachine.h"
#include "Textzone.h"

MenuState::MenuState(StateStack* stateStack, BattleManager* bm, DrawMaterials* drawMat)
    :WaitState(stateStack)
{
    player = bm->GetPlayer();
    turnQueue = bm->GetTurnQueue();
    drawMaterials = drawMat;

    std::string optionText[]{ player->GetAction(0)->name, player->GetAction(1)->name, player->GetAction(2)->name };
    menu = new Menu(drawMaterials->renderer, drawMat->font, optionText);

    currentState = subState::Enter;
}

void MenuState::runCurrentState()
{
    drawMaterials->currentMenu = menu;

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
    drawMaterials->currentMenu = nullptr;
    stateStack->StateFinish();
}

MenuState::~MenuState()
{
    delete menu;
    menu = nullptr;
}