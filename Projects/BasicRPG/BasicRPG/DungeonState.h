#pragma once
#include "BattleState.h"

class Texture;

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
    DrawMaterials* drawMaterials;
public:
    DungeonState(StateStack*, Player*, Texture*, Texture*, DrawMaterials*);
    virtual void Enter() {}
    virtual void Exit() override;
    virtual void runCurrentState() override;
    Texture* GetBGTexture();
    Texture* GetEnemySprite();
    bool CheckDungeonQueueEmpty();
    ~DungeonState();
};