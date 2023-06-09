#pragma once
#include "StateMachine.h"
#include "queue.h"

class Action;
class Menu;
class Player;
class BattleManager;
struct DrawMaterials;

class MenuState : public WaitState {
public:
    MenuState(StateStack*, BattleManager*, DrawMaterials*);
    virtual void Enter() override;
    virtual void Wait() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    virtual ~MenuState() override;
private:
    enum class subState { Enter, Wait, Exit };
    subState currentState;
    Menu* menu;
    Player* player;
    Queue<Action>* turnQueue;
    DrawMaterials* drawMaterials;
};