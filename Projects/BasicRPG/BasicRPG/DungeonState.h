#pragma once
#include "StateMachine.h"

struct Level {
    Enemy enemy;
    std::string bgFilepath;
    std::string openingLine;
};

class DungeonState : State {
public:
    DungeonState(StateStack*);
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    ~DungeonState() {}
private:
    Queue<Level> dungeonQueue;
};