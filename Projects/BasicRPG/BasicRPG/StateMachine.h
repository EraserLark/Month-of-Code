#pragma once
#include <stack>
#include <vector>
#include "SDLfoundation.h"
#include "entity.h"
#include "queue.h"
#include "action.h"

class Menu;
class Textbox;
class State;
class BattleManager;

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

class DungeonState : State {
public:
    DungeonState(StateStack*);
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    ~DungeonState() {}
private:
    //Queue<BattleState> dungeonQueue;

};

class BattleState : public State {
public:
    BattleState(StateStack*, Player*);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    ~BattleState();
private:
    enum class subState{Start, PromptPhase, ActionPhase, Finish};
    subState currentState;
    Player* p;
    Enemy* e;
    BattleManager* battleManager;
    Queue<Action> turnQueue;
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
};

class BattleManager {
public:
    BattleManager(StateStack*, Player*, Enemy*, Queue<Action>*);
    void ShowHP();
    void ShowAction();
    void InitializeActions();

    Player* GetPlayer() { return p; }
    Enemy* GetEnemy() { return e; }
    Queue<Action>* GetTurnQueue() { return turnQueue; }
private:
    StateStack* stateStack;
    Player* p;
    Enemy* e;
    Queue<Action>* turnQueue;
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

class TextboxState : public WaitState {
public:
    TextboxState(std::string, StateStack*);
    TextboxState(std::string*, int, StateStack*);
    virtual void Enter() override;
    virtual void Wait() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    virtual ~TextboxState();
private:
    enum class subState { Enter, Wait, Exit };
    subState currentState;
    Textbox* tb;
    std::vector<std::string> texts;
};

class MenuState : public WaitState {
public:
    MenuState(StateStack*, BattleManager*);
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
};