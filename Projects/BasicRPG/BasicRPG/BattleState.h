#pragma once
#include "StateMachine.h"

struct Level;

class BattleState : public State {
public:
    BattleState(StateStack*, Player*, Queue<Level>*, DrawMaterials*);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    ~BattleState();
private:
    enum class subState { Start, PromptPhase, ActionPhase, Finish };
    subState currentState;
    Player* player;
    Enemy* enemy;
    BattleManager* battleManager;
    Queue<Action> turnQueue;
    Queue<Level>* dungeonQueue;
    DrawMaterials* drawMaterials;
};

class BattleManager {
public:
    BattleManager(StateStack*, Player*, Enemy*, Queue<Action>*, DrawMaterials*);
    void ShowHP();
    void ShowAction();
    void InitializeActions();

    Player* GetPlayer() { return player; }
    Enemy* GetEnemy() { return enemy; }
    Queue<Action>* GetTurnQueue() { return turnQueue; }
private:
    StateStack* stateStack;
    Player* player;
    Enemy* enemy;
    Queue<Action>* turnQueue;
    DrawMaterials* drawMaterials;
};