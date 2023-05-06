#pragma once
#include <stack>
#include <vector>
#include "SDLfoundation.h"
#include "entity.h"
#include "queue.h"
#include "action.h"

class Player;
class Enemy;
class Menu;
class Textbox;
class State;
class BattleManager;
struct DrawMaterials;

class StateStack {
public:
    StateStack() {}

    void PushState(State*);
    State* TopState();
    void StateFinish();

    ~StateStack();
private:
    std::stack<State*> states;
};

class State {
public:
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    virtual ~State() {}
protected:
    State(StateStack* stateStackPtr)
        :stateStack{ stateStackPtr }
    {}
    StateStack* stateStack;
};

class TurnState : public State {
public:
    TurnState(StateStack*, BattleManager*);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    ~TurnState() {}
private:
    enum class subState { Start, Action, Check, Finish };
    subState currentState;
    Player* p;
    Enemy* e;
    Queue<Action>* turnQueue;
    DrawMaterials* drawMaterials;
};

class WaitState : public State {
public:
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    virtual void Wait() = 0;
    virtual ~WaitState() {}
protected:
    WaitState(StateStack* stateStackPtr)
        :State(stateStackPtr)
    {}
};