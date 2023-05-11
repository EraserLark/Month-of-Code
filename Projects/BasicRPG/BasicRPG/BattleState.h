#pragma once
#include "StateMachine.h"

class Player;
class Enemy;
class BattleManager;
struct Level;
struct DrawMaterials;

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
    Action* enemyAction;
    BattleManager* battleManager;
    Queue<Action> turnQueue;
    Queue<Level>* dungeonQueue;
    DrawMaterials* drawMaterials;
};

class BattleManager {
public:
    BattleManager(StateStack*, Player*, Enemy*, Queue<Action>*, DrawMaterials*);
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