#pragma once
#include "StateMachine.h"
#include "BattleState.h"

struct Level {
    Level(Enemy*, Texture*, std::string);
    Enemy* enemy;
    Texture* bgTexture;
    std::string openingLine;
};

class DungeonState : public State {
private:
    enum class subState { NewLevel, Active, Finish };
    subState currentState;
    Texture* bgTextures;
    Texture* enemySprites;
    Queue<Level> dungeonQueue;
    Player* player;
    StateStack* stateStack;
    BattleState* battleState;
public:
    DungeonState(StateStack*, Player*, Texture*, Texture*);
    virtual void Enter() {}
    virtual void Exit() override;
    virtual void runCurrentState() override;
    Texture* GetBGTexture();
    Texture* GetEnemySprite();
    bool CheckDungeonQueueEmpty();
    ~DungeonState() {}
};