#pragma once
#include "StateMachine.h"

class BattleState : public State {
public:
    BattleState(StateStack*, Player*, Queue<Enemy>*);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    ~BattleState();
private:
    enum class subState { Start, PromptPhase, ActionPhase, Finish };
    subState currentState;
    Player* p;
    Enemy* e;
    BattleManager* battleManager;
    Queue<Action> turnQueue;
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